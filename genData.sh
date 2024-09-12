#!/bin/bash
<<comment
echo "Frames, Page Fault Rate" > bzipLRU.csv

for (( i=1; i<101; i++ ))
do
    ./a.out bzip.trace $i lru quiet >> bzipLRU.csv
    echo "($i / 100)"
done


echo "Frames, Page Fault Rate" > gccLRU.csv

for (( i=1; i<101; i++ ))
do
    ./a.out gcc.trace $i lru quiet >> gccLRU.csv
    echo "($i / 100)"
done


echo "Frames, Page Fault Rate" > swimLRU.csv

for (( i=1; i<101; i++ ))
do
    ./a.out swim.trace $i lru quiet >> swimLRU.csv
    echo "($i / 100)"
done


echo "Frames, Page Fault Rate" > sixpackLRU.csv

for (( i=1; i<101; i++ ))
do
    ./a.out sixpack.trace $i lru quiet >> sixpackLRU.csv
    echo "($i / 100)"
done

echo "Frames, Page Fault Rate" > bzipClock.csv

for (( i=1; i<101; i++ ))
do
    ./a.out bzip.trace $i clock quiet >> bzipClock.csv
    echo "($i / 100)"
done


echo "Frames, Page Fault Rate" > gccClock.csv

for (( i=1; i<101; i++ ))
do
    ./a.out gcc.trace $i clock quiet >> gccClock.csv
    echo "($i / 100)"
done


echo "Frames, Page Fault Rate" > swimClock.csv

for (( i=1; i<101; i++ ))
do
    ./a.out swim.trace $i clock quiet >> swimClock.csv
    echo "($i / 100)"
done


echo "Frames, Page Fault Rate" > sixpackClock.csv

for (( i=1; i<101; i++ ))
do
    ./a.out sixpack.trace $i clock quiet >> sixpackClock.csv
    echo "($i / 100)"
done

comment


echo "Frames, Page Fault Rate" > bzipRand.csv

for (( i=1; i<101; i++ ))
do
    ./a.out bzip.trace $i rand quiet >> bzipRand.csv
    echo "($i / 100)"
done


echo "Frames, Page Fault Rate" > gccRand.csv

for (( i=1; i<101; i++ ))
do
    ./a.out gcc.trace $i rand quiet >> gccRand.csv
    echo "($i / 100)"
done


echo "Frames, Page Fault Rate" > swimRand.csv

for (( i=1; i<101; i++ ))
do
    ./a.out swim.trace $i rand quiet >> swimRand.csv
    echo "($i / 100)"
done


echo "Frames, Page Fault Rate" > sixpackRand.csv

for (( i=1; i<101; i++ ))
do
    ./a.out sixpack.trace $i rand quiet >> sixpackRand.csv
    echo "($i / 100)"
done
