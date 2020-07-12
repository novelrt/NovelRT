# Finds the Google Test library

# This file can be configured with the following CMake variables:
# - gtest_ROOT_DIR
# - gtest_INCLUDE_DIR
# - gtest_LIBRARY
# - gtest_USE_DEBUG_BUILD

# Or, alternatively, the following environment variables:
# - gtest_INSTALL_DIR
# - LIBRARY_PATH

include(FindPackageHandleStandardArgs)
find_package(PkgConfig)

pkg_check_modules(pc_gtest QUIET gtest)

if(NOT DEFINED gtest_USE_DEBUG_BUILD)
  if(CMAKE_BUILD_TYPE MATCHES "(Debug|DEBUG|debug)")
    set(GTest_BUILD_TYPE DEBUG)
  else()
    set(GTest_BUILD_TYPE RELEASE)
  endif()
elseif(gtest_USE_DEBUG_BUILD)
  set(GTest_BUILD_TYPE DEBUG)
else()
  set(GTest_BUILD_TYPE RELEASE)
endif()

set(GTest_DEFINITIONS ${pc_gtest_CFLAGS_OTHER})
set(gtest_search_dir ${gtest_ROOT_DIR} $ENV{gtest_INSTALL_DIR})

find_path(GTest_INCLUDE_DIR gtest/gtest.h
  HINTS ${gtest_search_dir} ${pc_gtest_INCLUDEDIR} ${pc_gtest_INCLUDE_DIRS}
  PATH_SUFFIXES include
)

find_library(
  GTest_LIBRARY_DEBUG NAMES gtestd
  HINTS ${gtest_search_dir} ${pc_gtest_LIBDIR} ${pc_gtest_LIBRARY_DIRS}
  PATH_SUFFIXES lib bin
  ENV LIBRARY_PATH
)

find_library(
  GTest_Main_LIBRARY_DEBUG NAMES gtest_maind
  HINTS ${gtest_search_dir} ${pc_gtest_LIBDIR} ${pc_gtest_LIBRARY_DIRS}
  PATH_SUFFIXES lib bin
  ENV LIBRARY_PATH
)

find_library(
  GTest_LIBRARY_RELEASE NAMES gtest
  HINTS ${gtest_search_dir} ${pc_gtest_LIBDIR} ${pc_gtest_LIBRARY_DIRS}
  PATH_SUFFIXES lib bin
  ENV LIBRARY_PATH
)

find_library(
  GTest_Main_LIBRARY_RELEASE NAMES gtest_main
  HINTS ${gtest_search_dir} ${pc_gtest_LIBDIR} ${pc_gtest_LIBRARY_DIRS}
  PATH_SUFFIXES lib bin
  ENV LIBRARY_PATH
)

if(GTest_Main_LIBRARY_DEBUG OR GTest_Main_LIBRARY_RELEASE)
  set(GTest_Main_FOUND TRUE)
endif()

set(GTest_LIBRARIES_DEBUG ${GTest_LIBRARY_DEBUG})
set(GTest_Main_LIBRARIES_DEBUG ${GTest_Main_LIBRARY_DEBUG})
set(GTest_LIBRARIES_RELEASE ${GTest_LIBRARY_RELEASE})
set(GTest_Main_LIBRARIES_RELEASE ${GTest_Main_LIBRARY_RELEASE})
set(GTest_LIBRARIES ${GTest_LIBRARIES_${GTest_BUILD_TYPE}})
set(GTest_Main_LIBRARIES ${GTest_Main_LIBRARIES_${GTest_BUILD_TYPE}})
set(GTest_INCLUDE_DIRS ${GTest_INCLUDE_DIR})
seT(GTest_VERSION ${pc_gtest_VERSION})

find_package_handle_standard_args(GTest
  REQUIRED_VARS GTest_LIBRARIES GTest_INCLUDE_DIRS
  VERSION_VAR GTest_VERSION
  HANDLE_COMPONENTS
)

if(GTest_FOUND)
  add_library(GTest::GTest UNKNOWN IMPORTED)
  set_target_properties(GTest::GTest PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${GTest_INCLUDE_DIRS}"
    IMPORTED_LOCATION "${GTest_LIBRARIES}"
    INTERFACE_COMPILE_OPTIONS "${GTest_DEFINITIONS}"
  )
endif()

if(GTest_Main_FOUND)
  add_library(GTest::Main UNKNOWN IMPORTED)
  set_target_properties(GTest::Main PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${GTest_INCLUDE_DIRS}"
    IMPORTED_LOCATION "${GTest_Main_LIBRARIES}"
    INTERFACE_COMPILE_OPTIONS "${GTest_DEFINITIONS}"
  )
endif()

mark_as_advanced(GTest_INCLUDE_DIRS GTest_LIBRARIES)
