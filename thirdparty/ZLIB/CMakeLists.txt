include(FetchContent)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

set(ZLIB_COMPAT ON)
set(ZLIB_ENABLE_TESTS OFF)
set(SKIP_INSTALL_ALL ON)

FetchContent_MakeAvailable(ZLIB)

# ZLIB has its own way of forcing CMake install directories,
# which becomes very cumbersome and impossible to manage for Windows
# lest we _always_ install in the "Program Files (x86)" directory.
# Until we can hide zlib to the point that we don't expose it,
# we will need to manually install it by re-using code from it's
# CMakeLists.txt, just modified to suit our needs.

file(READ ${zlib_SOURCE_DIR}/zlib.h.in _zlib_h_contents)
string(REGEX REPLACE ".*#define[ \t]+ZLIB_VERSION[ \t]+\"([0-9]+.[0-9]+.[0-9]+).*\".*"
        "\\1" ZLIB_HEADER_VERSION ${_zlib_h_contents})
message(STATUS "ZLIB Header Version Detected: ${ZLIB_HEADER_VERSION}")

set_target_properties(zlib
  PROPERTIES
    POSITION_INDEPENDENT_CODE ON)

if(NOT TARGET ZLIB::zlib)
  add_library(ZLIB::zlib ALIAS zlib)
endif()


install(FILES 
    ${zlib_BINARY_DIR}/zlib.h
    ${zlib_BINARY_DIR}/zlib_name_mangling.h
    ${zlib_BINARY_DIR}/zconf.h
  DESTINATION "include"
)


install(
  TARGETS zlib
  EXPORT ZLIB
  RUNTIME DESTINATION "bin"
  ARCHIVE DESTINATION "lib"
  LIBRARY DESTINATION "lib"
  INCLUDES DESTINATION "include"
)
install(
  EXPORT ZLIB
  NAMESPACE ZLIB::
  DESTINATION "lib/cmake/ZLIB"
)


install(FILES 
    ${zlib_BINARY_DIR}/zlib.pc
  DESTINATION "lib/pkgconfig")
  set (INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_INCLUDEDIR})
  set (LIB_INSTALL_DIR ${CMAKE_INSTALL_LIBDIR})
configure_package_config_file(${zlib_SOURCE_DIR}/zlib-config.cmake.in
    ${zlib_BINARY_DIR}/zlib-config.cmake
    INSTALL_DESTINATION lib/cmake/ZLIB
    PATH_VARS INCLUDE_INSTALL_DIR LIB_INSTALL_DIR)
write_basic_package_version_file(
    ${zlib_BINARY_DIR}/zlib-config-version.cmake
    VERSION ${ZLIB_HEADER_VERSION}
    COMPATIBILITY AnyNewerVersion)
install(FILES ${zlib_BINARY_DIR}/zlib-config.cmake
              ${zlib_BINARY_DIR}/zlib-config-version.cmake
    DESTINATION lib/cmake/ZLIB)

# Problem #2 - zlib-ng (and regular zlib) both love to add
# absolute references to the install path as an Interface
# Include directory, causing NovelRT to fall over when
# included unless it's installed in Program Files :)
# Have to patch this at install time, unfortunately.
install(CODE "
  message(STATUS \"Patching zlib.cmake at: \${CMAKE_INSTALL_PREFIX}/lib/cmake/ZLIB/zlib.cmake\")
  file(STRINGS \${CMAKE_INSTALL_PREFIX}/lib/cmake/ZLIB/ZLIB.cmake LINES)
  file(WRITE \${CMAKE_INSTALL_PREFIX}/lib/cmake/ZLIB/zlib.cmake \"\")
  foreach(LINE IN LISTS LINES)
    string(REGEX REPLACE \"\\\"+.*;+\\\\\\\${_IMPORT_PREFIX}/include\\\"\" \"\\\"\\\${_IMPORT_PREFIX}/include\\\"\" REPLACED \"\${LINE}\")
    file(APPEND \${CMAKE_INSTALL_PREFIX}/lib/cmake/ZLIB/zlib.cmake \"\${REPLACED}\n\")
  endforeach()
")


