cmake_minimum_required(VERSION 3.26)
project(ShardKV LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS_ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE debug)
endif()

# Process Abseil's CMake build system
add_subdirectory(src/abseil-cpp)

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
    src/main.cc
    src/client/CLI/command_line_interface.cc
    src/client/CLI/InputParser/input_parser.cc
    src/server/HashTable/hash_table.cc
    src/server/Core/core.cc
)

add_executable(ShardKV_tests
    src/client/CLI/command_line_interface.cc
    src/client/CLI/InputParser/input_parser.cc
    tests/CLI/test_input_parser.cc
    tests/CLI/test_cli.cc
    tests/HashTable/test_hash_table.cc
)

target_link_libraries(${PROJECT_NAME} PRIVATE absl::hash)
target_link_libraries(ShardKV_tests PRIVATE gtest_main absl::hash)
gtest_discover_tests(ShardKV_tests)
