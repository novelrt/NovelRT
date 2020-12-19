# Finds the libsndfile library

# This file can be configured with the following CMake variables:
# - SNDFILE_ROOT_DIR
# - SNDFILE_INCLUDE_DIR
# - SNDFILE_LIBRARY

# Or, alternatively, the following environment variables:
# - SNDFILE_INSTALL_DIR
# - LIBRARY_PATH

include(FindPackageHandleStandardArgs)
find_package(PkgConfig QUIET)

pkg_check_modules(PC_SNDFILE QUIET sndfile)

set(SNDFILE_DEFINITIONS ${PC_SNDFILE_CFLAGS_OTHER})
set(SNDFILE_SEARCH_DIR ${SNDFILE_ROOT_DIR} $ENV{SNDFILE_INSTALL_DIR})

find_path(SNDFILE_INCLUDE_DIR
  sndfile.h
  HINTS ${SNDFILE_SEARCH_DIR} ${PC_SNDFILE_INCLUDEDIR} ${PC_SNDFILE_INCLUDE_DIRS}
  PATH_SUFFIXES include
)

if(SNDFILE_INCLUDE_DIR)
  file(READ "${SNDFILE_INCLUDE_DIR}/sndfile.h" _sndfile_version_file)
  string(REGEX REPLACE ".*#define.*SNDFILE_([0-9]+).*" "\\1" _sndfile_suffix_version "${_sndfile_version_file}")
  set(_sndfile_extra_names "sndfile-${_sndfile_suffix_version}" "libsndfile-${_sndfile_suffix_version}")
endif()

find_library(SNDFILE_LIBRARY
  NAMES sndfile libsndfile ${_sndfile_extra_names}
  HINTS ${SNDFILE_SEARCH_DIR} ${PC_SNDFILE_LIBDIR} ${PC_SNDFILE_LIBRARY_DIRS}
  PATH_SUFFIXES lib bin
  ENV LIBRARY_PATH
)

set(SNDFILE_LIBRARIES ${SNDFILE_LIBRARY})
set(SNDFILE_INCLUDE_DIRS ${SNDFILE_INCLUDE_DIR})
set(SNDFILE_VERSION ${PC_SNDFILE_VERSION})

find_package_handle_standard_args(Sndfile
  REQUIRED_VARS SNDFILE_LIBRARIES SNDFILE_INCLUDE_DIR
  VERSION_VAR SNDFILE_VERSION
  HANDLE_COMPONENTS
)

if(SNDFILE_FOUND)
  add_library(Sndfile::Sndfile UNKNOWN IMPORTED)
  set_target_properties(Sndfile::Sndfile PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${SNDFILE_INCLUDE_DIRS}"
    IMPORTED_LOCATION "${SNDFILE_LIBRARY}"
    INTERFACE_COMPILE_OPTIONS "${SNDFILE_DEFINITIONS}"
  )
endif()

mark_as_advanced(SNDFILE_INCLUDE_DIRS SNDFILE_LIBRARIES)
