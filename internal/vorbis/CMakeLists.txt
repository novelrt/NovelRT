include(FetchContent)
include(functions/NovelRTDeps_Populate)
message(STATUS "Fetching Vorbis...")


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

NovelRTDeps_Populate(vorbis)

add_library(Vorbis::vorbisenc ALIAS vorbisenc)

# set_property(TARGET vorbis PROPERTY POSITION_INDEPENDENT_CODE ON)
# set_property(TARGET vorbisfile PROPERTY POSITION_INDEPENDENT_CODE ON)
# set_property(TARGET vorbisenc PROPERTY POSITION_INDEPENDENT_CODE ON)
set(Vorbis_Vorbis_LIBRARY "vorbis" PARENT_SCOPE)
set(Vorbis_Enc_LIBRARY "vorbisenc" PARENT_SCOPE)
set(Vorbis_File_LIBRARY "vorbisfile" PARENT_SCOPE)
set(Vorbis_Vorbis_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/src/include" PARENT_SCOPE)
set(Vorbis_Enc_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/src/include" PARENT_SCOPE)
set(Vorbis_File_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/src/include" PARENT_SCOPE)
