#!/bin/bash
#!/bin/bash

wget https://raw.githubusercontent.com/emp-toolkit/emp-readme/master/scripts/install.py
python install.py -install -tool -ot -sh2pc -ag2pc
cd sh_test && cmake . && make && cd ..
cd ag_test && cmake . && make && cd ..
