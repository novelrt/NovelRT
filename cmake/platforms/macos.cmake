message(STATUS "Building NovelRT for macOS")

#
# Platform-specific changes
#
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15" CACHE STRING "Minimum macOS / OS X deployment version")
set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH "@loader_path/")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "@loader_path/" isSystemDir)
if("${isSystemDir}" STREQUAL "-1")
  set(CMAKE_INSTALL_RPATH "@loader_path/")
endif("${isSystemDir}" STREQUAL "-1")

#
# Dependency checks
#
find_library(COREFOUNDATION CoreFoundation "/")

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
  ${COREFOUNDATION}
)

#
# Compile Options
#
list(APPEND NOVELRT_TARGET_COMPILE_OPTIONS
  -pedantic
  -pedantic-errors
  -Wall
  -Wextra
  -Werror
  -Wno-c++98-compat
  -Wno-c++98-compat-pedantic
  -Wno-float-equal
  -Wno-padded
  -Wno-reserved-id-macro
)

#
# Any verbose behaviour changes
#

#
# Installation behaviour changes
#
