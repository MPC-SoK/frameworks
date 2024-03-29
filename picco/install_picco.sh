#!/bin/sh

set -ex

# download
git clone https://github.com/applied-crypto-lab/picco
cd picco
git checkout aa2e71e7f8a0f7a313ac76a1ab3639e95637cd31 # Latest as of 27 October 2023

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
