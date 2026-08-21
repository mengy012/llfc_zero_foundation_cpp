cmake_minimum_required(VERSION 3.14)

add_executable(test ./test.cpp)
target_compile_options(test PRIVATE /W4 /utf-8)