cmake_minimum_required(VERSION 4.0)
project(rsync_log LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# This project uses headers rather than C++20 modules.
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

set(FMT_MODULE OFF CACHE BOOL "Build fmt as a C++20 module" FORCE)
add_subdirectory(./third-part/fmt-12.2.0)

set(SOURCE_FILES ./main.cpp ./rsync_log.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES}) 

target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt) 

 
