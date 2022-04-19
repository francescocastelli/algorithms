cmake_minimum_required(VERSION 3.10)

# set the project name
project(algorithms)

# set c++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set compiler flags
set(COMPILER_OPT "-O2 -flto")
set(LINK_OPT "-flto")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${COMPILER_OPT}")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS} ${LINK_OPT}")

enable_testing()
find_package(GTest REQUIRED)
include(GoogleTest)

# build all benchmarks
file(GLOB_RECURSE TEST_SOURCE_FILES *.cpp)
foreach(TEST_SOURCE_PATH ${TEST_SOURCE_FILES})

    get_filename_component(EXECUTABLE_NAME ${TEST_SOURCE_PATH} NAME_WE)
    add_executable(${EXECUTABLE_NAME} ${TEST_SOURCE_PATH})
    target_link_libraries(${EXECUTABLE_NAME} GTest::GTest GTest::Main source)
    gtest_discover_tests(${EXECUTABLE_NAME})

endforeach(TEST_SOURCE_PATH ${TEST_SOURCE_FILES})
