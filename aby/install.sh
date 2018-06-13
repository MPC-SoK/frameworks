#!/bin/bash

# build ABY
git clone --recursive https://github.com/encryptogroup/ABY.git
cd ABY
make

# copy our working examples and rename conflict
cp -r ~/source/mult3 src/examples/
cp -r ~/source/innerprod src/examples/
cp ~/source/geninput.py src/examples/
mv src/examples/innerproduct src/examples/innerproduct_ABY

