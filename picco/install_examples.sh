#!/bin/sh

set -ex

for DIR in mult3 innerprod xtabs; do
  cd /root/source/$DIR
  mkdir secure_server

  # link to shared resources
  ln -s /root/keys secure_server/keys 
  ln -s /root/picco/compute/smc-compute smc-compute
  picco $DIR.c smc_config $DIR utility_config
  make -j
done
