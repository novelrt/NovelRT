# Finds the Googletest Mocking library

# This file can be configured with the following CMake variables:
# - gmock_ROOT_DIR
# - gmock_INCLUDE_DIR
# - gmock_LIBRARY

# Or, alternatively, the following environment variables:
# - gmock_INSTALL_DIR
# - LIBRARY_PATH

include(FindPackageHandleStandardArgs)
find_package(PkgConfig)

pkg_check_modules(pc_gmock QUIET gmock)

set(GMock_DEFINITIONS ${pc_gmock_CFLAGS_OTHER})
set(gmock_search_dir ${gmock_ROOT_DIR} $ENV{gmock_INSTALL_DIR})

find_path(GMock_INCLUDE_DIR gmock.h
  HINTS ${gmock_search_dir} ${pc_gmock_INCLUDEDIR} ${pc_gmock_INCLUDE_DIRS}
  PATH_SUFFIXES gmock
)

find_library(
  GMock_LIBRARY NAMES gmock
  HINTS ${gmock_search_dir} ${pc_gmock_LIBDIR} ${pc_gmock_LIBRARY_DIRS}
)

find_library(
  GMock_Main_LIBRARY NAMES gmock_main
  HINTS ${gmock_search_dir} ${pc_gmock_LIBDIR} ${pc_gmock_LIBRARY_DIRS}
)

if(GMock_Main_LIBRARY)
  set(GMock_Main_FOUND TRUE)
endif()

set(GMock_LIBRARIES ${GMock_LIBRARY} ${GMock_Main_LIBRARY})
set(GMock_INCLUDE_DIRS ${GMock_INCLUDE_DIR})
set(GMock_VERSION ${pc_gmock_VERSION})

find_package_handle_standard_args(GMock
  REQUIRED_VARS GMock_INCLUDE_DIRS GMock_LIBRARIES
  VERSION_VAR GMock_VERSION
  HANDLE_COMPONENTS
)

if(GMock_FOUND)
  add_library(GMock::GMock UNKNOWN IMPORTED)
  set_target_properties(GMock::GMock PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${GMock_INCLUDE_DIRS}"
    IMPORTED_LOCATION "${GMock_LIBRARY}"
    INTERFACE_COMPILE_OPTIONS "${GMock_DEFINITIONS}"
  )
endif()

if(GMock_Main_FOUND)
  add_library(GMock::Main UNKNOWN IMPORTED)
  set_target_properties(GMock::Main PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${GMock_INCLUDE_DIRS}"
    IMPORTED_LOCATION "${GMock_Main_LIBRARY}"
    INTERFACE_COMPILE_OPTIONS "${GMock_DEFINITIONS}"
  )
endif()

mark_as_advanced(GMock_INCLUDE_DIRS GMock_LIBRARIES)
