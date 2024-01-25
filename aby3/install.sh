#!/bin/sh

set -ex

git clone https://github.com/gutjuri/aby3.git
cd aby3/
git checkout fix-build-script
python3 build.py --setup
python3 build.py
