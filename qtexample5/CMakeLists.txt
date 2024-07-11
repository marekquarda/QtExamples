cmake_minimum_required(VERSION 3.11)

project(emitter)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 CONFIG REQUIRED COMPONENTS Widgets)

add_executable(${PROJECT_NAME}
                src/main.cpp 
)               

target_link_libraries(${PROJECT_NAME} Qt6::Widgets)

