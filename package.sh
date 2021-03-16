#!/usr/bin/env bash

set -e
cd `dirname $0`

mkdir -p dist

mkdir -p build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
rm -f couch-linux.tgz
tar cvzf couch-linux.tgz \
    couch \
    CORRESPONDINGSOURCE.txt \
    LICENSE
mv couch-linux.tgz ../dist

