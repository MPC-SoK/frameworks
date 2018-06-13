# install proper cmake version
wget https://cmake.org/files/v3.11/cmake-3.11.0-Linux-x86_64.sh
sh cmake-3.11.0-Linux-x86_64.sh --skip-license --include-subdir
cp cmake-3.11.0-Linux-x86_64/bin/* /usr/bin/
cp -r cmake-3.11.0-Linux-x86_64/share/* /usr/share/
rm -r cmake-3.11*

# install sharemind sdk
git clone https://github.com/sharemind-sdk/build-sdk.git
cd build-sdk
git checkout tags/release_2017.12 
cp ~/source/config.local .
mkdir build
cd build
cmake ..
make
cp /root/build-sdk/prefix/bin/* /usr/bin/

# copy config files from VM setup into the expected location
CONFIG_DIR="/home/sharemind/.config/"
cd
git clone https://github.com/sharemind-sdk/packer-sharemind-sdk.git
cd packer-sharemind-sdk
git checkout tags/release_2017.12
mkdir -p $CONFIG_DIR
mv sharemind-sdk/files/sdk/sharemind-config/sharemind $CONFIG_DIR
cd 
rm -r packer-sharemind-sdk
ln -s $CONFIG_DIR .config


