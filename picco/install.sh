#!/bin/sh

set -ex

# download
git clone https://github.com/applied-crypto-lab/picco
cd picco
git checkout 4518a90c91332e726484215814dfcccb0c537727 

# build and install 
cd compiler
mkdir bin
./compile.sh
cp bin/* /usr/bin

# generate keys
mkdir /root/keys
cd /root/keys
for ID in $(seq 1 3); do
  openssl genrsa -out private$ID.pem
  openssl rsa -in private$ID.pem -outform PEM -pubout -out pubkey$ID.pem
done

# compile our tests
mkdir /root/tests
cp /root/source/geninput.py /root/tests/

for DIR in mult3 innerprod xtabs; do
  cd
  cp -r source/$DIR tests/
  cd tests/$DIR
  mkdir secure_server
  mv run_config secure_server/
  # link to shared resources
  ln -s /root/keys secure_server/keys 
  ln -s /root/picco/compute/smc-compute smc-compute

  picco $DIR.c smc_config $DIR.gen util_config
  make $DIR
done 

