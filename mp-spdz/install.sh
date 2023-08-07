#!/bin/bash

set -ex

fromsource=$1
MP_SPDZ_VERSION="0.3.6"

if [ $fromsource = "yes" ]; then
    # this may take a long time
    git clone https://github.com/data61/MP-SPDZ.git
    cd MP-SPDZ
    git checkout v$MP_SPDZ_VERSION

    make setup
    make all
else
    curl -L https://github.com/data61/MP-SPDZ/releases/download/v$MP_SPDZ_VERSION/mp-spdz-$MP_SPDZ_VERSION.tar.xz | tar xJv
    mv mp-spdz-$MP_SPDZ_VERSION MP-SPDZ
    cd MP-SPDZ
    Scripts/tldr.sh
fi