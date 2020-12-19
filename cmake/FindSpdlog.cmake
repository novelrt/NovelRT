# Finds the spdlog library

# This file can be configured with the following CMake variables:
# - SPDLOG_ROOT_DIR
# - SPDLOG_INCLUDE_DIR
# - SPDLOG_LIBRARY

# Or, alternatively, the following environment variables:
# - SPDLOG_INSTALL_DIR
# - LIBRARY_PATH

include(FindPackageHandleStandardArgs)
find_package(PkgConfig QUIET)

pkg_check_modules(PC_SPDLOG QUIET spdlog)

set(SPDLOG_DEFINITIONS ${PC_SPDLOG_CFLAGS_OTHER})
set(SPDLOG_SEARCH_DIR ${SPDLOG_ROOT_DIR} $ENV{SPDLOG_INSTALL_DIR})

find_path(SPDLOG_INCLUDE_DIR
  spdlog/spdlog.h
  HINTS ${SPDLOG_SEARCH_DIR} ${PC_SPDLOG_INCLUDEDIR} ${PC_SPDLOG_INCLUDE_DIRS}
  PATH_SUFFIXES include
)

set(SPDLOG_INCLUDE_DIRS ${SPDLOG_INCLUDE_DIR})
set(SPDLOG_VERSION ${PC_SPDLOG_VERSION})

find_package_handle_standard_args(Spdlog
  REQUIRED_VARS SPDLOG_INCLUDE_DIR
  VERSION_VAR SPDLOG_VERSION
  HANDLE_COMPONENTS
)

if(SPDLOG_FOUND)
  add_library(Spdlog::Spdlog INTERFACE IMPORTED)
  set_target_properties(Spdlog::Spdlog PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${SPDLOG_INCLUDE_DIRS}"
    INTERFACE_COMPILE_OPTIONS "${SPDLOG_DEFINITIONS}"
  )
endif()

mark_as_advanced(SPDLOG_INCLUDE_DIRS SPDLOG_LIBRARIES)
