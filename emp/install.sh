#!/bin/bash

set -e

wget https://raw.githubusercontent.com/emp-toolkit/emp-readme/master/scripts/install.py
# We don't set "-install" because our docker image already comes with the necessary dependencies.
# See: https://github.com/emp-toolkit/emp-readme/blob/master/scripts/install.py#L12
python3 install.py -install --tool --ot --sh2pc --ag2pc
