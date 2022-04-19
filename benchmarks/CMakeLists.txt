cmake_minimum_required(VERSION 3.10)

# google benchmark package
find_package(benchmark REQUIRED)

# build all benchmarks
file(GLOB_RECURSE BENCH_SOURCE_FILES *.cpp)
foreach(BENCH_SOURCE_PATH ${BENCH_SOURCE_FILES})

    get_filename_component(EXECUTABLE_NAME ${BENCH_SOURCE_PATH} NAME_WE)
    add_executable(${EXECUTABLE_NAME} ${BENCH_SOURCE_PATH})
    target_link_libraries(${EXECUTABLE_NAME} benchmark::benchmark source)

endforeach(BENCH_SOURCE_PATH ${BENCH_SOURCE_FILES})
