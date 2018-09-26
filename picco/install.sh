# download + update with our minor fixes
git clone https://github.com/PICCO-Team/picco.git
cd picco
git checkout ee85c91 
cp ../source/picco.patch picco/
patch -p1 -i picco.patch

# install 
cd compiler
mkdir bin
./compile.sh
cp bin/* /usr/bin

# generate keys
mkdir /root/keys
cd /root/keys
for ID in {1..3}
do
  openssl genrsa -out private$ID.pem
  openssl rsa -in private$ID.pem -outform PEM -pubout -out pubkey$ID.pem
done

# compile our tests
mkdir /root/tests
cp /root/source/geninput.py /root/tests/

for DIR in mult3 innerprod xtabs
do
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

