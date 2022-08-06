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

set(OGG_HEADERS
  ${ogg_BINARY_DIR}/include/ogg/config_types.h
  ${ogg_SOURCE_DIR}/include/ogg/ogg.h
  ${ogg_SOURCE_DIR}/include/ogg/os_types.h
)

set(OGG_SOURCES
  ${ogg_SOURCE_DIR}/src/bitwise.c
  ${ogg_SOURCE_DIR}/src/framing.c
  ${ogg_SOURCE_DIR}/src/crctable.h
)

if(WIN32 AND BUILD_SHARED_LIBS)
    list(APPEND OGG_SOURCES ${ogg_SOURCE_DIR}/win32/ogg.def)
endif()

add_library(Ogg ${type} ${OGG_HEADERS} ${OGG_SOURCES})
add_library(Ogg::Ogg ALIAS Ogg)

target_include_directories(Ogg PUBLIC
    $<BUILD_INTERFACE:${ogg_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${ogg_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

set_target_properties(Ogg PROPERTIES OUTPUT_NAME "ogg")

# Sndfile gets funny without forcing these
set(OGG_LIBRARY "Ogg" CACHE STRING "The target name for Ogg" FORCE)
set(OGG_INCLUDE_DIR "${ogg_SOURCE_DIR}/include" CACHE STRING "Where to find Ogg sources" FORCE)
set(OGG_FOUND TRUE PARENT_SCOPE)

if(NOVELRT_INSTALL)
  install(
    TARGETS Ogg
    EXPORT NovelRTTargets
    DESTINATION lib
    RUNTIME DESTINATION bin
  )
endif()
