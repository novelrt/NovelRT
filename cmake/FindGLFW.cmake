# Finds the OpenGL Graphics Library Framework library

# This file can be configured with the following CMake variables:
# - GLFW_ROOT_DIR
# - GLFW_INCLUDE_DIR
# - GLFW_LIBRARY

# Or, alternatively, the following environment variables:
# - GLFW_INSTALL_DIR
# - LIBRARY_PATH

include(FindPackageHandleStandardArgs)
find_package(PkgConfig QUIET)

pkg_check_modules(PC_GLFW QUIET glfw3)

set(GLFW_DEFINITIONS ${PC_GLFW_CFLAGS_OTHER})
set(GLFW_SEARCH_DIR ${GLFW_ROOT_DIR} $ENV{GLFW_INSTALL_DIR})

find_path(GLFW_INCLUDE_DIR
  GLFW/glfw3.h
  HINTS ${GLFW_SEARCH_DIR} ${PC_GLFW_INCLUDEDIR} ${PC_GLFW_INCLUDE_DIRS}
  PATH_SUFFIXES include
)

find_library(GLFW_LIBRARY
  NAMES glfw glfw3 glfw3dll
  HINTS ${GLFW_SEARCH_DIR} ${PC_GLFW_LIBDIR} ${PC_GLFW_LIBRARY_DIRS}
  PATH_SUFFIXES lib bin
  ENV LIBRARY_PATH
)

set(GLFW_LIBRARIES ${GLFW_LIBRARY})
set(GLFW_INCLUDE_DIRS ${GLFW_INCLUDE_DIR})
set(GLFW_VERSION ${PC_GLFW_VERSION})

find_package_handle_standard_args(GLFW
  REQUIRED_VARS GLFW_LIBRARIES GLFW_INCLUDE_DIR
  VERSION_VAR GLFW_VERSION
  HANDLE_COMPONENTS
)

if(GLFW_FOUND)
  add_library(GLFW::GLFW3 UNKNOWN IMPORTED)
  set_target_properties(GLFW::GLFW3 PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${GLFW_INCLUDE_DIRS}"
    IMPORTED_LOCATION "${GLFW_LIBRARY}"
    INTERFACE_COMPILE_OPTIONS "${GLFW_DEFINITIONS}"
  )
endif()

mark_as_advanced(GLFW_INCLUDE_DIRS GLFW_LIBRARIES)
