cmake_minimum_required(VERSION 3.5)
project(graphics_project VERSION 0.1.0)
cmake_policy(SET CMP0072 NEW)


file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS 
    "${CMAKE_CURRENT_SOURCE_DIR}/core/src/*.cpp"
)

add_library(Engine STATIC ${ENGINE_SOURCES})

add_subdirectory(external)

target_include_directories(Engine PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/core/include"
)

# external libraries
target_link_libraries(Engine PUBLIC
    glfw
    glad
    glm
    stb_image
)

find_package(assimp REQUIRED)
target_link_libraries(Engine PUBLIC assimp::assimp)

# OPENGL
find_package(OpenGL REQUIRED)

if (TARGET OpenGL::OpenGL)
    target_link_libraries(Engine PUBLIC OpenGL::OpenGL)
elseif(TARGET OpenGL::GL)
    target_link_libraries(Engine PUBLIC OpenGL::GL)
else()
    target_link_libraries(Engine PUBLIC ${OPENGL_LIBRARIES})
    target_include_directories(Engine PUBLIC ${OPENGL_INCLUDE_DIR})
endif()
