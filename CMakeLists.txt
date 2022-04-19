cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

# set the project name
project(algorithms)

# set c++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set compiler flags
set(OPT "-O3 -flto")
set(GCC_BENCHMARK_LINK_FLAGS "-isystem benchmark/include -Lbenchmark/build/src -lbenchmark -lpthread")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${OPT}")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_BENCHMARK_LINK_FLAGS} ${OPT}")

# headers 
include_directories(include/algorithms 
                    include/datastructures 
                    include/utils)

# add all src files as library 
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
add_library(source ${SOURCE_FILES})

add_subdirectory(benchmarks)
add_subdirectory(tests)
