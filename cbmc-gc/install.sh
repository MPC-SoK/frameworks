#!/bin/sh

set -ex

# download source
git clone https://gitlab.com/securityengineering/CBMC-GC-2.git
cd CBMC-GC-2
git checkout -b MPCSOK e57333b19484

# make and install cmbc-gc executables
make minisat2-download
make

cp bin/cbmc* /usr/bin/
cp bin/circuit* /usr/bin/


