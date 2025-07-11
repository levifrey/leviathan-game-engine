cmake_minimum_required(VERSION 3.5)
project(graphics_project VERSION 0.1.0)
cmake_policy(SET  CMP0072 NEW)

find_package(OpenGL REQUIRED)

add_executable(main 
    ../src/main.cpp
	../src/Shader.cpp
    ../include/glad.c
    ../src/Model.cpp
)

target_link_libraries(main glfw OpenGL::GL)
