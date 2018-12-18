#!/bin/bash

# Install mpir
wget http://mpir.org/mpir-3.0.0.tar.bz2
tar -xjf mpir-3.0.0.tar.bz2
rm mpir-3.0.0.tar.bz2
cd mpir-3.0.0/
./configure --enable-cxx
make
make install
cd ..

# Linking
LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/usr/local/lib
ldconfig

# Compile SPDZ with secure pre-processing
git clone https://github.com/n1analytics/MP-SPDZ
cd MP-SPDZ
git checkout f0e02f2
echo USE_NTL = 1 >> CONFIG.mine
echo USE_GF2N_LONG = 0 >> CONFIG.mine
echo MOD = -DMAX_MOD_SZ=6 >> CONFIG.mine
echo ARCH = -march=native >> CONFIG.mine

make
mkdir Player-Data
Scripts/setup-ssl.sh
