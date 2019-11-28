#!/bin/bash

cd MP-SPDZ

for i in mult3 innerprod xtabs; do
    ./compile.py -p 128 $i || exit 1
done

Scripts/setup-ssl.sh 3

mkdir Player-Data
echo 14 > Player-Data/Input-P0-0
echo 12 > Player-Data/Input-P1-0
echo 8 > Player-Data/Input-P2-0

progs="./mascot-party.x ./malicious-shamir-party.x ./shamir-party.x"

for prog in $progs; do
    for i in 0 1 2; do
	$prog -N 3 -p $i mult3 & true
    done | grep 1344 || exit 1
done

for i in 0 1; do
    cp Programs/Source/xtabs.Input-P$i-0 Player-Data/Input-P$i-0
done

for prog in $progs; do
    for i in 0 1 2; do
	$prog -N 3 -p $i innerprod & true
    done | grep 'InnerProd: 2248' || exit 1
done

for prog in $progs; do
    for i in 0 1 2; do
	$prog -N 3 -p $i xtabs & true
    done | grep 'expected 6, got 6' || exit 1
done
