message(STATUS "Building NovelRT for Linux")

#
# Platform-specific changes
#
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  message(WARNING
    " GCC is not fully guaranteed to be compatible with NovelRT at this time."
    " If this is meant for a production workload, we HIGHLY recommend switching "
    " your compiler to the recommended version of Clang as noted in the NovelRT "
    " repository before continuing. If proceeding, your mileage may vary."
  )
endif()

#
# Dependency checks
#
find_package(Vulkan ${NOVELRT_VULKAN_VERSION} REQUIRED)

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
