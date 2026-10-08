cmake_minimum_required(VERSION 3.14)
project(memory_management LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(xunique_ptr INTERFACE)
target_include_directories(xunique_ptr INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(memory_demo main.cpp)
target_link_libraries(memory_demo PRIVATE xunique_ptr)

include(CTest)
if(BUILD_TESTING)
    include(FetchContent)
    if(POLICY CMP0135)
        cmake_policy(SET CMP0135 NEW)
    endif()
    FetchContent_Declare(
        googletest
        URL https://codeload.github.com/google/googletest/zip/refs/tags/v1.17.0
        URL_HASH SHA256=40d4ec942217dcc84a9ebe2a68584ada7d4a33a8ee958755763278ea1c5e18ff
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
    set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    add_executable(xunique_ptr_tests tests/xunique_ptr_test.cpp)
    target_link_libraries(xunique_ptr_tests PRIVATE xunique_ptr GTest::gtest_main)

    include(GoogleTest)
    gtest_discover_tests(xunique_ptr_tests)
endif()
