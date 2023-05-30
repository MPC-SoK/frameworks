#!/bin/sh

set -ex

EX=$1

./run-compiler.sh 1234 examples/$EX/$EX.lcc

python3 ./genInput.py -i examples/$EX/human_input_alice.txt -o examples/$EX/input_alice.txt
python3 ./genInput.py -i examples/$EX/human_input_bob.txt -o examples/$EX/input_bob.txt

./runtogether.sh examples/$EX/input_alice.txt examples/$EX/input_bob.txt