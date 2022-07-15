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


#FetchContent_MakeAvailable(sndfile)

FetchContent_GetProperties(sndfile)
if(NOT sndfile_POPULATED)
  FetchContent_Populate(sndfile)

  set(BUILD_SHARED_LIBS_OLD ${BUILD_SHARED_LIBS})
  set(BUILD_SHARED_LIBS ON CACHE INTERNAL "Build SHARED libraries")
  set(ENABLE_PACKAGE_CONFIG OFF CACHE BOOL "" FORCE)

  add_subdirectory(${sndfile_SOURCE_DIR} ${sndfile_BINARY_DIR} EXCLUDE_FROM_ALL)
# Due to the CMakeLists patch, we define the deps, and target includes/link libs so that it'll
# use the ones we're vendoring w/o issue
  add_dependencies(sndfile FLAC ogg opus vorbis vorbisenc)
  target_include_directories(sndfile PRIVATE ${OGG_INCLUDE_DIR} ${OPUS_INCLUDE_DIR} ${FLAC_INCLUDE_DIR} ${Vorbis_Vorbis_INCLUDE_DIR})
  target_link_libraries(sndfile PRIVATE ogg vorbis vorbisenc opus FLAC)

  set(BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS_OLD} CACHE BOOL "Type of libraries to build" FORCE)
endif()

install(TARGETS sndfile
   EXPORT NovelRT
   LIBRARY DESTINATION lib)
