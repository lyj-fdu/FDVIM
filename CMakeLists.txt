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

# 编译main
add_executable(${PROJECT_NAME} main.cpp)

# 添加链接库
target_link_libraries(${PROJECT_NAME} PUBLIC
    Editor
    Screen
    Txt
    Util
)
