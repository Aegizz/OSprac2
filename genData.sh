#!/bin/bash
echo "Starting LRU:"
echo "Frames, Page Fault Rate" > data/bzipLRU.csv
echo "Frames, Page Fault Rate" > data/gccLRU.csv
echo "Frames, Page Fault Rate" > data/swimLRU.csv
echo "Frames, Page Fault Rate" > data/sixpackLRU.csv

for (( i=1; i<101; i++ ))
do
    ./memsim traces/bzip.trace $i lru quiet >> data/bzipLRU.csv
    ./memsim traces/gcc.trace $i lru quiet >> data/gccLRU.csv
    ./memsim traces/swim.trace $i lru quiet >> data/swimLRU.csv
    ./memsim traces/sixpack.trace $i lru quiet >> data/sixpackLRU.csv
    echo "($i / 100)"
done


echo "Starting Clock:"
echo "Frames, Page Fault Rate" > data/bzipClock.csv
echo "Frames, Page Fault Rate" > data/gccClock.csv
echo "Frames, Page Fault Rate" > data/swimClock.csv
echo "Frames, Page Fault Rate" > data/sixpackClock.csv

for (( i=1; i<101; i++ ))
do
    ./memsim traces/bzip.trace $i clock quiet >> data/bzipClock.csv
    ./memsim traces/gcc.trace $i clock quiet >> data/gccClock.csv
    ./memsim traces/swim.trace $i clock quiet >> data/swimClock.csv
    ./memsim traces/sixpack.trace $i clock quiet >> data/sixpackClock.csv
    echo "($i / 100)"
done


echo "Starting Rand:"
echo "Frames, Page Fault Rate" > data/bzipRand.csv
echo "Frames, Page Fault Rate" > data/gccRand.csv
echo "Frames, Page Fault Rate" > data/swimRand.csv
echo "Frames, Page Fault Rate" > data/sixpackRand.csv

for (( i=1; i<101; i++ ))
do
    ./memsim traces/bzip.trace $i rand quiet >> data/bzipRand.csv
    ./memsim traces/gcc.trace $i rand quiet >> data/gccRand.csv
    ./memsim traces/swim.trace $i rand quiet >> data/swimRand.csv
    ./memsim traces/sixpack.trace $i rand quiet >> data/sixpackRand.csv
    echo "($i / 100)"
done