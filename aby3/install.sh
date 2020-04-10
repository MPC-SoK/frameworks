# download aby3
cd ~
git clone https://github.com/ladnir/aby3.git
cd aby3
git checkout -b MPCSOK 4d17c6476135723a2ed3d596dbba1709d0c6b4ae
cd thirdparty/linux
bash eigen.get
bash function2.get

# put our files in place
cd ~/aby3/
mkdir samples 
mv ~/source/* samples
printf "add_subdirectory(samples)\n" >> CMakeLists.txt

# build entire library
cmake .
make -j

