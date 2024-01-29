#!/bin/sh

set -ex

git clone https://github.com/ladnir/aby3.git
cd aby3/
git checkout 0849df6
python3 build.py --setup
python3 build.py

mkdir samples
printf "add_subdirectory(samples)\n" >> CMakeLists.txt
