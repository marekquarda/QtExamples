cmake_minimum_required(VERSION 3.19)

project(izgOpenCL)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

option(SDL_SHARED "" OFF)
option(SDL_STATIC "" ON)
add_subdirectory(SDL-release)
add_subdirectory(geGL)

add_library(glm INTERFACE)
target_include_directories(glm INTERFACE glm)
#add_subdirectory(glm)
#add_library(SDL2::SDL2 ALIAS SDL2-static)
#add_library(SDL2::SDL2main ALIAS SDL2main)

# add_custom_target(copy_resources ALL COMMAND ${CMAKE_COMMAND} -E copy_directory 
#                         ${PROJECT_SOURCE_DIR}/res
#                         ${PROJECT_BINARY_DIR}/res 
#                         COMMENT "Copying resource into binary directory")

#add_dependencies(${PROJECT_NAME} copy_resources)

add_executable(${PROJECT_NAME} src/main.cpp
                               src/shaders.cpp 
                               src/bunny.cpp
#                               src/shaders.h
)

add_custom_target(run ./${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
        SDL2::SDL2 
        SDL2::SDL2main
        geGL::geGL       
        glm
)
