#! /mnt/c/Users/cesar/Documents/HPC
for i in 1 2 3 4 5 6 7 8 9 10
do  
    for k in 2 4 6 8
    do
        echo "Try $i \n">>result_threads.txt
        for j in 16 200 400 600
        do
            echo "Matrix's size $j x $j with $k threads: ">>result_threads.txt
            gcc -pthread matrix_thread.c -o output
            ./output $j $k
        done
        echo "\n">>result_threads.txt
    done
done