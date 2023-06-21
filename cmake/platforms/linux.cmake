message(STATUS "Building NovelRT for Linux")

include(NovelRTBuildDeps)

#
# Platform-specific changes
#

#
# Dependency checks
#
find_package(spdlog ${NOVELRT_SPDLOG_VERSION} REQUIRED)
find_package(TBB ${NOVELRT_ONETBB_VERSION} CONFIG REQUIRED)
find_package(Microsoft.GSL ${NOVELRT_GSL_VERSION} REQUIRED)
find_package(stduuid CONFIG REQUIRED)
find_package(glfw3 ${NOVELRT_GLFW_VERSION} CONFIG REQUIRED)
find_package(glm REQUIRED)
find_package(Ogg ${NOVELRT_OGG_VERSION} REQUIRED)
find_package(OpenAL CONFIG REQUIRED)
find_package(Opus REQUIRED)
find_package(Vorbis ${NOVELRT_VORBIS_VERSION} REQUIRED)
find_package(flac ${NOVELRT_FLAC_VERSION} REQUIRED)
find_package(SndFile REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(Vulkan ${NOVELRT_VULKAN_VERSION} REQUIRED)
if(NOVELRT_DEPS_INSTALLED)
  find_package(ZLIB CONFIG REQUIRED)
  include(${NOVELRT_DEPS_PATH}/lib/libpng/libpng16.cmake)
else()
  find_package(ZLIB REQUIRED)
  find_package(PNG ${NOVELRT_PNG_VERSION} REQUIRED)
endif()

#
# Libraries to be linked
#
list(APPEND NOVELRT_ENGINE_LINK_LIBS
  Vulkan::Vulkan
  TBB::tbb
  OpenAL::OpenAL
  SndFile::sndfile
  glfw
  png
  spdlog::spdlog
  nlohmann_json::nlohmann_json
  stduuid
  Vorbis::vorbis
  Vorbis::vorbisenc
  FLAC::FLAC
  Opus::opus
  Ogg::ogg
)

#
# Compile Options
#
list(APPEND NOVELRT_TARGET_COMPILE_OPTIONS
  $<$<CXX_COMPILER_ID:GNU>:-pedantic>
  $<$<CXX_COMPILER_ID:GNU>:-pedantic-errors>
  $<$<CXX_COMPILER_ID:GNU>:-Wall>
  $<$<CXX_COMPILER_ID:GNU>:-Wextra>
  $<$<CXX_COMPILER_ID:GNU>:-Werror>
  $<$<CXX_COMPILER_ID:GNU>:-Wno-float-equal>
  $<$<CXX_COMPILER_ID:GNU>:-Wno-padded>

  $<$<CXX_COMPILER_ID:Clang>:-pedantic>
  $<$<CXX_COMPILER_ID:Clang>:-pedantic-errors>
  $<$<CXX_COMPILER_ID:Clang>:-Wall>
  $<$<CXX_COMPILER_ID:Clang>:-Wextra>
  $<$<CXX_COMPILER_ID:Clang>:-Werror>
  $<$<CXX_COMPILER_ID:Clang>:-Wno-c++98-compat>
  $<$<CXX_COMPILER_ID:Clang>:-Wno-c++98-compat-pedantic>
  $<$<CXX_COMPILER_ID:Clang>:-Wno-float-equal>
  $<$<CXX_COMPILER_ID:Clang>:-Wno-padded>
  $<$<CXX_COMPILER_ID:Clang>:-Wno-reserved-id-macro>
)

#
# Any verbose behaviour changes
#

#
# Installation behaviour changes
#
