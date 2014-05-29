#!/bin/sh

if [ ! -d build/ ]; then
  mkdir build
  cd build
  cmake .. -DCMAKE_INSTALL_PREFIX=$PREFIX -DCMAKE_BUILD_TYPE=Debug
  make -j4
else
  cd build
  make -j4
fi
