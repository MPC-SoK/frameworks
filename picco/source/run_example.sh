#!/bin/sh

set -ex

EX=$1

EXPECTED=$(python3 geninput.py -e $EX -n 10)

cd $EX
picco $EX.c smc_config $EX utility_config

if [ $EX = "mult3" ]; then
    NO_INPUT_PARTIES=1

    picco-utility -I 1 data/input.A.dat utility_config secure_server/share

    make

    cd secure_server
    ./$EX 3 ../run_config keys/private3.pem $NO_INPUT_PARTIES 1 share3 output &
    sleep 2
    ./$EX 2 ../run_config keys/private2.pem $NO_INPUT_PARTIES 1 share2 output &
    sleep 2
    ./$EX 1 ../run_config keys/private1.pem $NO_INPUT_PARTIES 1 share1 output &
    sleep 2

elif [ $EX = "innerprod" ]; then
    NO_INPUT_PARTIES=2
    picco-utility -I 1 data/input.A.dat utility_config secure_server/shareA
    picco-utility -I 2 data/input.B.dat utility_config secure_server/shareB

    make

    cd secure_server
    ./$EX 3 ../run_config keys/private3.pem $NO_INPUT_PARTIES 1 shareA3 shareB3 output &
    sleep 2
    ./$EX 2 ../run_config keys/private2.pem $NO_INPUT_PARTIES 1 shareA2 shareB2 output &
    sleep 2
    ./$EX 1 ../run_config keys/private1.pem $NO_INPUT_PARTIES 1 shareA1 shareB1 output &
    sleep 2
else
    echo unimplemented
fi


picco-seed ../run_config ../utility_config
sleep 10

picco-utility -O 1 output ../utility_config result
cat result
echo "$EXPECTED"