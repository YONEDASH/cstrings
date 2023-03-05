cmake_minimum_required(VERSION 3.10)
project(WSTR)

file(GLOB SRC "src/*.c" "src/*.h" "test/*.c" "test/*.h")
add_executable(testbin ${SRC})