#!/bin/sh

set -ex

# Install mpir
wget https://github.com/wbhart/mpir/archive/refs/tags/mpir-3.0.0.tar.gz
tar -xvzf mpir-3.0.0.tar.gz
rm mpir-3.0.0.tar.gz
cd mpir-mpir-3.0.0
./autogen.sh
autoreconf -i
./configure --enable-cxx
make
make check
make install
ldconfig
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
