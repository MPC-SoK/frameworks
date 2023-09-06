set -ex

# install supporting mpir library
wget https://github.com/wbhart/mpir/archive/refs/tags/mpir-3.0.0.tar.gz
tar -xvzf mpir-3.0.0.tar.gz
rm mpir-3.0.0.tar.gz
cd mpir-mpir-3.0.0
./autogen.sh
./configure --enable-cxx
make
make check
make install
ldconfig

cd
curl https://sh.rustup.rs -sSf | sh -s -- -y
