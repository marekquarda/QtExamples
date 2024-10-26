# Install script for directory: /home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/geGL

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/build/geGL/libgeGLd.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/geGL" TYPE FILE FILES
    "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/geGL/src/geGL/Fwd.h"
    "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/geGL/src/geGL/Definitions.h"
    "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/geGL/src/geGL/Buffer.h"
    "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/geGL/src/geGL/VertexArray.h"
    "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/geGL/src/geGL/Framebuffer.h"
    "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/geGL/src/geGL/Texture.h"
    "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/geGL/src/geGL/Sampler.h"
    "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/geGL/src/geGL/ProgramPipeline.h"
    "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/geGL/src/geGL/Shader.h"
    "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/geGL/src/geGL/Program.h"
    "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/geGL/src/geGL/ProgramInfo.h"
    "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/geGL/src/geGL/Renderbuffer.h"
    "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/geGL/src/geGL/OpenGL.h"
    "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/geGL/src/geGL/OpenGLUtil.h"
    "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/geGL/src/geGL/AsynchronousQuery.h"
    "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/geGL/src/geGL/DebugMessage.h"
    "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/geGL/src/geGL/OpenGLObject.h"
    "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/geGL/src/geGL/geGL.h"
    "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/geGL/src/geGL/OpenGLFunctionTable.h"
    "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/geGL/src/geGL/OpenGLContext.h"
    "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/geGL/src/geGL/OpenGLCapabilities.h"
    "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/geGL/src/geGL/FunctionLoaderInterface.h"
    "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/geGL/src/geGL/DefaultLoader.h"
    "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/geGL/src/geGL/LoaderTableDecorator.h"
    "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/geGL/src/geGL/DSATableDecorator.h"
    "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/geGL/src/geGL/TrapTableDecorator.h"
    "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/geGL/src/geGL/CapabilitiesTableDecorator.h"
    "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/geGL/src/geGL/StaticCalls.h"
    "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/geGL/src/geGL/GLSLNoise.h"
    "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/build/geGL/geGL/gegl_export.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/geGL/Generated" TYPE FILE FILES
    "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/geGL/src/geGL/Generated/ContextCalls.h"
    "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/geGL/src/geGL/Generated/ContextDeclarations.h"
    "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/geGL/src/geGL/Generated/FunctionTableCalls.h"
    "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/geGL/src/geGL/Generated/LoaderImplementation.h"
    "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/geGL/src/geGL/Generated/LoaderLoadingCalls.h"
    "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/geGL/src/geGL/Generated/NumberOfFunctions.h"
    "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/geGL/src/geGL/Generated/MemberOpenGLFunctions.h"
    "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/geGL/src/geGL/Generated/MemberOpenGLPFN.h"
    "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/geGL/src/geGL/Generated/OpenGLConstants.h"
    "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/geGL/src/geGL/Generated/OpenGLFunctions.h"
    "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/geGL/src/geGL/Generated/OpenGLPFN.h"
    "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/geGL/src/geGL/Generated/OpenGLTypes.h"
    "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/geGL/src/geGL/Generated/TrapCalls.h"
    "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/geGL/src/geGL/Generated/TrapImplementation.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/geGL/geGLTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/geGL/geGLTargets.cmake"
         "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/build/geGL/CMakeFiles/Export/5393ca3d7db93097ba02c25a5cd379af/geGLTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/geGL/geGLTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/geGL/geGLTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/geGL" TYPE FILE FILES "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/build/geGL/CMakeFiles/Export/5393ca3d7db93097ba02c25a5cd379af/geGLTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/geGL" TYPE FILE FILES "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/build/geGL/CMakeFiles/Export/5393ca3d7db93097ba02c25a5cd379af/geGLTargets-debug.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/geGL" TYPE FILE FILES
    "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/build/geGL/geGL/geGLConfig.cmake"
    "/home/marra/Projects/OpenGlExamples/QtExamples/izOpenGl1/build/geGL/geGL/geGLConfigVersion.cmake"
    )
endif()

