cmake_minimum_required(VERSION 3.10)

project(only_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(only_test main.cpp 1.cpp)
target_include_directories(only_test PRIVATE .)
