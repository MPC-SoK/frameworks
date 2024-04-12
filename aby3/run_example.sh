#!/bin/sh

set -ex

SAMPLE=$1

BIN=out/build/linux/samples/samples.exe

if [ $SAMPLE = mult3 -o $SAMPLE = innerprod -o $SAMPLE = xtabs ]; then
    $BIN -p 0 -u $SAMPLE & 
    $BIN -p 1 -u $SAMPLE & 
    $BIN -p 2 -u $SAMPLE
else
    echo "Bad sample name. Supported samples: mult3, innerprod, xtabs"
    exit 1
fi
