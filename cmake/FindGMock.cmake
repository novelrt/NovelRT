# Finds the Googletest Mocking library

# This file can be configured with the following CMake variables:
# - gmock_ROOT_DIR
# - gmock_INCLUDE_DIR
# - gmock_LIBRARY
# - gmock_USE_DEBUG_BUILD

# Or, alternatively, the following environment variables:
# - gmock_INSTALL_DIR
# - LIBRARY_PATH

include(FindPackageHandleStandardArgs)
find_package(PkgConfig)

pkg_check_modules(pc_gmock QUIET gmock)
pkg_check_modules(pc_gmock_main QUIET gmock_main)

if(NOT DEFINED gmock_USE_DEBUG_BUILD)
  if(CMAKE_BUILD_TYPE MATCHES "(Debug|DEBUG|debug)")
    set(GMock_BUILD_TYPE DEBUG)
  else()
    set(GMock_BUILD_TYPE RELEASE)
  endif()
elseif(gmock_USE_DEBUG_BUILD)
  set(GMock_BUILD_TYPE DEBUG)
else()
  set(GMock_BUILD_TYPE RELEASE)
endif()

set(GMock_DEFINITIONS ${pc_gmock_CFLAGS_OTHER})
set(GMock_Main_DEFINITIONS ${pc_gmock_main_CFLAGS_OTHER})
set(gmock_search_dir ${gmock_ROOT_DIR} $ENV{gmock_INSTALL_DIR})

find_path(GMock_INCLUDE_DIR gmock/gmock.h
  HINTS ${gmock_search_dir} ${pc_gmock_INCLUDEDIR} ${pc_gmock_INCLUDE_DIRS}
  PATH_SUFFIXES include
)

find_library(
  GMock_LIBRARY_DEBUG NAMES gmockd
  HINTS ${gmock_search_dir} ${pc_gmock_LIBDIR} ${pc_gmock_LIBRARY_DIRS}
  PATH_SUFFIXES lib bin
  ENV LIBRARY_PATH
)

find_library(
  GMock_Main_LIBRARY_DEBUG NAMES gmock_maind
  HINTS ${gmock_search_dir} ${pc_gmock_LIBDIR} ${pc_gmock_main_LIBDIR} ${pc_gmock_LIBRARY_DIRS}
  PATH_SUFFIXES lib bin
  ENV LIBRARY_PATH
)

find_library(
  GMock_LIBRARY_RELEASE NAMES gmock
  HINTS ${gmock_search_dir} ${pc_gmock_LIBDIR} ${pc_gmock_LIBRARY_DIRS}
  PATH_SUFFIXES lib bin
  ENV LIBRARY_PATH
)

find_library(
  GMock_Main_LIBRARY_RELEASE NAMES gmock_main
  HINTS ${gmock_search_dir} ${pc_gmock_LIBDIR} ${pc_gmock_main_LIBDIR} ${pc_gmock_LIBRARY_DIRS}
  PATH_SUFFIXES lib bin
  ENV LIBRARY_PATH
)

if(GMock_Main_LIBRARY_DEBUG OR GMock_Main_LIBRARY_RELEASE)
  set(GMock_Main_FOUND TRUE)
endif()

set(GMock_LIBRARIES_DEBUG ${GMock_LIBRARY_DEBUG})
set(GMock_Main_LIBRARIES_DEBUG ${GMock_Main_LIBRARY_DEBUG})
set(GMock_LIBRARIES_RELEASE ${GMock_LIBRARY_RELEASE})
set(GMock_Main_LIBRARIES_RELEASE ${GMock_Main_LIBRARY_RELEASE})
set(GMock_LIBRARIES ${GMock_LIBRARIES_${GMock_BUILD_TYPE}})
set(GMock_Main_LIBRARIES ${GMock_Main_LIBRARIES_${GMock_BUILD_TYPE}})
set(GMock_INCLUDE_DIRS ${GMock_INCLUDE_DIR})
seT(GMock_VERSION ${pc_gmock_VERSION})

find_package_handle_standard_args(GMock
  REQUIRED_VARS GMock_LIBRARIES GMock_INCLUDE_DIRS
  VERSION_VAR GMock_VERSION
  HANDLE_COMPONENTS
)

if(GMock_FOUND)
  add_library(GMock::GMock UNKNOWN IMPORTED)
  set_target_properties(GMock::GMock PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${GMock_INCLUDE_DIRS}"
    IMPORTED_LOCATION "${GMock_LIBRARIES}"
    INTERFACE_COMPILE_OPTIONS "${GMock_DEFINITIONS}"
  )
endif()

if(GMock_Main_FOUND)
  add_library(GMock::Main UNKNOWN IMPORTED)
  set_target_properties(GMock::Main PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${GMock_INCLUDE_DIRS}"
    IMPORTED_LOCATION "${GMock_Main_LIBRARIES}"
    INTERFACE_COMPILE_OPTIONS "${GMock_Main_DEFINITIONS}"
  )
endif()

mark_as_advanced(GMock_INCLUDE_DIRS GMock_LIBRARIES)
