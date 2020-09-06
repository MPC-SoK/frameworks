#!/bin/bash

wget https://raw.githubusercontent.com/emp-toolkit/emp-readme/master/scripts/install.py
python install.py -install -tool -ot -sh2pc -ag2pc

# add our files to compile scripts
cp source/* emp-sh2pc/test/
cd emp-sh2pc
mv test/geninput.py .
echo "add_test (mult3)" >> CMakeLists.txt
echo "add_test (innerprod)" >> CMakeLists.txt
echo "add_test (xtabs)" >> CMakeLists.txt

# build project
mkdir build
cd build
cmake ..
make
make install

#Generate mult3 circuit
./bin/mult3 -m
mv mult3.circuit.txt /usr/local/include/emp-tool/circuits/files/

cd emp-ag2pc
echo "add_test (agmult3)" >> CMakeLists.txt
mv ../emp-sh2pc/test/agmult3.cpp test/agmult3.cpp
mkdir build
cd build
cmake ..
make 
