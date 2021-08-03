cmake_minimum_required(VERSION 3.8)
project(chutes)

set(CMAKE_C_STANDARD 90)

set(SOURCE_FILES chutes.c tools.c)
add_executable(chutes ${SOURCE_FILES})

set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -pedantic")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )