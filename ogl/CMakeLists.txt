cmake_minimum_required(VERSION 3.11)

project(ogl)

set(SOURCES src/main.cpp)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#find_package(SDL2 CONFIG)
#find_package(GLEW REQUIRED)
add_subdirectory(SDL-release)
link_directories(${CMAKE_SOURCE_DIR}/Glew/lib)
include_directories(${CMAKE_SOURCE_DIR}/Glew/include)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PUBLIC SDL2::SDL2 SDL2::SDL2main GLEW32)