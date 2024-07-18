cmake_minimum_required(VERSION 3.16)
project(openglwindow LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Gui OpenGL OpenGLWidgets)

qt_standard_project_setup()

qt_add_executable(openglwindow
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.ui
    src/mainwindow.h
    src/triangleglwidget.cpp
    src/triangleglwidget.h
)

set_target_properties(openglwindow PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(openglwindow PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::OpenGL
    Qt6::OpenGLWidgets
)

install(TARGETS openglwindow
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET openglwindow
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
