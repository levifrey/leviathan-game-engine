cmake_minimum_required(VERSION 3.5)
project(graphics_project VERSION 0.1.0)
cmake_policy(SET  CMP0072 NEW)

file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

list(APPEND ENGINE_SOURCES  
    "${CMAKE_CURRENT_SOURCE_DIR}/external/glad/src/glad.c"
)

add_library(Engine STATIC ${ENGINE_SOURCES})

target_include_directories(Engine PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# Include external headers (GLAD, STB)
target_include_directories(Engine PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/external/stb_image" 
    "${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include"
)


# ----- OpenGL -----
find_package(OpenGL REQUIRED)

# ----- GLFW -----
find_package(glfw3 3.3 REQUIRED)

target_link_libraries(Engine PUBLIC glfw OpenGL::GL)

# ----- GLM -----
find_package(glm QUIET)

if(NOT glm_FOUND)
    target_include_directories(Engine PUBLIC 
        "${CMAKE_CURRENT_SOURCE_DIR}/external/glm"
    )
else()
    target_link_libraries(Engine PUBLIC glm::glm)
endif()


# Include Glad, GLM, STB (I have the headers)
#include_directories(external)
#set(CMAKE_BUILD_TYPE Debug)
# Fetch GLFW
#include(FetchContent)
#FetchContent_Declare(
#   glfw
#   GIT_REPOSITORY https://github.com/glfw/glfw.git
#   GIT_TAG latest
#)
#FetchContent_MakeAvailable(glfw)
#
#add_library(glad STATIC external/glad/glad.c)
#target_include_directories(glad PUBLIC include)

#file(GLOB_RECURSE SOURCES src/*.cpp)

#add_executable(main ${SOURCES})

#target_link_libraries(main PRIVATE OpenGL::GL glfw glad)
