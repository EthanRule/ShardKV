#!/bin/bash

BUILD_DIR="build/"
# Ensure this matches your test executable name in CMakeLists.txt
TEST_EXECUTABLE="ShardKV_tests"

mkdir -p $BUILD_DIR
cd $BUILD_DIR

# 1. Configure
cmake .. -G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

if [ ! -L "../compile_commands.json" ]; then
    ln -s "$BUILD_DIR/compile_commands.json" "../compile_commands.json"
fi

# 2. Build (clean is optional, usually handled by Ninja)
echo "--- Building project & tests ---"
cmake --build .

if [ $? -eq 0 ]; then
    echo "--- Running Tests ---"
    # --output-on-failure: Shows GTest logs only if something fails
    # -j8: Runs tests in parallel (adjust based on your CPU cores)
    ctest --output-on-failure -j8
else
    echo "--- Build failed, not running tests ---"
    exit 1
fi
