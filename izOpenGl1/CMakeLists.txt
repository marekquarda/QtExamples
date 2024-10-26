cmake_minimum_required(VERSION 3.18)

project(lzgOpenGL)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

option(SDL_SHARED "" OFF)
option(SDL_STATIC "" ON)
add_subdirectory(SDL-release)
add_subdirectory(geGL)
add_subdirectory(glm)
include_directories(SDL-release/include)

add_executable(${PROJECT_NAME} src/main.cpp
                                src/bunny.cpp) 

target_link_libraries(${PROJECT_NAME} SDL2::SDL2 
                                      SDL2::SDL2main
                                      geGL::geGL
                                      glm)
