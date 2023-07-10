# CMake版本要求
cmake_minimum_required(VERSION 3.20)

# 项目信息
project(fdvim)

# 添加头文件目录
include_directories(include/Editor)
include_directories(include/Screen)
include_directories(include/Txt)
include_directories(include/Util)

# 递归构建
add_subdirectory(lib)
add_subdirectory(tools)