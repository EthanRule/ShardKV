#!/bin/bash

BUILD_DIR="build/"

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

echo "--- Building hash table dev ---"
cmake --build . --target hashtable_dev 2>&1

if [ $? -eq 0 ]; then
    echo "--- Running ---"
    ./hashtable_dev
else
    echo "--- Build failed ---"
fi
