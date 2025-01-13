#!/bin/bash

batch_size=10
counter=0

end=500
for t0 in $(seq 1 $end); do
    for t1 in $(seq 1 $end); do
        for t2 in $(seq 1 $end); do
            for w in in $(seq 1 $end); do
                echo "$t0 $t1 $t2 $w";
                ./run_me ./dynamicInput.txt <<< "$t0 $t1 $t2 $w"
            done;
        done;
    done;
done;