include(FetchContent)
include(functions/NovelRTDeps_Populate)
message(STATUS "Fetching zlib-ng...")

set(ZLIB_COMPAT ON)

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
set(CMAKE_C_STANDARD 11)
NovelRTDeps_Populate(zlib)

if(NOVELRT_SHARED_ZLIB OR NOVELRT_BUILD_SHARED_LIBS)
  set(type SHARED)
else()
  set(type STATIC)
endif()

set(ZLIB_PUBLIC_HDRS
    ${zlib_BINARY_DIR}/zconf.h
    ${zlib_SOURCE_DIR}/zlib.h
)
set(ZLIB_PRIVATE_HDRS
  ${zlib_SOURCE_DIR}/adler32_p.h
  ${zlib_SOURCE_DIR}/chunkset_tpl.h
  ${zlib_SOURCE_DIR}/crc32_p.h
  ${zlib_SOURCE_DIR}/crc32_tbl.h
  ${zlib_SOURCE_DIR}/crc32_comb_tbl.h
  ${zlib_SOURCE_DIR}/deflate.h
  ${zlib_SOURCE_DIR}/deflate_p.h
  ${zlib_SOURCE_DIR}/functable.h
  ${zlib_SOURCE_DIR}/gzguts.h
  ${zlib_SOURCE_DIR}/inffast.h
  ${zlib_SOURCE_DIR}/inffixed_tbl.h
  ${zlib_SOURCE_DIR}/inflate.h
  ${zlib_SOURCE_DIR}/inflate_p.h
  ${zlib_SOURCE_DIR}/inftrees.h
  ${zlib_SOURCE_DIR}/insert_string_tpl.h
  ${zlib_SOURCE_DIR}/match_tpl.h
  ${zlib_SOURCE_DIR}/trees.h
  ${zlib_SOURCE_DIR}/trees_emit.h
  ${zlib_SOURCE_DIR}/trees_tbl.h
  ${zlib_SOURCE_DIR}/zbuild.h
  ${zlib_SOURCE_DIR}/zendian.h
  ${zlib_SOURCE_DIR}/zutil.h
)
set(ZLIB_SRCS
  ${zlib_SOURCE_DIR}/adler32.c
  ${zlib_SOURCE_DIR}/chunkset.c
  ${zlib_SOURCE_DIR}/compare258.c
  ${zlib_SOURCE_DIR}/compress.c
  ${zlib_SOURCE_DIR}/crc32.c
  ${zlib_SOURCE_DIR}/crc32_comb.c
  ${zlib_SOURCE_DIR}/deflate.c
  ${zlib_SOURCE_DIR}/deflate_fast.c
  ${zlib_SOURCE_DIR}/deflate_medium.c
  ${zlib_SOURCE_DIR}/deflate_quick.c
  ${zlib_SOURCE_DIR}/deflate_slow.c
  ${zlib_SOURCE_DIR}/functable.c
  ${zlib_SOURCE_DIR}/gzlib.c
  ${zlib_SOURCE_DIR}/gzread.c
  ${zlib_SOURCE_DIR}/gzwrite.c
  ${zlib_SOURCE_DIR}/infback.c
  ${zlib_SOURCE_DIR}/inffast.c
  ${zlib_SOURCE_DIR}/inflate.c
  ${zlib_SOURCE_DIR}/inftrees.c
  ${zlib_SOURCE_DIR}/insert_string.c
  ${zlib_SOURCE_DIR}/trees.c
  ${zlib_SOURCE_DIR}/uncompr.c
  ${zlib_SOURCE_DIR}/zutil.c
)

if(WIN32 AND NOT MINGW AND NOT MSYS AND NOT CYGWIN)
  set(ZLIB_DLL_SRCS
    ${zlib_SOURCE_DIR}/win32/zlib1.rc # If present will override custom build rule below.
  )
endif()

set(ZLIB_ALL_SRCS
  ${ZLIB_SRCS}
  ${ZLIB_PUBLIC_HDRS}
  ${ZLIB_PRIVATE_HDRS}
)

add_library(ZLIB ${type} ${ZLIB_ALL_SRCS})

set_target_properties(ZLIB
  PROPERTIES
  SUFFIX "1.${NOVELRT_LIB_SUFFIX}"
  OUTPUT_NAME "zlib")
target_include_directories(ZLIB PUBLIC ${zlib_SOURCE_DIR})
target_include_directories(ZLIB PUBLIC ${zlib_BINARY_DIR})
set_target_properties(ZLIB PROPERTIES SOVERSION 1)
target_compile_definitions(ZLIB PUBLIC -DZLIB_COMPAT)

add_library(ZLIB::ZLIB ALIAS ZLIB)

set(ZLIB_LIBRARY ZLIB::ZLIB PARENT_SCOPE)

if(NOT DEFINED ZLIB_INCLUDE_DIR)
  list(APPEND ZLIB_INCLUDE_DIR ${zlib_SOURCE_DIR} ${zlib_BINARY_DIR})
  # Finding zlib in Freetype appears to be sporatic in success unless we define these forcefully
  set(ZLIB_INCLUDE_DIR ${ZLIB_INCLUDE_DIR} CACHE STRING "Where to find zlib.h, etc." FORCE)
  set(ZLIB_FOUND TRUE PARENT_SCOPE)
endif()

