#!/bin/bash
rm -rf build
mkdir build
cd build
cmake ..
make
rm compile_commands.json
ln -s compile_commands.json .
cd ..

