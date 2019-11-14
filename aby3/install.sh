git clone --recursive https://github.com/osu-crypto/libOTe.git
cd libOTe/cryptoTools/thirdparty/linux
bash boost.get
bash miracl.get
cd ../../..
cmake -DENABLE_CIRCUITS=ON -DENABLE_SIMPLESTOT=ON .
make -j
cd ../
git clone https://github.com/marsella/aby3.git
cd aby3
#git checkout -b MPCSOK e4e3f989327d2b937e3d21fbbe05a3ab56696e84
cd thirdparty/linux
bash eigen.get
bash function2.get
cd ../..
cmake .

