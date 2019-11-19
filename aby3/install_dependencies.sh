alias wget="wget -nv"
wget https://github.com/Kitware/CMake/releases/download/v3.16.0-rc4/cmake-3.16.0-rc4-Linux-x86_64.tar.gz
tar xzvf cmake-3.16.0-rc4-Linux-x86_64.tar.gz
cd cmake-3.16.0-rc4-Linux-x86_64
mv bin/* /usr/bin/
cp -r share/* /usr/share/

cd
git clone --recursive https://github.com/osu-crypto/libOTe.git
cd libOTe/cryptoTools/thirdparty/linux
bash boost.get
bash miracl.get
cd ../../..
cmake -DENABLE_CIRCUITS=ON -DENABLE_SIMPLESTOT=ON .
make -j
