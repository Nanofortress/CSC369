import sys
import re

if len(sys.argv) < 2:
    print "please specify a file as input and try again!"
else:
    fname = sys.argv[-1]
    with open(fname, "r") as f:
        text = f.read()

rates = re.findall(r"Hit rate: .*", text)
rates = map(lambda x: x.split()[-1], rates)

memsizes = [50, 100, 150, 200]
algos = ["rand ", "fifo ", "lru  ", "clock", "opt  "]

head = "                 50         100         150         200"
r1 = rates[0::4]
print
print "tr-simpleloop"
print head
for a in algos:
    print "  " + a,
    for m in memsizes:
        print "  ", r1.pop(0).rjust(8),
    print


r2 = rates[1::4]
print
print "tr-matmul"
print head
for a in algos:
    print "  " + a,
    for m in memsizes:
        print "  ", r2.pop(0).rjust(8),
    print

r3 = rates[2::4]
print
print "tr-blocked"
print head
for a in algos:
    print "  " + a,
    for m in memsizes:
        print "  ", r3.pop(0).rjust(8),
    print

r4 = rates[3::4]
print
print "tr-mine"
print head
for a in algos:
    print "  " + a,
    for m in memsizes:
        print "  ", r4.pop(0).rjust(8),
    print
