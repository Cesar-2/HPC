#! /mnt/c/Users/cesar/Documents/HPC
for i in 1 2 3 4 5 6 7 8 9 10
do
    echo "Try $i \n">>result.txt
    for j in 16 200 400 600
    do
        echo "Matrix's size $j x $j: ">>result.txt
        gcc matrix.c -o output
        ./output $j
    done
    echo "\n">>result.txt
done