#!/bin/bash

set -ex

# Compile SPDZ with secure pre-processing
git clone https://github.com/bristolcrypto/SPDZ-2 
cd SPDZ-2
git checkout v0.0.3
echo USE_NTL = 1 >> CONFIG.mine
echo MOD = -DMAX_MOD_SZ=6 >> CONFIG.mine
echo ARCH = -march=native >> CONFIG.mine
sed -i s/-Werror//g CONFIG # needed because recent versions of gcc cannot compile SPDZ w/o warnings.
sed -i s/python/python2/g compile.py # The command is now called "python2" instead of "python".

make
mkdir Player-Data



