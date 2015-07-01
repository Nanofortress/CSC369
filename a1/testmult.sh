#! /bin/sh
make test_malloc

./test_malloc -f traces/5-parallel-allocs
./test_malloc -f traces/7-longrandom
./test_malloc -f traces/12-mult-1000
./test_malloc -f traces/14-mult-10000
./test_malloc -f traces/15-mult-harsh
