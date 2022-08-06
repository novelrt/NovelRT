include(FetchContent)
include(functions/NovelRTDeps_Populate)
message(STATUS "Fetching Vorbis...")

if(NOVELRT_SHARED_VORBIS OR NOVELRT_BUILD_SHARED_LIBS)
  set(type SHARED)
else()
  set(type STATIC)
endif()

FetchContent_Declare(vorbis
  URL https://github.com/xiph/vorbis/releases/download/v1.3.7/libvorbis-1.3.7.tar.gz
  URL_HASH SHA256=0e982409a9c3fc82ee06e08205b1355e5c6aa4c36bca58146ef399621b0ce5ab

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

NovelRTDeps_PopulateExplicit(vorbis ${type})

#Required for libsndfile
add_library(Vorbis::vorbisenc ALIAS vorbisenc)

set(Vorbis_Vorbis_LIBRARY "vorbis" PARENT_SCOPE)
set(Vorbis_Enc_LIBRARY "vorbisenc" PARENT_SCOPE)
set(Vorbis_File_LIBRARY "vorbisfile" PARENT_SCOPE)
set(Vorbis_Vorbis_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/src/include" PARENT_SCOPE)
set(Vorbis_Enc_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/src/include" PARENT_SCOPE)
set(Vorbis_File_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/src/include" PARENT_SCOPE)

if(NOVELRT_INSTALL)
  install(
    TARGETS vorbis vorbisfile vorbisenc
    EXPORT NovelRTTargets
    DESTINATION lib
    RUNTIME DESTINATION bin
  )
endif()
