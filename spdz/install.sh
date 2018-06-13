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

# Install libsodium
wget https://github.com/jedisct1/libsodium/releases/download/1.0.16/libsodium-1.0.16.tar.gz
tar -xf libsodium-1.0.16.tar.gz
rm libsodium-1.0.16.tar.gz 
cd libsodium-1.0.16/  
./configure
make
make install
cd ..

# Install NTL (needed by SPDZ-2)
wget http://www.shoup.net/ntl/ntl-10.5.0.tar.gz
tar -xf ntl-10.5.0.tar.gz
rm ntl-10.5.0.tar.gz
cd ntl-10.5.0/src/
./configure
make
make install
cd ../..

# Linking
LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/usr/local/lib
ldconfig

# Compile SPDZ with secure pre-processing
git clone https://github.com/bristolcrypto/SPDZ-2 
cd SPDZ-2
echo USE_NTL = 1 >> CONFIG.mine
echo MOD = -DMAX_MOD_SZ=6 >> CONFIG.mine
echo ARCH = -march=native >> CONFIG.mine

make
mkdir Player-Data



