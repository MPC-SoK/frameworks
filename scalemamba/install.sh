#frigate install supporting mpir library
wget http://mpir.org/mpir-3.0.0.tar.bz2
tar -xvf mpir-3.0.0.tar.bz2
rm mpir-3.0.0.tar.bz2
cd mpir-3.0.0
./configure --enable-cxx
make install
cp .libs/* /usr/lib64/

# install openssl from source because apparently apt's version is not good
# enough
cd
wget https://www.openssl.org/source/openssl-1.1.0h.tar.gz
tar -xvf openssl-1.1.0h.tar.gz
rm openssl-1.1.0h.tar.gz
cd openssl-1.1.0h
./config
make
make install
ldconfig 

# download SCALE-MAMBA
cd 
git clone https://github.com/KULeuven-COSIC/SCALE-MAMBA.git
cd SCALE-MAMBA
git checkout -b MPCSOK e05c19e
cp /root/source/CONFIG.mine .
make progs

# set up certificate authority
SUBJ="/CN=www.example.com"
cd Cert-Store

openssl genrsa -out RootCA.key 4096
openssl req -new -x509 -days 1826 -key RootCA.key \
           -subj $SUBJ -out RootCA.crt

# make 4 certificates. More can be added as necessary
mkdir csr
for ID in {0..3}
do
  SUBJ="/CN=player$ID@example.com"
  openssl genrsa -out Player$ID.key 2048
  openssl req -new -key Player$ID.key -subj $SUBJ -out csr/Player$ID.csr
  openssl x509 -req -days 1000 -set_serial 101$ID \
    -CA RootCA.crt -CAkey RootCA.key \
    -in csr/Player$ID.csr -out Player$ID.crt 
done

# copy examples to correct locations
cd /root/SCALE-MAMBA
for EX in mult3 innerprod xtabs
do
  mkdir Programs/$EX
  cp /root/source/$EX.mpc Programs/$EX/
done

# add simple syntax highlighting
cd
mkdir -p .vim/syntax
mv source/mamba.vim .vim/syntax
mkdir .vim/ftdetect
cd .vim/ftdetect
echo "au BufNewFile,BufRead *.wir set filetype=mamba" > mamba.vim
