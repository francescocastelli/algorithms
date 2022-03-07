cmake_minimum_required(VERSION 3.10)

# set the project name
project(algorithms)

# set c++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set compiler flags
set(GCC_BENCHMARK_COMPILE_FLAGS "-isystem benchmark/include -Lbenchmark/build/src -lbenchmark -lpthread")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_BENCHMARK_COMPILE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

# google benchmark package
find_package(benchmark REQUIRED)

# headers 
include_directories(include/algorithms 
                    include/datastructures 
                    include/utils)

# add all src files as library 
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
add_library(source ${SOURCE_FILES})

# build all benchmarks
file(GLOB_RECURSE BENCH_SOURCE_FILES benchmarks/*.cpp)
foreach(BENCH_SOURCE_PATH ${BENCH_SOURCE_FILES})

    get_filename_component(EXECUTABLE_NAME ${BENCH_SOURCE_PATH} NAME_WE)
    add_executable(${EXECUTABLE_NAME} ${BENCH_SOURCE_PATH})
    target_link_libraries(${EXECUTABLE_NAME} benchmark::benchmark source)

endforeach(BENCH_SOURCE_PATH ${BENCH_SOURCE_FILES})
