cmake_minimum_required(VERSION 3.15)
project(CCollections VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -g")

include_directories(include)

# 1. Core Library Target
file(GLOB_RECURSE LIB_SOURCES "src/*.c")
add_library(ccollections SHARED ${LIB_SOURCES})

# Enable Testing Suite Automation
enable_testing()

# 2. Target A: Unity Unit Tests Binary
# This target explicitly links the Unity framework to your concrete arraylist tests
add_executable(run_tests 
    tests/test_arraylist.c 
    tests/vendor/unity/unity.c
)
target_link_libraries(run_tests ccollections)
add_test(NAME CoreTests COMMAND run_tests)

# 3. Target B: Performance Benchmark Tool Binary
# This keeps the benchmarking tool isolated with its own main() execution path
add_executable(benchmark_lists 
    tests/benchmark_lists.c
)
target_link_libraries(benchmark_lists ccollections)
# Add this block after the 'add_executable(run_tests ...)' section
target_include_directories(run_tests PRIVATE 
    include 
    tests/vendor/unity
)
