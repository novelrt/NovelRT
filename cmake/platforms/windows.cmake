message(STATUS "Building NovelRT for Windows 10/11")

include(NovelRTBuildDeps)

#
# Platform-specific changes
#
if(CMAKE_GENERATOR STREQUAL "Visual Studio 2017 15")
  message(FATAL_ERROR
    " NovelRT is not compatible with Visual Studio 2017."
    " Please use Visual Studio 2019 or higher, or Build "
    " Tools for Visual Studio 2019 or higher at this time."
  )
endif()

if(MSVC)
  # CMake by default appends /W3, so we need to strip it to prevent warnings (D9025)
  string(REGEX REPLACE " /W[0-4]" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
  string(REGEX REPLACE " /W[0-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  string(REGEX REPLACE " /M[TD]d?" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
  string(REGEX REPLACE " /M[TD]d?" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  list(APPEND NOVELRT_ENGINE_LINK_LIBS Winmm)
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
  list(APPEND NOVELRT_TARGET_COMPILE_DEFS -D__TBB_NO_IMPLICIT_LINKAGE=$<IF:$<CONFIG:DEBUG>,1,0> -DXAUDIO2_HELPER_FUNCTIONS)
endif()

# this is needed, because Windows can be weird, man.
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")

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
  #CMake-standard FindZLIB breaks runtime deps for Windows
  #So we just use our version that doesn't :)
  find_package(ZLIB CONFIG REQUIRED)
  include(${NOVELRT_DEPS_PATH}/lib/libpng/libpng16.cmake)
else()
  find_package(ZLIB REQUIRED)
  find_package(PNG ${NOVELRT_PNG_VERSION} REQUIRED)
endif()

#
# Sources to be compiled
#
list(APPEND NOVELRT_ENGINE_PLATFORM_SOURCES
  Audio/XAudio2/XAudio2Engine.cpp

  ResourceManagement/Windows/DesktopResourceLoader.cpp
  ResourceManagement/Windows/DesktopResourceManagementPluginProvider.cpp
)

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
  /W4
  /WX
  /wd4611
  /MP
)

#
# Any verbose behaviour changes
#
if(NOVELRT_VERBOSE_BUILD)
  if(CMAKE_GENERATOR STREQUAL "Visual Studio 2019 16" OR CMAKE_GENERATOR STREQUAL "Visual Studio 2022 17")
    string(APPEND CMAKE_CXX_FLAGS "-v:detailed")
  endif()
endif()

#
# Installation behaviour changes
#
if(NOVELRT_DEPS_INSTALLED)
  install(
    DIRECTORY ${NOVELRT_DEPS_PATH}/bin/
    DESTINATION bin
    PATTERN "png*.exe" EXCLUDE
    PATTERN "gtest*" EXCLUDE
  )
endif()
