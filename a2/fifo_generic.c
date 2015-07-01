#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "pagetable.h"

#include <stdbool.h>
#include <string.h>

extern int memsize;

extern int debug;

extern struct frame *coremap;

// main fifo queue, record the sequence of insertion
int* fifoq;
// bitmap recording referenced frames
bool* referenced;
// indices: tail - insert, head - evict
int tail, head;


/* Page to evict is chosen using the fifo algorithm.
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */
int fifo_evict() {
  // recover frame number from head of fifoq
  int frame = fifoq[head];

  // extra error checking
  assert(referenced[frame] == true);

  // mark frame as unreferneced
  referenced[frame] = false;

  // udpate deletion index
  head = (head + 1) % memsize;

  return frame;
}

/* This function is called on each access to a page to update any information
 * needed by the fifo algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void fifo_ref(pgtbl_entry_t *p) {
  // frame number of pte
  int frame = p->frame >> PAGE_SHIFT;

  // if not recently referenced
  if (referenced[frame] == false) {
    // mark frame as referenced
    referenced[frame] = true;
    // put frame number on to fifoq
    fifoq[tail] = frame;
    // update insertion index
    tail = (tail + 1) % memsize;
  }

  return;
}

/* Initialize any data structures needed for this 
 * replacement algorithm 
 */
void fifo_init() {
  fifoq = malloc(sizeof(int) * memsize);
  referenced = malloc(sizeof(bool) * memsize);
  memset(referenced, false, sizeof(bool) * memsize);
  tail = 0;
  head = 0;
}
