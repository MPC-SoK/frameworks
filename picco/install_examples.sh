#!/bin/sh

set -ex

# compile our tests
mkdir /root/tests
cp /root/source/geninput.py /root/tests/
cp /root/source/run_example.sh /root/tests/

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

rm -rf /root/source