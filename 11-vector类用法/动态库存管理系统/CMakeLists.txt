cmake_minimum_required(VERSION 3.10)

project(dynamic_inventory_management_system LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(dynamic_inventory_management_system
    main.cpp
    InventoryItem.cpp
    InventoryItem.h
)

target_compile_options(dynamic_inventory_management_system PRIVATE -Wall -Wextra -Wpedantic)