cmake_minimum_required(VERSION 3.16)
project(MyGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(Engine)

file(GLOB_RECURSE USER_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/games/*.cpp")

file(GLOB_RECURSE USER_BEHAVIORS 
    "${CMAKE_CURRENT_SOURCE_DIR}/behaviors/*.cpp" 
    "${CMAKE_CURRENT_SOURCE_DIR}/behaviors/*.h")

foreach(GAME_FILE ${USER_SOURCES})
    get_filename_component(GAME_NAME ${GAME_FILE} NAME_WE)

    add_executable(${GAME_NAME} ${GAME_FILE})

    target_include_directories(${GAME_NAME} PRIVATE 
        "${CMAKE_CURRENT_SOURCE_DIR}/behaviors"
    )
    
    target_link_libraries(${GAME_NAME} PRIVATE Engine)
endforeach()
