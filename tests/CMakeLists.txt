cmake_minimum_required(VERSION 3.10)

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
