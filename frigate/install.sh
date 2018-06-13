
# install bison dependencies
wget http://launchpadlibrarian.net/140087283/libbison-dev_2.7.1.dfsg-1_amd64.deb
dpkg -i libbison-dev_2.7.1.dfsg-1_amd64.deb

wget http://launchpadlibrarian.net/140087282/bison_2.7.1.dfsg-1_amd64.deb
dpkg -i bison_2.7.1.dfsg-1_amd64.deb

rm libbison-dev_2.7.1.dfsg-1_amd64.deb
rm bison_2.7.1.dfsg-1_amd64.deb

# install frigate
git clone https://bitbucket.org/bmood/frigaterelease.git
cd frigaterelease/src

make
cp frigate /bin/

# copy our examples
cp -r ~/source/* tests

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
