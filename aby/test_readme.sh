#!/bin/sh

set -ex

# Test mult3 and innerprod, for which geninput.py can generate inputs
for ex in mult3 innerprod; do
    EXPECTED=$(python3 ABY/src/examples/geninput.py -e "$ex" | grep -Eo "[0-9]+")
    cd ABY/build
    ./bin/"$ex"_test -r 0 & 
    ACTUAL=$(./bin/"$ex"_test -r 1 | grep "Circuit Result:" | grep -Eo "[0-9]+")
    if [ "$ACTUAL" -ne "$EXPECTED" ]; then
        echo "$ex: Expected $EXPECTED but got $ACTUAL"
        exit 1
    fi
    cd ../..
done

# Test crosstabs

cd ABY/build
./bin/crosstabs_test -r 0 &
./bin/crosstabs_test -r 1 | grep "expect:" | while read -r OUT_LINE ; do
    BIN=$(echo "$OUT_LINE" | grep -Eo "[0-9]+" | sed '1q;d')
    ACTUAL=$(echo "$OUT_LINE" | grep -Eo "[0-9]+" | sed '2q;d')
    EXPECTED=$(echo "$OUT_LINE" | grep -Eo "[0-9]+" | sed '3q;d')
    if [ "$ACTUAL" -ne "$EXPECTED" ]; then
        echo "crosstabs: Bin $BIN: expected $EXPECTED but got $ACTUAL"
        exit 1
    fi
done
cd ../..