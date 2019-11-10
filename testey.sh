#!/bin/bash

FILES=/dataset/*

for f in dataset/*.txt
do
    x=$f
    y=${x%.}
    declare name=${y##*/}
    ./tp3 dataset/$name
done
