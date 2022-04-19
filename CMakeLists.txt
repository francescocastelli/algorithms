cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

# set the project name
project(algorithms)

# headers 
include_directories(include/algorithms 
                    include/datastructures 
                    include/utils)

# add all src files as library 
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
add_library(source ${SOURCE_FILES})

add_subdirectory(benchmarks)
add_subdirectory(tests)
