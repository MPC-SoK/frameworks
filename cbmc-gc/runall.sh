#!/bin/sh

set -ex

examples="mult3 innerprod xtabs" # xtabs-hash takes >1h to compile
trials=10

cd examples

for ex in $examples; do
    python3 geninput.py -e "$ex" -t "$trials"
    cd "$ex"
    make
    make run-sim | grep -q failed && exit 1
    cd ..
done

echo "Successfully ran all examples"