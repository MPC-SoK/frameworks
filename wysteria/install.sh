#!/bin/bash

# download source
wget https://bitbucket.org/aseemr/wysteria/get/a0ef9b69b465.zip
unzip a0ef9b69b465.zip
mv aseemr-wysteria-a0ef9b69b465/ wysteria/
rm a0ef9b69b465.zip

# build/install z3
cd wysteria/z3
autoconf
./configure
python scripts/mk_make.py
cd build
make
make install

# build/install gmw
cd ../../gmw
make
cp mpc.exe /usr/bin

# build/install wysteria
cd ../src
sh make.sh
cp bin/wysteria /usr/bin/

# clean up unused scripts & files
rm -r bin
rm build.sh
rm killall.sh
rm racketport*
rm start_3*

# move our source code to a useful directory
cp ~/source/examples/mult3.wy ~/wysteria/src/examples
cp ~/source/scripts/*.sh ~/wysteria/src/

# add vim syntax
cd
mkdir -p .vim/syntax
mv source/scripts/wysteria.vim .vim/syntax
mkdir .vim/ftdetect
cd .vim/ftdetect
echo "au BufNewFile,BufRead *.wy set filetype=wysteria" > wysteria.vim
