#!/bin/bash

# get readme scripts
git clone https://github.com/emp-toolkit/emp-readme.git

# install tools
bash ./emp-readme/scripts/install_packages.sh
apt-get install -y libboost-{chrono,log,program-options,date-time,thread,system,filesystem,regex,test}1.58-dev

bash ./emp-readme/scripts/install_relic.sh
bash ./emp-readme/scripts/install_emp-tool.sh
bash ./emp-readme/scripts/install_emp-ot.sh

# install semi-honest 2-party circuits
git clone https://github.com/emp-toolkit/emp-sh2pc.git


# add our files to compile scripts
cp source/* emp-sh2pc/test/
cd emp-sh2pc
mv test/geninput.py .
echo "add_test (mult3)" >> CMakeLists.txt
echo "add_test (innerprod)" >> CMakeLists.txt
echo "add_test (xtabs)" >> CMakeLists.txt

# build project
mkdir build
cd build
cmake ..
make
make install

# install malicious 2-party circuits
cd
git clone https://github.com/emp-toolkit/emp-ag2pc.git
cd emp-ag2pc
mkdir build
cd build
cmake ..
make 
