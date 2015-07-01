make
./sim -f traceprogs/short.ref -m $1 -s $2 -a lru
./sim -f traceprogs/tr-simpleloop.ref -m $1 -s $2 -a lru
./sim -f traceprogs/tr-matmul.ref -m $1 -s $2 -a lru
./sim -f traceprogs/tr-blocked.ref -m $1 -s $2 -a lru
