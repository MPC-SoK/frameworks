#!/bin/bash

cd MP-SPDZ

for i in mult3 innerprod xtabs; do
    ./compile.py -B 32 $i || exit 1
done

mkdir Player-Data
echo 14 8 > Player-Data/Input-P0-0
echo 12 > Player-Data/Input-P1-0

./yao-player.x -p 0 mult3 &
./yao-player.x -p 1 mult3 | grep 1344 || exit 1

for i in 0 1; do
    cp Programs/Source/xtabs.Input-P$i-0 Player-Data/Input-P$i-0
done

./yao-player.x -p 0 innerprod &
./yao-player.x -p 1 innerprod

./yao-player.x -p 0 xtabs &
./yao-player.x -p 1 xtabs | grep 'expected 6, got 6' || exit 1

for i in mult3 innerprod xtabs; do
    ./compile.py -p 128 $i || exit 1
done

for i in 0 1; do
    ./spdz2-offline.x -p $i -N 3 -m &
done
./spdz2-offline.x -p 2 -N 3 -m || exit 1

mkdir Programs/InputData
printf "1\n14\n8\n" > Programs/InputData/mult3.P0 
printf "1\n12\n" > Programs/InputData/mult3.P1 
printf "0\n" > Programs/InputData/mult3.P2

for i in 0 1 2; do
    ./gen_input_fp.x -N 3 -i ./Programs/InputData/mult3.P$i -o ./Player-Data/Private-Input-$i
done

./Server.x 3 5000 &
./Player-Online.x 0 mult3 | grep 1344 || exit 1 &
./Player-Online.x 1 mult3 & ./Player-Online.x 2 mult3

for i in 0 1; do
    ./gen_input_fp.x -N 3 -i ./Programs/Source/xtabs.P$i -o ./Player-Data/Private-Input-$i
done

./Server.x 3 5000 &
./Player-Online.x 0 innerprod || exit 1
./Player-Online.x 1 inneprod & ./Player-Online.x 2 innerprod

./Server.x 3 5000 &
./Player-Online.x 0 xtabs | grep 'expected 6, got 6' || exit 1 &
./Player-Online.x 1 xtabs & ./Player-Online.x 2 xtabs
