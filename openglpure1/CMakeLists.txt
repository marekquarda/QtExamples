cmake_minimum_required(VERSION 3.11)

project(openglpure VERSION 1.0.0)

add_executable(${PROJECT_NAME}
                src/main.cpp 
)

target_include_directories(${PROJECT_NAME} PRIVATE dependencies/headers)
#target_link_libraries(${CMAKE_SOURCE_DIR}/dependencies/libs/glfw3.lib)
set(CMAKE_LIBRARY_PATH dependencies/libs)
find_library(GLFW_LIBRARY NAMES glfw3)
#message(${CMAKE_SOURCE_DIR}/dependencies/libs)

target_link_libraries(${PROJECT_NAME} GLFW_LIBRARY) 
