#!/bin/bash
rm -rf build
rm compile_commands.json
cmake -S . -B build
cmake --build build
ln -s compile_commands.json .
cd ..

