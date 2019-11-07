#!/bin/bash

FILES=/tst/*

for f in tst/*.txt
do
    x=$f
    y=${x%.}
    declare name=${y##*/}
    ./tp2 tst/$name
done
