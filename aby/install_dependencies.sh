#!/bin/bash

# install gcc 8.3 and set up symlinks
apt-add-repository -y ppa:ubuntu-toolchain-r/test
apt-get update
apt-get install -y gcc-8 g++-8
ln -sf /usr/bin/gcc-8 /usr/bin/gcc
ln -sf /usr/bin/g++-8 /usr/bin/g++
ln -sf /usr/bin/gcc /usr/bin/cc
ln -sf /usr/bin/g++ /usr/bin/c++

# install latest cmake
wget https://cmake.org/files/v3.12/cmake-3.12.3-Linux-x86_64.sh
bash cmake-3.12.3-Linux-x86_64.sh --include-subdir --skip-license
cp cmake-3.12.3-Linux-x86_64/bin/* /usr/bin
cp -r cmake-3.12.3-Linux-x86_64/share/* /usr/share/
rm -r cmake*

# install latest boost 1.66
cd
wget https://dl.bintray.com/boostorg/release/1.66.0/source/boost_1_66_0.tar.bz2
tar xvjf boost_1_66_0.tar.bz2
rm boost_1_66_0.tar.bz2
rm -rf /usr/include/boost # remove older version if it's there
ln -sf /root/boost_1_66_0/boost /usr/include
cd boost_1_66_0
./bootstrap.sh
./bjam toolset=gcc --with-system --with-thread --with-chrono --with-date_time --with-atomic install

