
tar xvf node-v10.15.3-linux-x64.tar.xz
cd node-v10.15.3-linux-x64
for DIR in bin include lib share; do
  cp -r ./$DIR/* /usr/$DIR/
done


