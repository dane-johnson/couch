#!/usr/bin/env bash

set -e
cd `dirname $0`

mkdir -p dist

## Linux build

mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
rm -f couch-linux.tgz
tar cvzf couch-linux.tgz \
    couch \
    CORRESPONDINGSOURCE.txt \
    LICENSE
mv couch-linux.tgz ../dist
cd ..

## Windows build
mkdir -p build-win
cd build-win
x86_64-w64-mingw32-cmake -DCMAKE_BUILD_TYPE=Release ..
make
rm -rf couch-win.zip
cp ../binaries/*.dll .
zip couch-win.zip \
    couch.exe \
    CORRESPONDINGSOURCE.txt \
    LICENSE \
    *.dll
mv couch-win.zip ../dist
cd ..

## Source packages
git archive -o dist/couch-source.tgz master
git archive -o dist/couch-source.zip master
