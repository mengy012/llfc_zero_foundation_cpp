cmake_minimum_required(VERSION 4.0)

project(demo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(${PROJECT_NAME} ./main.cpp)

# target_include_directories(${PROJECT_NAME} PRIVATE ./static_lib/include)
# target_link_directories(${PROJECT_NAME} PRIVATE ./static_lib/build/lib)
# target_link_libraries(${PROJECT_NAME} PRIVATE my_math.lib)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_directories(${PROJECT_NAME} PRIVATE lib)
target_link_libraries(${PROJECT_NAME} PRIVATE my_math)
