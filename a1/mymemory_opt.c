#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>

/*

Optimization documentation:

0. 
free list is already used in mymemory.c, no need to encounter allocated
memory chunks during mymalloc

1.
change first-fit algorithm to best-fit, resulting in some improvements:
space: obviously best-fit will find the most suitable chunk in the list
for a test file i used locally (single thread for bench marking reasons),
the max heap extent is reduced from 21168128 to 20365312, 3.8% less.
time: both algorithms are O(n), since best-fit looks through entire list,
it may takes a slightly more time, yet really not much loss.

2.
in mymalloc where search through the entire list without success to find
a big enough node, a new call to sbrk is required. i did extra work before
calling sbrk to see if the last node in free list can be coalesced with
the to-be-allocated chunk from sbrk.
for example: single line test file "m 0 1 8000"
suppose during init, one page is allocated but not yet used. normally,
8000 bytes would cause 2 pages to be allocated from sbrk. however, since
the previous page is still unused, i can only allocated one page and coalesce
with previous page to offer the 8000 bytes to user.
in this way, clearly, memory usage can be reduced to some extent.
as for the cost, it only requires O(1) arithmetic checking, given we have
been keeping track of last_node and its size.

*/

// macros
// simple macro for readability
#define PAGE 4096

// structs
// definition for free list node
typedef struct node_t {
  // number of bytes available after flnode info
  int size;
  // ptr to prev flnode
  struct node_t* prev;
  // ptr to next flnode
  struct node_t* next;
} flnode_t;

// definition for memory header
typedef struct {
  // number of bytes allocated
  int size;
  // magic number providing sanity check
  int magic;
} header_t;

// constants
// the magic number i pick
const int MAGIC = 13579;
// enforce multiple of 8 bytes for free list node
// const int FLNSIZE = 8 * (int)ceil(sizeof(flnode_t) / 8.0);
const int FLNSIZE = 24;
// enforce multiple of 8 bytes for header
// const int HSIZE = 8 * (int)ceil(sizeof(header_t) / 8.0);
const int HSIZE = 8;

// global variable to keep track of free list
flnode_t* head = NULL;

// pthread mutex lock protecting the free list
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;


// inspect the free list, for debug
void inspect() {
  flnode_t* p = head;
  while (p) {
    // printf("\t%p\t%d\n", p, p->size);
    p = p->next;
  }
}


/*
  add a new flnode to free list
  you can count on this function to do proper coalescing
  no threading handling in this function
  when use: please guarantee the lock is acquired!
*/
void add_and_coalesce(flnode_t* new_node) {
  // if no free list node, just make new_node the head
  if (head == NULL) {
    head = new_node;
    return;
  }
  
  flnode_t* p = head;
  while (p) {
    if (p < new_node && (p->next > new_node || p->next == NULL)) {
      // if both front and back are possible, need to coalesce both
      // need two vars to indicate branching option
      int wprev = ((void*)p + p->size + FLNSIZE == new_node);
      int wnext = ((void*)new_node + new_node->size + FLNSIZE == p->next);

      // coalsece with p and p->next
      if (wprev && wnext) {
        // p->next automatically not NULL
        p->size += new_node->size + p->next->size + FLNSIZE * 2;
        if (p->next->next) {
          p->next->next->prev = p;
        }
        p->next = p->next->next;

        return;
      }

      // coalesce with p
      if (wprev) {
        p->size += new_node->size + FLNSIZE;

        return;
      }

      // coalesce with p->next
      if (wnext) {
        new_node->size += p->next->size + FLNSIZE;
        new_node->prev = p;
        new_node->next = p->next->next;
        p->next = new_node;
        if (p->next->next) {
          p->next->next->prev = new_node;
        }

        return;
      }

      // no coalesce
      new_node->next = p->next;
      if (p->next) {
        p->next->prev = new_node;
      }
      p->next = new_node;
      new_node->prev = p;

      return;
    }
    p = p->next;
  }
}

  
/* mymalloc_init: initialize any data structures that your malloc needs in
   order to keep track of allocated and free blocks of 
   memory. Get an initial chunk of memory for the heap from
   the OS using sbrk() and mark it as free so that it can be 
   used in future calls to mymalloc()
*/
int mymalloc_init() {
  // init only called once for all threads, no need to lock

  // make sbrk give one page on startup
  int initial_size = PAGE;
  if ((head = sbrk(initial_size)) == (void*)-1) {
    fputs("sbrk yields -1!", stderr);
    return 1;
  }

  // record size of avail mem excluding flnode
  head->size = initial_size - FLNSIZE;
  head->prev = NULL;
  head->next = NULL;

  return 0;
}


/* mymalloc: allocates memory on the heap of the requested size. The block
   of memory returned should always be padded so that it begins
   and ends on a word boundary.
   unsigned int size: the number of bytes to allocate.
   retval: a pointer to the block of memory allocated or NULL if the 
   memory could not be allocated. 
   (NOTE: the system also sets errno, but we are not the system, 
   so you are not required to do so.)
*/
// assume the free list goes monotonically in address and are coalesced
void *mymalloc(unsigned int size) {
  // about how to deal with malloc(0):
  // http://stackoverflow.com/questions/2022335/whats-the-point-in-malloc0#answer-2022402
  // i choose to allocate some nonzero size memory

  // need to deal with mem size <= some value
  // size + HSIZE <= FLNSIZE
  // =: still need to keep the fl node for future coalescing
  // ensure when the mem is freed, a free list node can fit in
  if (size + HSIZE <= FLNSIZE) {
    size = FLNSIZE - HSIZE;
  }

  // enforce allocating multiples of 8 bytes
  size = 8 * (int)ceil(size / 8.0);
  // reserve more bytes for header
  int size_required = size + HSIZE;

  // start of lock
  pthread_mutex_lock(&lock);

  // main ptr for list traversal
  flnode_t* p = head;
  // record last_node for future optimization
  flnode_t* last_node = NULL;
  
  // vars used for keeping track of best-fit
  flnode_t* best_node = NULL;
  int best_size_diff = 0xffffff; // some random large number

  while (p != NULL) {

    // this case is fairly optimal, threat as best-fit if it occurs
    if (p->size + FLNSIZE >= size_required && size_required >= p->size) {
      // no extra space left for free list node
      // might as well just allocate all it has to user
      size = FLNSIZE + p->size - HSIZE;

      // remove node p, join p->prev and p->next
      if (p->prev) {
        p->prev->next = p->next;
      } else {
        head = p->next;
      }
      if (p->next) {
        p->next->prev = p->prev;
      }

      void* retaddr = (void*)p + HSIZE;
      // allocated mem info header
      header_t* mem_info = retaddr - HSIZE;
      mem_info->size = size;
      mem_info->magic = MAGIC;

      pthread_mutex_unlock(&lock);
      return retaddr;
    }
    
    // traverse, compare, get the best-fit
    if (p->size > size_required) {
      if (p->size - size_required < best_size_diff) {
        best_size_diff = p->size - size_required;
        best_node = p;
      }
    }

    last_node = p;
    p = p->next;
  }

  // if exist a best-fit
  if (best_node) {
    // allocate from the back of avail mem chunk
    // so as to reduce operations on free list node
    void* retaddr = (void*)best_node + FLNSIZE + best_node->size - size;
    
    // make extra header for allocated mem
    header_t* mem_info = retaddr - HSIZE;
    mem_info->size = size;
    mem_info->magic = MAGIC;
    
    // update free list node avail size info
    best_node->size -= size_required;
    
    pthread_mutex_unlock(&lock);
    return retaddr;
  }

  // not enough mem in free list, sbrk a new chunk
  // tricky! new sbrk amount depends on whether last fl node can be coalesced
  int alloc_size = size;

  if (last_node) {
    // NULL checking necessary! in case: head = NULL, last_node = NULL
    if ((void*)last_node + FLNSIZE + last_node->size == sbrk(0)) {
      // can be coalesced
      if (alloc_size - last_node->size > 0) {
        alloc_size -= last_node->size;
      }
    }
  }

  int new_size = PAGE * ceil(alloc_size / (float)PAGE);
  
  // make new node for free list
  flnode_t* new_node = NULL;
  if ((new_node = sbrk(new_size)) == (void*)-1) {
    // sbrk gives error
    pthread_mutex_unlock(&lock);
    return NULL;
  }
  new_node->size = new_size - FLNSIZE;

  // now new_node is produced, only need to add to list
  add_and_coalesce(new_node);

  pthread_mutex_unlock(&lock);
  return mymalloc(size);
}


/* myfree: unallocates memory that has been allocated with mymalloc.
   void *ptr: pointer to the first byte of a block of memory allocated by 
   mymalloc.
   retval: 0 if the memory was successfully freed and 1 otherwise.
   (NOTE: the system version of free returns no error.)
*/
unsigned int myfree(void *ptr) {
  // simplest way now: lock everything in myfree
  pthread_mutex_lock(&lock);

  // from spec, NULL is illegal input
  if (ptr == NULL) {
    fputs("freeing NULL ptr!\n", stderr);
    pthread_mutex_unlock(&lock);
    return 1;
  }

  header_t* mem_info = ptr - HSIZE; // DIFF
  // simplest form of sanity check
  if (mem_info->magic != MAGIC) {
    fputs("freeing bad ptr!\n", stderr);
    if (mem_info->magic == 0) {
      fputs("possibly this is already freed!\n", stderr);
    }
    pthread_mutex_unlock(&lock);
    return 1;
  }
  // set magic field to 0 to mark it as freed
  mem_info->magic = 0;

  // retrieve size of allocated block
  int size = mem_info->size;
  // make a new free list node
  flnode_t* new_node = ptr - HSIZE;
  new_node->size = size + HSIZE - FLNSIZE;

  // insert to right position
  add_and_coalesce(new_node);

  pthread_mutex_unlock(&lock);
  return 0;
}
