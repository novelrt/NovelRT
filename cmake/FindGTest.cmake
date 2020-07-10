# Finds the Google Test library

# This file can be configured with the following CMake variables:
# - gtest_ROOT_DIR
# - gtest_INCLUDE_DIR
# - gtest_LIBRARY

# Or, alternatively, the following environment variables:
# - gtest_INSTALL_DIR
# - LIBRARY_PATH

include(FindPackageHandleStandardArgs)
find_package(PkgConfig)

pkg_check_modules(pc_gtest QUIET gtest)

set(GTest_DEFINITIONS ${pc_gtest_CFLAGS_OTHER})
set(gtest_search_dir ${gtest_ROOT_DIR} $ENV{gtest_INSTALL_DIR})

find_path(GTest_INCLUDE_DIR gtest.h
  HINTS ${gtest_search_dir} ${pc_gtest_INCLUDEDIR} ${pc_gtest_INCLUDE_DIRS}
  PATH_SUFFIXES gtest
)

find_library(
  GTest_LIBRARY NAMES gtest
  HINTS ${gtest_search_dir} ${pc_gtest_LIBDIR} ${pc_gtest_LIBRARY_DIRS}
)

find_library(
  GTest_Main_LIBRARY NAMES gtest_main
  HINTS ${gtest_search_dir} ${pc_gtest_LIBDIR} ${pc_gtest_LIBRARY_DIRS}
)

if(GTest_Main_LIBRARY)
  set(GTest_Main_FOUND TRUE)
endif()

set(GTest_LIBRARIES ${GTest_LIBRARY} ${GTest_Main_LIBRARY})
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
    IMPORTED_LOCATION "${GTest_LIBRARY}"
    INTERFACE_COMPILE_OPTIONS "${GTest_DEFINITIONS}"
  )
endif()

if(GTest_Main_FOUND)
  add_library(GTest::Main UNKNOWN IMPORTED)
  set_target_properties(GTest::Main PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${GTest_INCLUDE_DIRS}"
    IMPORTED_LOCATION "${GTest_Main_LIBRARY}"
    INTERFACE_COMPILE_OPTIONS "${GTest_DEFINITIONS}"
  )
endif()

mark_as_advanced(GTest_INCLUDE_DIRS GTest_LIBRARIES)
