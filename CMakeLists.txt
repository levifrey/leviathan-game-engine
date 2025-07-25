cmake_minimum_required(VERSION 3.5)
project(graphics_project VERSION 0.1.0)
cmake_policy(SET  CMP0072 NEW)

find_package(OpenGL REQUIRED)

# Include Glad, GLM, STB (I have the headers)
include_directories(external)
set(CMAKE_BUILD_TYPE Debug)
# Fetch GLFW
include(FetchContent)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG latest
)
FetchContent_MakeAvailable(glfw)

add_library(glad STATIC external/glad/glad.c)
target_include_directories(glad PUBLIC include)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(main ${SOURCES})

target_link_libraries(main PRIVATE OpenGL::GL glfw glad)
