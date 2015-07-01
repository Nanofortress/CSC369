README a2


1. Task 2 tables

fourth program:
a python program for CSC384 a1
given it's quite exotic, it might be interesting in some sense


trace file:  simple

memsize:  50

           HitRate    HitCount   MissCount  TotalEvict  CleanEvict  DirtyEvict
  rand     71.6555        7670        3034        2984         272        2712
  fifo     72.1880        7727        2977        2927         204        2723
   lru     73.9817        7919        2785        2735          89        2646
 clock     73.8322        7903        2801        2751          97        2654
   opt     74.9626        8024        2680        2630          29        2601

memsize:  100

           HitRate    HitCount   MissCount  TotalEvict  CleanEvict  DirtyEvict
  rand     74.1125        7933        2771        2671          64        2607
  fifo     74.2059        7943        2761        2661          44        2617
   lru     74.8786        8015        2689        2589           2        2587
 clock     74.8505        8012        2692        2592           3        2589
   opt     75.3457        8065        2639        2539           0        2539

memsize:  150

           HitRate    HitCount   MissCount  TotalEvict  CleanEvict  DirtyEvict
  rand     74.5422        7979        2725        2575          21        2554
  fifo     74.5889        7984        2720        2570          16        2554
   lru     74.9066        8018        2686        2536           0        2536
 clock     74.8972        8017        2687        2537           0        2537
   opt     75.3457        8065        2639        2489           0        2489

memsize:  200

           HitRate    HitCount   MissCount  TotalEvict  CleanEvict  DirtyEvict
  rand     74.6357        7989        2715        2515          15        2500
  fifo     74.6637        7992        2712        2512          12        2500
   lru     74.9066        8018        2686        2486           0        2486
 clock     74.8972        8017        2687        2487           0        2487
   opt     75.3457        8065        2639        2439           0        2439


trace file:  matmul

memsize:  50

           HitRate    HitCount   MissCount  TotalEvict  CleanEvict  DirtyEvict
  rand     66.4848     1973461      994827      994777      955498       39279
  fifo     62.0226     1841009     1127279     1127229     1083234       43995
   lru     64.9218     1927065     1041223     1041173     1040067        1106
 clock     64.9215     1927058     1041230     1041180     1040068        1112
   opt     80.2086     2380823      587465      587415      586329        1086

memsize:  100

           HitRate    HitCount   MissCount  TotalEvict  CleanEvict  DirtyEvict
  rand     89.0829     2644237      324051      323951      316281        7670
  fifo     63.4956     1884731     1083557     1083457     1061230       22227
   lru     66.0930     1961832     1006456     1006356     1005274        1082
 clock     66.2500     1966492     1001796     1001696     1000612        1084
   opt     96.8737     2875489       92799       92699       91615        1084

memsize:  150

           HitRate    HitCount   MissCount  TotalEvict  CleanEvict  DirtyEvict
  rand     96.7449     2871668       96620       96470       94096        2374
  fifo     98.8406     2933874       34414       34264       32947        1317
   lru     98.8920     2935400       32888       32738       31657        1081
 clock     98.8317     2933610       34678       34528       33446        1082
   opt     99.1033     2941672       26616       26466       25383        1083

memsize:  200

           HitRate    HitCount   MissCount  TotalEvict  CleanEvict  DirtyEvict
  rand     98.0846     2911434       56854       56654       55006        1648
  fifo     98.8582     2934396       33892       33692       32436        1256
   lru     98.8924     2935412       32876       32676       31595        1081
 clock     98.8920     2935399       32889       32689       31608        1081
   opt     99.3509     2949022       19266       19066       17983        1083


trace file:  blocked

memsize:  50

           HitRate    HitCount   MissCount  TotalEvict  CleanEvict  DirtyEvict
  rand     99.6714     2516774        8298        8248        5691        2557
  fifo     99.7448     2518629        6443        6393        4118        2275
   lru     99.7967     2519939        5133        5083        2748        2335
 clock     99.7726     2519331        5741        5691        3251        2440
   opt     99.8534     2521370        3702        3652        2568        1084

memsize:  100

           HitRate    HitCount   MissCount  TotalEvict  CleanEvict  DirtyEvict
  rand     99.7930     2519844        5228        5128        3404        1724
  fifo     99.8291     2520757        4315        4215        2734        1481
   lru     99.8501     2521286        3786        3686        2603        1083
 clock     99.8343     2520888        4184        4084        2608        1476
   opt     99.8812     2522072        3000        2900        1829        1071

memsize:  150

           HitRate    HitCount   MissCount  TotalEvict  CleanEvict  DirtyEvict
  rand     99.8242     2520633        4439        4289        2788        1501
  fifo     99.8331     2520858        4214        4064        2640        1424
   lru     99.8507     2521302        3770        3620        2558        1062
 clock     99.8502     2521290        3782        3632        2570        1062
   opt     99.9000     2522547        2525        2375        1300        1075

memsize:  200

           HitRate    HitCount   MissCount  TotalEvict  CleanEvict  DirtyEvict
  rand     99.8484     2521244        3828        3628        2289        1339
  fifo     99.8746     2521905        3167        2967        1868        1099
   lru     99.8536     2521375        3697        3497        2435        1062
 clock     99.8733     2521872        3200        3000        1938        1062
   opt     99.9099     2522797        2275        2075        1009        1066


trace file:  mine

memsize:  50

           HitRate    HitCount   MissCount  TotalEvict  CleanEvict  DirtyEvict
  rand     99.7065      449166        1322        1272         861         411
  fifo     99.7458      449343        1145        1095         712         383
   lru     99.8351      449745         743         693         406         287
 clock     99.8275      449711         777         727         433         294
   opt     99.8941      450011         477         427         173         254

memsize:  100

           HitRate    HitCount   MissCount  TotalEvict  CleanEvict  DirtyEvict
  rand     99.9003      450039         449         349         114         235
  fifo     99.9094      450080         408         308          73         235
   lru     99.9305      450175         313         213          31         182
 clock     99.9281      450164         324         224          37         187
   opt     99.9465      450247         241         141           2         139

memsize:  150

           HitRate    HitCount   MissCount  TotalEvict  CleanEvict  DirtyEvict
  rand     99.9296      450171         317         167          21         146
  fifo     99.9456      450243         245          95           0          95
   lru     99.9501      450263         225          75           0          75
 clock     99.9498      450262         226          76           0          76
   opt     99.9501      450263         225          75           0          75

memsize:  200

           HitRate    HitCount   MissCount  TotalEvict  CleanEvict  DirtyEvict
  rand     99.9432      450232         256          56           3          53
  fifo     99.9492      450259         229          29           0          29
   lru     99.9501      450263         225          25           0          25
 clock     99.9496      450261         227          27           0          27
   opt     99.9501      450263         225          25           0          25



2. comparison

hit rate table


tr-simpleloop
                 50         100         150         200
  rand      71.6555     74.1125     74.5422     74.6357
  fifo      72.1880     74.2059     74.5889     74.6637
  lru       73.9817     74.8786     74.9066     74.9066
  clock     73.8322     74.8505     74.8972     74.8972
  opt       74.9626     75.3457     75.3457     75.3457

tr-matmul
                 50         100         150         200
  rand      66.4848     89.0829     96.7449     98.0846
  fifo      62.0226     63.4956     98.8406     98.8582
  lru       64.9218     66.0930     98.8920     98.8924
  clock     64.9215     66.2500     98.8317     98.8920
  opt       80.2086     96.8737     99.1033     99.3509

tr-blocked
                 50         100         150         200
  rand      99.6714     99.7930     99.8242     99.8484
  fifo      99.7448     99.8291     99.8331     99.8746
  lru       99.7967     99.8501     99.8507     99.8536
  clock     99.7726     99.8343     99.8502     99.8733
  opt       99.8534     99.8812     99.9000     99.9099

tr-mine
                 50         100         150         200
  rand      99.7065     99.9003     99.9296     99.9432
  fifo      99.7458     99.9094     99.9456     99.9492
  lru       99.8351     99.9305     99.9501     99.9501
  clock     99.8275     99.9281     99.9496     99.9496
  opt       99.8941     99.9465     99.9501     99.9501


hit rates:

Generally, we have the trend of: FIFO < LRU ~= CLOCK < OPT.
OPT always have the highest hit rate since OPT is optimal in a sense that
it always selects the page that won't be used for the longest period of 
time. Thus when a page is being evicted, OPT ensures that's the best page
to pick, which minimizes miss count in the whole process.
RAND does better than FIFO, LRU, CLOCK in tr-matmul. The major reason is
that the data used in matmul is randomly generated dynamically, which means
the blocks of data are less likely to be contiguous. With locality reduced,
LRU and CLOCK can't optimize much and thus RAND might get the chance to 
perform better.
RAND does worse than FIFO, LRU, CLOCK in other trace files, where locality of
data is ensured by the program (putting data into blocks before computation
is carried out). By similar reasoning, FIFO, LRU, CLOCK can make use of
locality to reduce miss count and beat RAND in this case. In tr-simpleloop,
RAND does obviously the worse since the trace file exhibits strong locality
and RAND just can't utilize this property.
LRU and CLOCK get very similar hit rates in all cases. The primary reason
might be that they are very similar algorithms, since we can see CLOCK
(evicting the page that is old enough) as a away of approximating exact LRU
(evicting the oldest page). The two both performs better than FIFO since
they deal with the last reference time for a frame rather than the first
reference time, which is naturally more sensible to be considered when we
measure the behavior of the referenced frame.


3. LRU

hit rate table for LRU

                  50         100         150         200
simpleloop   73.9817     74.8786     74.9066     74.9066
    matmul   64.9218     66.0930     98.8920     98.8924
   blocked   99.7967     99.8501     99.8507     99.8536
      mine   99.8351     99.9305     99.9501     99.9501


Generally, under each test trace file, as memory size increases, the hit rate
(or hit count) also increases. LRU makes use of the fact of locality, which
means program and data references within a process tend to cluster in physical
memory. Once eviction is needed, LRU selects the page that hasn't been used 
for the longest time. Hence with increased memory size, we can store more 
recently used pages, which enables us to store a more complete profile of 
recently referenced pages, improving the precision of our knowledge of least 
recently used page. Hence, LRU is good at exploiting the locality of a program
by analyzing the past, leading to increased hit rate.
We can see when when memsize increase from 100 to 150 for matmul case, there
is a sudden jump in hit rate. With some calculation, we can see for storing
each matrix to be multiplied, we need roughly 100 page frames. And for naive
multiplication to work, we need to have 200 page frames for storing the two
matrices. Yet for the case where memsize = 50 or 100, it is far from enough to
load the matrix all at once, hence switching back and forth between the 200
frames is needed. With memsize = 150, we can store at least one and a half
matrices at the same time, reducing a lot of page replacement in computation.
It is not specific to LRU actually, as we can see there are jumps from 100 to
150 for each algorithm.
And we can also see a ceiling of hit rates in the case of tr-mine.ref, at 
memsize = 150 and 200. It's definitely possible, since the program might 
exhibit certain behavior to cause the hit rate not increasing, when memory
size increase. This essentially means LRU is achieving its best at even 
memsize = 150, and such fact can be backed up since we see LRU and OPT have 
the same hit rate at memsize = 150 and 200, meaning LRU is behaving quite 
optimal.

