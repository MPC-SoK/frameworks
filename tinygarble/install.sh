
# make and install library
git clone https://github.com/esonghori/TinyGarble.git

cd TinyGarble
git reset --hard 3a2a610
./configure
cd bin
make

cp garbled_circuit/TinyGarble /bin/
cp garbled_circuit/

