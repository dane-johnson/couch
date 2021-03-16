#!/bin/bash

set -e
cd `dirname $0`

mkdir -p build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
make
cd ..

mkdir -p build-win/
cd build-win
x86_64-w64-mingw32-cmake ..
make
cd ..

echo "All builds successful"
