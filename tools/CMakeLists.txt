# 编译main
add_executable(${PROJECT_NAME} fdvim.cpp)

# 添加链接库
target_link_libraries(${PROJECT_NAME} PUBLIC
    Editor
    Screen
    Txt
    Util
)
