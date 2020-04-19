# Findglad
# --------
#
# Finds the GLAD library.
#
# This will define the following variables:
#   GLAD_FOUND   - True if the system has found GLAD
#   GLAD_VERSION - The full version string which was found
#
# And the following imported targets:
#  glad::glad - The GLAD library
#
# Note the lack of GLAD_LIBRARIES or GLAD_INCLUDE_DIRS.
#

cmake_policy(PUSH)
cmake_policy(SET CMP0077 NEW)

if (DEFINED PACKAGE_VERSION_EXACT)
  find_package(glad ${glad_FIND_VERSION} EXACT CONFIG QUIET)
else()
  find_package(glad ${glad_FIND_VERSION} CONFIG QUIET)
endif()

if(NOT DEFINED GLAD_FOUND)
  find_package(PkgConfig)
  pkg_check_modules(PC_GLAD QUIET glad)
endif()

find_path(GLAD_INCLUDE_DIR
  NAMES glad.h
  PATHS ${PC_GLAD_INCLUDE_DIRS}
  PATH_SUFFIXES glad
)

find_library(GLAD_LIBRARY
  NAMES glad
  PATHS ${PC_GLAD_LIBRARY_DIRS}
)

if(PC_GLAD_VERSION)
  set(GLAD_VERSION ${PC_GLAD_VERSION})

  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(glad
    FOUND_VAR GLAD_FOUND
    REQUIRED_VARS
      GLAD_LIBRARY
      GLAD_INCLUDE_DIR
    VERSION_VAR GLAD_VERSION
  )

  add_library(glad::glad UNKNOWN IMPORTED)
  set_target_properties(glad::glad PROPERTIES
    IMPORTED_LOCATION "${GLAD_LIBRARY}"
    INTERFACE_COMPILE_OPTIONS "${PC_GLAD_CFLAGS_OTHER}"
    INTERFACE_INCLUDE_DIRECTORIES "${GLAD_INCLUDE_DIR}"
  )
elseif(GLAD_INCLUDE_DIR)
  file(READ "${GLAD_INCLUDE_DIR}/glad.h" _glad_version_file)
  string(REGEX REPLACE ".*glad ([0-9\\.]+) on.*" "\\1"
    GLAD_VERSION "${_glad_version_file}")

  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(glad
    FOUND_VAR GLAD_FOUND
    REQUIRED_VARS
      GLAD_LIBRARY
      GLAD_INCLUDE_DIR
    VERSION_VAR GLAD_VERSION
  )

  add_library(glad::glad UNKNOWN IMPORTED)
  set_target_properties(glad::glad PROPERTIES
    IMPORTED_LOCATION "${GLAD_LIBRARY}"
    INTERFACE_COMPILE_OPTIONS "${PC_GLAD_CFLAGS_OTHER}"
    INTERFACE_INCLUDE_DIRECTORIES "${GLAD_INCLUDE_DIR}"
  )
else()
  include(FetchContent)

  set(GLAD_INSTALL ON CACHE BOOL "" FORCE)

  FetchContent_Declare(glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG "v${glad_FIND_VERSION}")

  FetchContent_MakeAvailable(glad)
  FetchContent_GetProperties(glad BINARY_DIR _glad_binary_dir)

  add_library(glad::glad ALIAS glad)

  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(glad
    FOUND_VAR GLAD_FOUND
    REQUIRED_VARS _glad_binary_dir
    VERSION_VAR GLAD_VERSION
  )
endif()

cmake_policy(POP)
