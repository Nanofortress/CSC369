import sys
import re


def read_chunk(c):
    s = c.split("\n")
    hit_count = s[0].split()[-1].rjust(11)
    miss_count = s[1].split()[-1].rjust(11)
    clean_evict = s[2].split()[-1].rjust(11)
    dirty_evict = s[3].split()[-1].rjust(11)
    total_evict = str(int(clean_evict) + int(dirty_evict)).rjust(11)
    hit_rate = s[5].split()[-1].rjust(11)
    return (hit_rate, hit_count, miss_count, 
            total_evict, clean_evict, dirty_evict)


if len(sys.argv) < 2:
    print "please specify a file as input and try again!"
else:
    fname = sys.argv[-1]
    with open(fname, "r") as f:
        text = f.read()

# ignore first chunk of compilation output
chunks = text.split("\n\n")[1:]

trsimple = {}
trmatmul = {}
trblocked = {}
trmine = {}

for i in range(20):
    size, algo = chunks[5 * i].split()
    simp = read_chunk(chunks[5 * i + 1])
    matm = read_chunk(chunks[5 * i + 2])
    bloc = read_chunk(chunks[5 * i + 3])
    mine = read_chunk(chunks[5 * i + 4])
    trsimple[(size, algo)] = simp
    trmatmul[(size, algo)] = matm
    trblocked[(size, algo)] = bloc
    trmine[(size, algo)] = mine

HEAD = "           HitRate    HitCount   MissCount  TotalEvict  CleanEvict  DirtyEvict"
for f in ["simple", "matmul", "blocked", "mine"]:
    print
    print
    print "trace file: ", f
    for size in map(str, [50, 100, 150, 200]):
        print
        print "memsize: ", size
        print
        print HEAD
        for algo in ["rand", "fifo", "lru", "clock", "opt"]:
            query = "tr" + f + "[(size, algo)]"
            tup = eval(query)
            print algo.rjust(6),
            print " ".join(tup)
