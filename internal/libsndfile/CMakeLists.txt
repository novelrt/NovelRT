include(FetchContent)
message(STATUS "Fetching libsndfile...")

FetchContent_Declare(sndfile
        URL https://github.com/libsndfile/libsndfile/archive/refs/tags/1.1.0.tar.gz
        URL_HASH SHA512=5e530c33165a2d2be1c22d3a4bd96f0f1817dded3a45d24bad0e3f2c7908ccc1f19327a91d5040c3ea4d591845876019180747a125bf2a6f8bd49a6f67eadacd

        PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
        TMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/tmp"
        STAMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/stamp"
        DOWNLOAD_DIR "${CMAKE_CURRENT_BINARY_DIR}/dl"
        SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/src"
        SUBBUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/build"
        BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/bin"
        INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/inst"
        LOG_DIR "${CMAKE_CURRENT_BINARY_DIR}/log"

        PATCH_COMMAND git apply "${CMAKE_CURRENT_LIST_DIR}/v1.1.0.patch"
)
set(BUILD_SHARED_LIBS ON CACHE INTERNAL "Build SHARED libraries")
set(ENABLE_PACKAGE_CONFIG OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(sndfile)

# Due to the CMakeLists patch, we define the deps, and target includes/link libs so that it'll
# use the ones we're vendoring w/o issue
add_dependencies(sndfile FLAC ogg opus vorbis vorbisenc)
target_include_directories(sndfile PRIVATE ${OGG_INCLUDE_DIR} ${OPUS_INCLUDE_DIR} ${FLAC_INCLUDE_DIR} ${Vorbis_Vorbis_INCLUDE_DIR})
target_link_libraries(sndfile PRIVATE ogg vorbis vorbisenc opus FLAC)

set_target_properties(sndfile PROPERTIES 
  PUBLIC_HEADER "${sndfile_SOURCE_DIR}/include/sndfile.hh;${sndfile_BINARY_DIR}/include/sndfile.h"
)
if(APPLE)
  set_target_properties(sndfile PROPERTIES NO_SONAME TRUE)
  target_link_options(sndfile PRIVATE -install_name @rpath/libsndfile.dylib)
endif()

install(EXPORT SndFileTargets
  DESTINATION lib/cmake/SndFile
  NAMESPACE SndFile::)
install(FILES SndFileConfig.cmake DESTINATION lib/cmake/SndFile)
install(TARGETS sndfile
  EXPORT SndFileTargets
  LIBRARY DESTINATION lib
  PUBLIC_HEADER DESTINATION include
  RUNTIME DESTINATION bin
  ARCHIVE DESTINATION lib
  FRAMEWORK DESTINATION lib)
