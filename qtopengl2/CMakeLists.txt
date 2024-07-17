cmake_minimum_required(VERSION 3.11)

project(opengldemo)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS OpenGL)

add_executable(${PROJECT_NAME}
                src/main.cpp 
                src/mainwindow.cpp 
           #     src/mainwindow.ui
            #    src/glwidget.cpp
)               

target_link_libraries(${PROJECT_NAME} Qt6::Widgets Qt6::OpenGL)

