#!/bin/bash

# get readme scripts
git clone https://github.com/emp-toolkit/emp-readme.git

# install tools
bash ./emp-readme/scripts/install_packages.sh
apt-get install -y libboost-{chrono,log,program-options,date-time,thread,system,filesystem,regex,test}1.58-dev

bash ./emp-readme/scripts/install_relic.sh
bash ./emp-readme/scripts/install_emp-tool.sh
bash ./emp-readme/scripts/install_emp-ot.sh

# install semi-honest 2-party circuits and malicious 2-party circuits
git clone https://github.com/emp-toolkit/emp-sh2pc.git
git clone https://github.com/emp-toolkit/emp-ag2pc.git

# add our files to compile scripts
mv source/mult3.ag2pc.cpp emp-ag2pc/test/
echo "add_test (mult3.ag2pc)" >> emp-ag2pc/CMakeLists.txt
mv source/* emp-sh2pc/test/
cd emp-sh2pc
mv test/geninput.py .
echo "add_test (mult3)" >> CMakeLists.txt
echo "add_test (innerprod)" >> CMakeLists.txt
echo "add_test (xtabs)" >> CMakeLists.txt

# build semi-honest 
mkdir build
cd build
cmake ..
make
make install

# build malicious
cd /root/emp-ag2pc
mkdir build
cd build
cmake ..
make 
