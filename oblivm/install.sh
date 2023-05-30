#!/bin/sh

set -ex

git clone https://github.com/oblivm/ObliVMLang

cd ObliVMLang
git checkout -b MPCSOK 50ed0fbb556a157c0c85440dabf141a3cf7384c5

patch -p1 < ../real.patch

./compile.sh
