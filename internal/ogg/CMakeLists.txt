include(FetchContent)
include(functions/NovelRTDeps_Populate)
message(STATUS "Fetching Ogg...")

if(NOVELRT_SHARED_OGG OR NOVELRT_BUILD_SHARED_LIBS)
  set(type SHARED)
else()
  set(type STATIC)
endif()

FetchContent_Declare(Ogg
  URL https://github.com/xiph/ogg/releases/download/v1.3.5/libogg-1.3.5.tar.gz
  URL_HASH SHA256=0eb4b4b9420a0f51db142ba3f9c64b333f826532dc0f48c6410ae51f4799b664

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

NovelRTDeps_PopulateExplicit(Ogg ${type})

add_library(Ogg::Ogg ALIAS ogg)
# Sndfile gets funny without forcing these
set(OGG_LIBRARY "ogg" CACHE STRING "The target name for Ogg" FORCE)
set(OGG_INCLUDE_DIR "${ogg_SOURCE_DIR}/include" CACHE STRING "Where to find Ogg sources" FORCE)
set(OGG_FOUND TRUE PARENT_SCOPE)
