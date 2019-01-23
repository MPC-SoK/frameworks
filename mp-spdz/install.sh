#!/bin/bash

# Compile SPDZ with secure pre-processing
git clone https://github.com/n1analytics/MP-SPDZ
cd MP-SPDZ
git checkout -b MPCSOK 4092d61
echo USE_NTL = 1 >> CONFIG.mine
echo USE_GF2N_LONG = 0 >> CONFIG.mine
echo MOD = -DMAX_MOD_SZ=6 >> CONFIG.mine
echo ARCH = -march=native >> CONFIG.mine

make mpir || exit 1
make || exit 1
mkdir Player-Data
Scripts/setup-ssl.sh

# Linking
LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/usr/local/lib
ldconfig
