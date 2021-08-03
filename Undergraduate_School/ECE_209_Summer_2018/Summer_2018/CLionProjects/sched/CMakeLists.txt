cmake_minimum_required(VERSION 3.10)
project(sched C)

set(CMAKE_C_STANDARD 90)

add_executable(sched sched.c sched.h main.c)

