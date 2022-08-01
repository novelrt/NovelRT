message(STATUS "Fetching libpng...")

if(NOT DISABLE_LTO)
  # Force CMake to raise an error if INTERPROCEDURAL_OPTIMIZATION
  # is enabled and compiler does not support IPO
  # Source: https://github.com/diasurgical/devilutionX
  set(CMAKE_POLICY_DEFAULT_CMP0069 NEW)
endif()

# Source: https://github.com/diasurgical/devilutionX
# PNG_ARM_NEON should be supported on arm64 Apple Silicon
if(APPLE AND "${CMAKE_OSX_ARCHITECTURES}" STREQUAL "arm64")
  set(PNG_ARM_NEON "on" CACHE STRING "" FORCE)
endif()

# libpng doesn't set CMP0077 and uses old CMake so we force these
# variables to stop the warnings.
set(PNG_SHARED OFF CACHE BOOL "Build libpng Shared" FORCE)
set(PNG_STATIC ON CACHE BOOL "Build libpng Static" FORCE)
set(PNG_BUILD_ZLIB ON CACHE BOOL "Build libpng using a provided ZLIB" FORCE)
set(PNG_TESTS OFF CACHE BOOL "Build libpng tests" FORCE)
set(PNG_EXECUTABLES OFF CACHE BOOL "Build libpng Shared" FORCE)
set(SKIP_INSTALL_ALL ON)
set(PNG_LIBRARY "png_static" CACHE STRING "Set PNG libraries" FORCE)

FetchContent_Declare(libpng
  URL https://github.com/diasurgical/libpng/archive/3fe9510f01748b8c706550974e23b09166e5a42d.tar.gz
  URL_HASH SHA512=68495516a0517afb76a9f66d9910452f0fdf4fc663fc191ea1b744bc54fb3e931405f5cb7b08f68997c608f2bec5d188a0af5b089f66eaf5dda9e4ae1a50b142

  PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
  TMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/tmp"
  STAMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/stamp"
  DOWNLOAD_DIR "${CMAKE_CURRENT_BINARY_DIR}/dl"
  SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/src"
  SUBBUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/build"
  BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/bin"
  INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/inst"
  LOG_DIR "${CMAKE_CURRENT_BINARY_DIR}/log"

)

NovelRTDeps_PopulateStatic(libpng)

set(NOVELRT_PNG_SOURCE_DIR "${libpng_SOURCE_DIR}" CACHE STRING "" FORCE)
set(NOVELRT_PNGLIBCONFG_SOURCE_DIR "${libpng_BINARY_DIR}" CACHE STRING "" FORCE)
set(PNG_PNG_INCLUDE_DIR "${NOVELRT_PNG_SOURCE_DIR};${NOVELRT_PNGLIBCONFG_SOURCE_DIR}" CACHE STRING "Set PNG include dirs" FORCE)
set_property(TARGET png_static PROPERTY POSITION_INDEPENDENT_CODE ON)
add_library(PNG::PNG ALIAS ${PNG_LIBRARY})
