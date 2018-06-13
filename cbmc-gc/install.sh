
# download source
wget https://www.seceng.informatik.tu-darmstadt.de/assets/software/cbmc-gc-v2.0alpha.tgz
tar zxvf cbmc-gc-v2.0alpha.tgz 
rm cbmc-gc-v2.0alpha.tgz

# make and install cmbc-gc executables
cd cbmc-gc
make minisat2-download
make

cp bin/cbmc* /usr/bin/
cp bin/circuit* /usr/bin/

# copy our source
cp -r ~/source/* examples/
