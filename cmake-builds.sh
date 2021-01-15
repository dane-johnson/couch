#!/bin/bash

set -e

mkdir -p build
cd build
cmake ..
make
cd ..

mkdir -p build-win/
cd build-win
x86_64-w64-mingw32-cmake ..
make
cd ..

echo "All builds successful"
