cmake_minimum_required(VERSION 3.20)        

project(izgOpenGL)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

option(SDL_SHARED "" OFF)
option(SDL_STATIC "" ON)
add_subdirectory(SDL)
add_subdirectory(geGL)
add_subdirectory(glfw)
add_subdirectory(glm)

#add_library(SDL2::SDL2 ALIAS SDL2-static)
#add_library(SDL2::SDL2main ALIAS SDL2main)

add_executable(${PROJECT_NAME} src/main.cpp src/bunny.cpp) 

target_link_libraries(${PROJECT_NAME} SDL3::SDL3 geGL::geGL glm)