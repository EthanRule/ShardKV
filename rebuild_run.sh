# This script was AI generated via the base google search engine.

#!/bin/bash

BUILD_DIR="build/"
EXECUTABLE_NAME="exe"

mkdir -p $BUILD_DIR
cd $BUILD_DIR

cmake .. -G Ninja

echo "--- Cleaning build directory"
cmake --build . --target clean

echo "--- Building project ---"
cmake --build .

if [ $? -eq 0 ]; then
    echo "--- Running executable ---"
    ./$EXECUTABLE_NAME
else
    echo "--- Build failed, not running executable ---"
fi
