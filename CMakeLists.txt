cmake_minimum_required(VERSION 3.26)
project(ShardKV LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

include(FetchContent)

# Set the policy to ensure NEW behavior for FetchContent (prevents some parsing bugs)
cmake_policy(SET CMP0135 NEW)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY "https://github.com/google/googletest.git"
  GIT_TAG        v1.16.0
)
FetchContent_MakeAvailable(googletest)

# Source files to preprocess compile and link
set(SOURCE_FILES
    src/main.cpp
    src/CLI/command_line_interface.cpp
    src/CLI/InputParser/input_parser.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE gtest_main)
