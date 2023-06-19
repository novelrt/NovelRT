message(STATUS "Building NovelRT for Windows 10/11")

# We require windows SDK version: v10.0.22621 due to the D3D12 enum values we want only being available from this version onwards.
# The value sets the minimal version that we need to use during building
set(CMAKE_SYSTEM_VERSION 10.0.22621.0)

if(MSVC)
  # CMake by default appends /W3, so we need to strip it to prevent warnings (D9025)
  string(REGEX REPLACE " /W[0-4]" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
  string(REGEX REPLACE " /W[0-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  string(REGEX REPLACE " /M[TD]d?" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
  string(REGEX REPLACE " /M[TD]d?" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()

# this is needed, because Windows can be weird, man.
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")

include(../NovelRTBuildDeps.cmake)

### Dependency checks
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

if(NOVELRT_VERBOSE_BUILD)
  if(CMAKE_GENERATOR STREQUAL "Visual Studio 2019 16" OR CMAKE_GENERATOR STREQUAL "Visual Studio 2022 17")
    string(APPEND CMAKE_CXX_FLAGS "-v:detailed")
  endif()
endif()

if(NOVELRT_DEPS_INSTALLED)
  install(
    DIRECTORY ${NOVELRT_DEPS_PATH}/bin/
    DESTINATION bin
    PATTERN "png*.exe" EXCLUDE
    PATTERN "gtest*" EXCLUDE
  )
endif()
