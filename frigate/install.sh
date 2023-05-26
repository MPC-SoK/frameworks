set -ex


# install bison dependencies
#wget http://ftp.br.debian.org/debian/pool/main/b/bison/libbison-dev_3.6.3+dfsg-1_amd64.deb
#dpkg -i libbison-dev_3.6.3+dfsg-1_amd64.deb
#
#wget http://ftp.br.debian.org/debian/pool/main/b/bison/bison_3.6.3+dfsg-1_amd64.deb
#dpkg -i bison_3.6.3+dfsg-1_amd64.deb
#
#rm libbison-dev_3.6.3+dfsg-1_amd64.deb
#rm bison_3.6.3+dfsg-1_amd64.deb

# install frigate
git clone https://bitbucket.org/bmood/frigaterelease.git
cd frigaterelease/src

make
cp frigate /bin/

# add a vim syntax file :)
cd
mkdir -p .vim/syntax
mv source/frigate.vim .vim/syntax
mkdir .vim/ftdetect
cd .vim/ftdetect
echo "au BufNewFile,BufRead *.wir set filetype=frigate" > frigate.vim

# install Semi-Honest-BMR
cd
git clone https://github.com/cryptobiu/Semi-Honest-BMR
cd Semi-Honest-BMR
bash build
