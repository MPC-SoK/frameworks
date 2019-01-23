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

./replicated-bin-party.x -p 1 mult3 &
./replicated-bin-party.x -p 2 mult3 &
./replicated-bin-party.x -p 0 mult3 | grep 1344 || exit 1

for i in 0 1; do
    cp Programs/Source/xtabs.Input-P$i-0 Player-Data/Input-P$i-0
done

./yao-player.x -p 0 innerprod &
./yao-player.x -p 1 innerprod

./yao-player.x -p 0 xtabs &
./yao-player.x -p 1 xtabs | grep 'expected 6, got 6' || exit 1

./replicated-bin-party.x -p 0 innerprod &
./replicated-bin-party.x -p 1 innerprod &
./replicated-bin-party.x -p 2 innerprod

./replicated-bin-party.x -p 1 xtabs &
./replicated-bin-party.x -p 2 xtabs &
./replicated-bin-party.x -p 0 xtabs | grep 'expected 6, got 6' || exit 1

for i in mult3 innerprod xtabs; do
    ./compile.py -p 128 $i || exit 1
done

echo 14 8 > Player-Data/Input-P0-0
echo 12 > Player-Data/Input-P1-0

./malicious-rep-field-party.x 1 mult3 & ./malicious-rep-field-party.x 2 mult3 &
./malicious-rep-field-party.x 0 mult3 | grep 1344 || exit 1

for i in 0 1; do
    cp Programs/Source/xtabs.Input-P$i-0 Player-Data/Input-P$i-0
done

./malicious-rep-field-party.x 1 innerprod & ./malicious-rep-field-party.x 2 innerprod &
./malicious-rep-field-party.x 0 innerprod || exit 1

./malicious-rep-field-party.x 1 xtabs & ./malicious-rep-field-party.x 2 xtabs &
./malicious-rep-field-party.x 0 xtabs | grep 'expected 6, got 6' || exit 1

for i in 0 1; do
    ./spdz2-offline.x -p $i -N 3 -m &
done
./spdz2-offline.x -p 2 -N 3 -m || exit 1

echo 14 8 > Player-Data/Input-P0-0
echo 12 > Player-Data/Input-P1-0

./Server.x 3 5000 &
./Player-Online.x 1 mult3 & ./Player-Online.x 2 mult3 &
./Player-Online.x 0 mult3 | grep 1344 || exit 1

for i in 0 1; do
    cp Programs/Source/xtabs.Input-P$i-0 Player-Data/Input-P$i-0
done

./Server.x 3 5000 &
./Player-Online.x 1 innerprod & ./Player-Online.x 2 innerprod &
./Player-Online.x 0 innerprod || exit 1

./Server.x 3 5000 &
./Player-Online.x 1 xtabs & ./Player-Online.x 2 xtabs &
./Player-Online.x 0 xtabs | grep 'expected 6, got 6' || exit 1
