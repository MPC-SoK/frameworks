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
