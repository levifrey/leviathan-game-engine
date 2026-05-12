#!/bin/bash
rm -rf build
<<<<<<< HEAD:make.sh
cmake -S . -B build
cmake --build build
=======
>>>>>>> assimp:build.sh
rm compile_commands.json
cmake -S . -B build
cmake --build build
ln -s compile_commands.json .

