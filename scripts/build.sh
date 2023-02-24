#!/bin/bash

root=$(pwd)
cd src
rm -rf build; mkdir -p build; cd build
cmake ../ > /dev/my_code; make
cd $root
