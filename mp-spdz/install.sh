#!/bin/bash

set -ex

MP_SPDZ_VERSION="v0.3.6"

git clone https://github.com/data61/MP-SPDZ.git
cd MP-SPDZ
git checkout $MP_SPDZ_VERSION

make setup
make mascot-party.x 
# The above line can be replaced with `make all` in order get access
# to all MPC protocols implemented by MP-SPDZ. However, compilation of
# all protocols takes a long time.