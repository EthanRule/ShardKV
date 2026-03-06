cmake_minimum_required(VERSION 3.26)
project(ShardKV LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

include(FetchContent)
cmake_policy(SET CMP0135 NEW)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY "https://github.com/google/googletest.git"
  GIT_TAG        v1.16.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/CLI/command_line_interface.cpp
    src/CLI/InputParser/input_parser.cpp
)

add_executable(ShardKV_tests
    src/CLI/command_line_interface.cpp
    src/CLI/InputParser/input_parser.cpp
    tests/CLI/test_input_parser.cpp
    tests/CLI/test_cli.cpp
)

target_link_libraries(ShardKV_tests PRIVATE gtest_main)
gtest_discover_tests(ShardKV_tests)
