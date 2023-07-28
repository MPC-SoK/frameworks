#!/bin/sh

set -ex

# get MOTION
git clone https://github.com/encryptogroup/MOTION.git
cd MOTION
git checkout 1e082c9 

# build MOTION
mkdir build && cd build
cmake ..
make -j4
