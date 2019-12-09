
# get ABY
git clone --recursive https://github.com/encryptogroup/ABY.git
cd ABY

# build ABY
mkdir build && cd build
cmake -DABY_BUILD_EXE=On ..
make 
