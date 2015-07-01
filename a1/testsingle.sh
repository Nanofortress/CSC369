#! /bin/sh
make test_malloc

./test_malloc -f traces/1-simple-malloc
./test_malloc -f traces/2-extended-malloc
./test_malloc -f traces/3-simple-free
./test_malloc -f traces/4-reuse
./test_malloc -f traces/6-coalesce
./test_malloc -f traces/8-singleshort
./test_malloc -f traces/9-singlelong
./test_malloc -f traces/10-singlelonglong
./test_malloc -f traces/11-single-3000
./test_malloc -f traces/13-single-harsh
