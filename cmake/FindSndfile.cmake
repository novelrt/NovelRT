# Finds the libsndfile library

# This file can be configured with the following CMake variables:
# - Sndfile_ROOT_DIR
# - Sndfile_INCLUDE_DIR
# - Sndfile_LIBRARY

# Or, alternatively, the following environment variables:
# - sndfile_INSTALL_DIR
# - LIBRARY_PATH

include(FindPackageHandleStandardArgs)
find_package(PkgConfig)

pkg_check_modules(pc_sndfile QUIET sndfile)

set(GTest_DEFINITIONS ${pc_sndfile_CFLAGS_OTHER})
set(sndfile_search_dir ${sndfile_ROOT_DIR} $ENV{sndfile_INSTALL_DIR})

find_path(Sndfile_INCLUDE_DIR sndfile.h
  HINTS ${sndfile_search_dir} ${pc_sndfile_INCLUDEDIR} ${pc_sndfile_INCLUDE_DIRS}
  PATH_SUFFIXES include
)

find_library(
  Sndfile_LIBRARY NAMES sndfile
  HINTS ${sndfile_search_dir} ${pc_sndfile_LIBDIR} ${pc_sndfile_LIBRARY_DIRS}
)

set(Sndfile_LIBRARIES ${Sndfile_LIBRARY})
set(Sndfile_INCLUDE_DIRS ${Sndfile_INCLUDE_DIR})
set(Sndfile_VERSION ${pc_sndfile_VERSION})

find_package_handle_standard_args(Sndfile
  REQUIRED_VARS Sndfile_LIBRARIES Sndfile_INCLUDE_DIR
  VERSION_VAR Sndfile_VERSION
  HANDLE_COMPONENTS
)

if(Sndfile_FOUND)
  add_library(Sndfile::sndfile UNKNOWN IMPORTED)
  set_target_properties(Sndfile::sndfile PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${Sndfile_INCLUDE_DIRS}"
    IMPORTED_LOCATION "${Sndfile_LIBRARY}"
    INTERFACE_COMPILE_OPTIONS "${Sndfile_DEFINITIONS}"
  )
endif()

mark_as_advanced(Sndfile_INCLUDE_DIRS Sndfile_LIBRARIES)
