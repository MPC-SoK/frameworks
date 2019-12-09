
# get ABY
git clone --recursive https://github.com/encryptogroup/ABY.git
cd ABY
git checkout -b MPCSOK 8aa003c2e145c6d43b6ec73ef75618be43951b1d

# build ABY
mkdir build && cd build
cmake -DABY_BUILD_EXE=On ..
make 
