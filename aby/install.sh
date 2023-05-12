#!/bin/sh

# get ABY
git clone --recursive https://github.com/encryptogroup/ABY.git
cd ABY
git checkout -b MPCSOK 08baa853de76a9070cb8ed8d41e96569776e4773

# copy our working examples 
for EX in mult3 crosstabs innerprod
do
  cp -r ~/source/$EX src/examples/
  echo 'add_subdirectory('$EX')' >> src/examples/CMakeLists.txt
done

cp ~/source/geninput.py src/examples/

# build ABY
mkdir build && cd build
cmake -DABY_BUILD_EXE=On ..
make 

