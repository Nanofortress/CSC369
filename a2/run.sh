make
./rand.sh $1 999999 2> err | grep 'check' | wc -l
./fifo.sh $1 999999 2>> err | grep 'check' | wc -l
./lru.sh $1 999999 2>> err | grep 'check' | wc -l
./clock.sh $1 999999 2>> err | grep 'check' | wc -l
./opt.sh $1 999999 2>> err | grep 'check' | wc -l
ls -ahl err
cat err | grep 'core dump'
cat err | grep 'Error'
cat err | grep 'swap'
