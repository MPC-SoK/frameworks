#!/bin/bash

# install latest cmake
wget https://cmake.org/files/v3.12/cmake-3.12.3-Linux-x86_64.sh
bash cmake-3.12.3-Linux-x86_64.sh --include-subdir --skip-license
cp cmake-3.12.3-Linux-x86_64/bin/* /usr/bin
cp -r cmake-3.12.3-Linux-x86_64/share/* /usr/share/
rm -r cmake*

# get ABY
git clone --recursive https://github.com/encryptogroup/ABY.git
cd ABY
#git reset --hard abd5b3ffe0681aa9df69969c4adc3e51804b542b

# copy our working examples 
for EX in mult3 crosstabs # innerprod
do
  cp -r ~/source/$EX src/examples/
  echo 'add_subdirectory('$EX')' >> src/examples/CMakeLists.txt
done

cp ~/source/geninput.py src/examples/

# build ABY
mkdir build 
cd build
cmake -DABY_BUILD_EXE=On ..
make 

