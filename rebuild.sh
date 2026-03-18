#!/bin/bash

BUILD_DIR="build/"

mkdir -p $BUILD_DIR
cd $BUILD_DIR

cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

echo "--- Cleaning build directory"
cmake --build . --target clean

echo "--- Building project ---"
cmake --build .
