#!/bin/sh

set -ex

CONTAINERS=$@

if [ -z "$CONTAINERS" ]; then  
    echo "Nothing to do!"
    exit 0
fi

for dirname in $CONTAINERS; do
    echo "building container from directory $dirname"
    cd "$dirname"
    docker build . --tag "$dirname"
    cd ..
done