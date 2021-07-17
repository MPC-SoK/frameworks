# install g++
apt-add-repository -y ppa:ubuntu-toolchain-r/test
apt-get update
apt-get install -y g++-10
ln -sf /usr/bin/g++-10 /usr/bin/g++
ln -sf /usr/bin/g++ /usr/bin/c++

# install cmake 3.19.5
wget https://cmake.org/files/v3.19/cmake-3.19.5-Linux-x86_64.sh
bash cmake-3.19.5-Linux-x86_64.sh --include-subdir --skip-license
cp cmake-3.19.5-Linux-x86_64/bin/* /usr/bin
cp -r cmake-3.19.5-Linux-x86_64/share/* /usr/share/
rm -r cmake*

# compile and install boost
wget -O boost_1_76_0.tar.bz2 https://boostorg.jfrog.io/artifactory/main/release/1.76.0/source/boost_1_76_0.tar.bz2
tar xjvf boost_1_76_0.tar.bz2
cd boost_1_76_0
./bootstrap.sh --prefix=/usr/local --with-libraries=context,fiber,filesystem,log,system,thread,program_options,json
./b2 install variant=release link=static,shared threading=multi -j 4 define=BOOST_LOG_USE_NATIVE_SYSLOG define=BOOST_ERROR_CODE_HEADER_ONLY
cd ..
rm -r boost_1_76_0 boost_1_76_0.tar.bz2
echo 'export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib' >> ~/.bashrc
