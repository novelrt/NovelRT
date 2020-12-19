# Finds the OpenGL Graphics Math library

# This file can be configured with the following CMake variables:
# - GLM_ROOT_DIR
# - GLM_INCLUDE_DIR
# - GLM_LIBRARY

# Or, alternatively, the following environment variables:
# - GLM_INSTALL_DIR
# - LIBRARY_PATH

include(FindPackageHandleStandardArgs)
find_package(PkgConfig QUIET)

pkg_check_modules(PC_GLM QUIET glm)

set(GLM_DEFINITIONS ${PC_GLM_CFLAGS_OTHER})
set(GLM_SEARCH_DIR ${GLM_ROOT_DIR} $ENV{GLM_INSTALL_DIR})

find_path(GLM_INCLUDE_DIR
  glm/glm.hpp
  HINTS ${GLM_SEARCH_DIR} ${PC_GLM_INCLUDEDIR} ${PC_GLM_INCLUDE_DIRS}
  PATH_SUFFIXES include
)

set(GLM_INCLUDE_DIRS ${GLM_INCLUDE_DIR})
set(GLM_VERSION ${PC_GLM_VERSION})

find_package_handle_standard_args(GLM
  REQUIRED_VARS GLM_INCLUDE_DIR
  VERSION_VAR GLM_VERSION
  HANDLE_COMPONENTS
)

if(GLM_FOUND)
  add_library(GLM::GLM INTERFACE IMPORTED)
  set_target_properties(GLM::GLM PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${GLM_INCLUDE_DIRS}"
    INTERFACE_COMPILE_OPTIONS "${GLM_DEFINITIONS}"
  )
endif()

mark_as_advanced(GLM_INCLUDE_DIRS GLM_LIBRARIES)
