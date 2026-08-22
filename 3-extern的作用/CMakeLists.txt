# 设置CMake最小版本要求
cmake_minimum_required(VERSION 3.10)

# 设置项目名称和版本
project(MyProject VERSION 1.0)

# 添加一个可执行文件
# 语法：add_executable(目标名 源文件...)
add_executable(namespace_test main.cpp 1.cpp)