cmake_minimum_required(VERSION 3.10)

project(impl_myString)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(myString main.cpp
    my_string.h
    my_string.cpp)