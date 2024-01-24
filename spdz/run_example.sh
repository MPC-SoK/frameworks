#!/bin/sh

set -e

EX=$1

mkdir -p Programs/InputData

if [ $EX = mult3 ]; then
    ./compile.py -p 128 $EX
    printf "1\n14\n" > Programs/InputData/$EX.P0
    printf "1\n12\n" > Programs/InputData/$EX.P1
    printf "1\n8\n" > Programs/InputData/$EX.P2
    ./gen_input_fp.x -N 3 -i ./Programs/InputData/$EX.P0 -o ./Player-Data/Private-Input-0
    ./gen_input_fp.x -N 3 -i ./Programs/InputData/$EX.P1 -o ./Player-Data/Private-Input-1
    ./gen_input_fp.x -N 3 -i ./Programs/InputData/$EX.P2 -o ./Player-Data/Private-Input-2

    ./Server.x 3 5000 &
    ./Player-Online.x 0 $EX & ./Player-Online.x 1 $EX & ./Player-Online.x 2 $EX

elif [ $EX = innerprod ]; then
    # This example is currently not working. For unknown reasons, it produces wrong outputs.
    ./compile.py -p 128 $EX
    printf "1\n14\n10\n5\n" > Programs/InputData/$EX.P0
    printf "1\n12\n64\n3\n" > Programs/InputData/$EX.P1
    ./gen_input_fp.x -N 2 -i ./Programs/InputData/$EX.P0 -o ./Player-Data/Private-Input-0
    ./gen_input_fp.x -N 2 -i ./Programs/InputData/$EX.P1 -o ./Player-Data/Private-Input-1

    ./Server.x 2 5000 &
    ./Player-Online.x 0 $EX & ./Player-Online.x 1 $EX

elif [ $EX = xtabs ]; then
    ./compile.py -p 128 $EX
    ./gen_input_fp.x -N 2 -i ./Programs/InputData/$EX.P0 -o ./Player-Data/Private-Input-0
    ./gen_input_fp.x -N 2 -i ./Programs/InputData/$EX.P1 -o ./Player-Data/Private-Input-1

    ./Server.x 2 5000 &
    ./Player-Online.x 0 $EX & ./Player-Online.x 1 $EX

fi
