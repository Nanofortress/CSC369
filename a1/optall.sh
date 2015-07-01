#! /bin/sh
make test_malloc_opt

./test_malloc_opt -f traces/1-simple-malloc
./test_malloc_opt -f traces/2-extended-malloc
./test_malloc_opt -f traces/3-simple-free
./test_malloc_opt -f traces/4-reuse
./test_malloc_opt -f traces/6-coalesce
./test_malloc_opt -f traces/8-singleshort
./test_malloc_opt -f traces/9-singlelong
./test_malloc_opt -f traces/10-singlelonglong
./test_malloc_opt -f traces/11-single-3000
./test_malloc_opt -f traces/13-single-harsh

make test_malloc_opt

./test_malloc_opt -f traces/5-parallel-allocs
./test_malloc_opt -f traces/7-longrandom
./test_malloc_opt -f traces/12-mult-1000
./test_malloc_opt -f traces/14-mult-10000
./test_malloc_opt -f traces/15-mult-harsh
