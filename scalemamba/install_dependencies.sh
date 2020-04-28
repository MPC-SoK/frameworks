# install supporting mpir library
wget http://mpir.org/mpir-3.0.0.tar.bz2
tar -xvf mpir-3.0.0.tar.bz2
rm mpir-3.0.0.tar.bz2
cd mpir-3.0.0
./configure --enable-cxx
make
make check
make install

curl -sSf sh.rustup.rs | sh -s -- -y