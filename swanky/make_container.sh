#!/usr/bin/bash            

echo "Making swanky"

cntr=$(buildah from fedora)

echo "Installing tools"

buildah run $cntr dnf install -y git rust cargo

echo "Getting code"

buildah run $cntr git clone https://github.com/GaloisInc/swanky /root/swanky

echo "Compiling"

buildah run $cntr /bin/sh -c 'cd /root/swanky; cargo build --release --examples'

echo "Saving container"

buildah commit $cntr swanky

buildah rm $cntr

