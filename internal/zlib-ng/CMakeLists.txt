include(FetchContent)
message(STATUS "Fetching zlib-ng")
FetchContent_Declare(zlib
        URL https://github.com/zlib-ng/zlib-ng/archive/refs/tags/2.0.6.tar.gz
        URL_HASH SHA512=4888f17160d0a87a9b349704047ae0d0dc57237a10e11adae09ace957afa9743cce5191db67cb082991421fc961ce68011199621034d2369c0e7724fad58b4c5

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
set(ZLIB_COMPAT ON CACHE BOOL "Compile with zlib compatible API" FORCE)
set(ZLIB_ENABLE_TESTS OFF CACHE BOOL "Build test binaries" FORCE)
set(INC_INSTALL_DIR "include" CACHE STRING "Relocate includes installation folder" FORCE)
set(LIB_INSTALL_DIR "lib" CACHE STRING "Relocate libraries installation folder" FORCE)
FetchContent_MakeAvailable(zlib)
set(ZLIB_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/src;${CMAKE_CURRENT_BINARY_DIR}/bin" CACHE STRING "" FORCE)
set(ZLIB_LIBRARY "zlibstatic" CACHE STRING "" FORCE)
install(EXPORT ZLIB
  DESTINATION lib
  NAMESPACE ZLIB::)
install(TARGETS zlib
  EXPORT ZLIB
  LIBRARY DESTINATION lib)
