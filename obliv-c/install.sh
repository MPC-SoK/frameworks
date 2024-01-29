#!/bin/sh

set -ex

git clone https://github.com/samee/obliv-c

cd obliv-c
git checkout -b MPCSOK e02e5c590523ef4dae06e167a7fa00037bb3fdaf

./configure && make
