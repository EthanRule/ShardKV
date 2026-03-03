cmake_minimum_required(VERSION 3.26)
project(ShardKV LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

# Source files to preprocess compile and link
set(SOURCE_FILES
    src/main.cpp
    src/CLI/command_line_interface.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})