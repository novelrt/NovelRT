# Finds the OGG library

# This file can be configured with the following CMake variables:
# - OGG_ROOT_DIR
# - OGG_INCLUDE_DIR
# - OGG_LIBRARY

# Or, alternatively, the following environment variables:
# - OGG_INSTALL_DIR
# - LIBRARY_PATH

include(FindPackageHandleStandardArgs)
find_package(PkgConfig QUIET)

pkg_check_modules(PC_OGG QUIET OGG)

set(OGG_DEFINITIONS ${PC_OGG_CFLAGS_OTHER})
set(OGG_SEARCH_DIR ${OGG_ROOT_DIR} ${CONAN_OGG_ROOT} $ENV{OGG_INSTALL_DIR})

find_path(OGG_INCLUDE_DIR
  ogg/ogg.h
  HINTS ${OGG_SEARCH_DIR} ${PC_OGG_INCLUDEDIR} ${PC_OGG_INCLUDE_DIRS}
  PATH_SUFFIXES include
)

find_library(OGG_LIBRARY
  NAMES OGG
  HINTS ${OGG_SEARCH_DIR} ${PC_OGG_LIBDIR} ${PC_OGG_LIBRARY_DIRS}
  PATH_SUFFIXES lib bin
  ENV LIBRARY_PATH
)

set(OGG_LIBRARIES ${OGG_LIBRARY})
set(OGG_INCLUDE_DIRS ${OGG_INCLUDE_DIR})
set(OGG_VERSION ${PC_OGG_VERSION})

find_package_handle_standard_args(Ogg
  REQUIRED_VARS OGG_LIBRARIES OGG_INCLUDE_DIR
  VERSION_VAR OGG_VERSION
  HANDLE_COMPONENTS
)

if(OGG_FOUND)
  add_library(Ogg::Ogg UNKNOWN IMPORTED)
  set_target_properties(Ogg::Ogg PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${OGG_INCLUDE_DIRS}"
    IMPORTED_LOCATION "${OGG_LIBRARY}"
    INTERFACE_COMPILE_OPTIONS "${OGG_DEFINITIONS}"
  )
endif()

mark_as_advanced(OGG_INCLUDE_DIRS OGG_LIBRARIES)
