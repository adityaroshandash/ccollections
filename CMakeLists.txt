cmake_minimum_required(VERSION 3.15)
project(CCollections VERSION 1.0.0 LANGUAGES C)

# Force strict C11 standard and error on warnings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -g")

# Include paths
include_directories(include)

# Define Core Shared/Static Library
file(GLOB_RECURSE LIB_SOURCES "src/*.c")
add_library(ccollections SHARED ${LIB_SOURCES})

# Target Unit Testing
enable_testing()
file(GLOB_RECURSE TEST_SOURCES "tests/*.c")
# Assuming Unity framework files are under tests/vendor/unity
add_executable(run_tests ${TEST_SOURCES} tests/vendor/unity/unity.c)
target_link_libraries(run_tests ccollections)
add_test(NAME CoreTests COMMAND run_tests)
# Add the benchmarking runtime target
add_executable(benchmark_lists tests/benchmark_lists.c)
target_link_libraries(benchmark_lists ccollections)
# Install the library binary (.so / .a)
install(TARGETS ccollections
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib)

# Install the public header interface files
install(DIRECTORY include/ DESTINATION include/ccollections)