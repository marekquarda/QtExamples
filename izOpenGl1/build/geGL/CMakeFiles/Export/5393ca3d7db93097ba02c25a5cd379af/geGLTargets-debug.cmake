#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "geGL::geGL" for configuration "Debug"
set_property(TARGET geGL::geGL APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(geGL::geGL PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libgeGLd.a"
  )

list(APPEND _cmake_import_check_targets geGL::geGL )
list(APPEND _cmake_import_check_files_for_geGL::geGL "${_IMPORT_PREFIX}/lib/libgeGLd.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
