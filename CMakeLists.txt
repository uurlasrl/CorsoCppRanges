cmake_minimum_required(VERSION 3.22)
project(ranges)

set(CMAKE_CXX_STANDARD 20)
set(RANGE_V3 "/Users/domeniconeri/CLionProjects/Libraries/range-v3/include")


add_executable(ranges main.cpp)
target_include_directories(ranges PRIVATE ${RANGE_V3})