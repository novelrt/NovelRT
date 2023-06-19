message(STATUS "Building NovelRT for macOS")

include(NovelRTBuildDeps)

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
find_package(Vulkan ${NOVELRT_VULKAN_VERSION} REQUIRED COMPONENTS MoltenVK)
find_library(COREFOUNDATION CoreFoundation "/")
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
if(NOVELRT_VERBOSE_BUILD)
  set(CMAKE_VERBOSE_MAKEFILE TRUE)
  set(VERBOSE TRUE)
endif()

#
# Installation behaviour changes
#
