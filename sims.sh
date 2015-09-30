#!/bin/bash
for i in `seq 1 10`;
do
    ./bin/sim_executable -d 0.0 -r 100 -a $i"000"e-12 -l resets 100000 -o 100-$i"000".dat -v 1e-60 -p 0 > /dev/null &
    ./bin/sim_executable -d 0.0 -r $i"000" -a 1e-12 -l resets 100000 -o $i"000"-1.dat -v 1e-60 -p 0 > /dev/null &
done
