#!/bin/bash

curl -L https://github.com/n1analytics/MP-SPDZ/releases/download/v0.0.8/mp-spdz-0.0.8.tar.gz | tar xzv
mv mp-spdz-0.0.8 MP-SPDZ

cd MP-SPDZ
Scripts/tldr.sh
