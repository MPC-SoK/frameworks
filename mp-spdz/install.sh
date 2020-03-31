#!/bin/bash

curl -L https://github.com/data61/MP-SPDZ/releases/download/v0.1.5/mp-spdz-0.1.5.tar.xz | tar xJv
mv mp-spdz-0.1.5 MP-SPDZ

cd MP-SPDZ
Scripts/tldr.sh
