#!/bin/bash

files=( "grafo4.txt" "grafo8.txt" "grafo12.txt" "grafo16.txt" "grafo20.txt")
for i in "${files[@]}"
do
   for j in 1 2 3 4 5
   do
        echo $i
        ./tp1 $i
    done
    echo "------FIM\n" >> tempo/tempos.txt
done
