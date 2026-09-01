cmake_minimum_required(VERSION 3.10)

project(simple_student_management_system LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(simple_student_management_system
    main.cpp
    Student.cpp
    Student.h
)

target_compile_options(simple_student_management_system PRIVATE -Wall -Wextra -Wpedantic)