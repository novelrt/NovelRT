# Finds the OpenGL Graphics Library Framework library

# This file can be configured with the following CMake variables:
# - GLFW_ROOT_DIR
# - GLFW_INCLUDE_DIR
# - GLFW_LIBRARY

# Or, alternatively, the following environment variables:
# - GLFW_INSTALL_DIR
# - LIBRARY_PATH

include(FindPackageHandleStandardArgs)
find_package(PkgConfig)

pkg_check_modules(pc_glfw QUIET glfw3)

set(GTest_DEFINITIONS ${pc_glfw_CFLAGS_OTHER})
set(glfw_search_dir ${glfw_ROOT_DIR} $ENV{glfw_INSTALL_DIR})

find_path(GLFW_INCLUDE_DIR
  GLFW/glfw3.h
  HINTS ${glfw_search_dir} ${pc_glfw_INCLUDEDIR} ${pc_glfw_INCLUDE_DIRS}
  PATH_SUFFIXES include
)

find_library(GLFW_LIBRARY
  NAMES glfw glfw3 glfw3dll
  HINTS ${glfw_search_dir} ${pc_glfw_LIBDIR} ${pc_glfw_LIBRARY_DIRS}
  PATH_SUFFIXES lib bin
  ENV LIBRARY_PATH
)

set(GLFW_LIBRARIES ${GLFW_LIBRARY})
set(GLFW_INCLUDE_DIRS ${GLFW_INCLUDE_DIR})
set(GLFW_VERSION ${pc_glfw_VERSION})

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
