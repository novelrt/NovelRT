cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

cmake_policy(SET CMP0091 NEW)

project(NovelRT
  VERSION 0.1.0
  DESCRIPTION "NovelRT game engine"
  HOMEPAGE_URL "https://github.com/novelrt/NovelRT"
  LANGUAGES C CXX
)

if(MSVC)
  # CMake by default appends /W3, so we need to strip it to prevent warnings (D9025)
  string(REGEX REPLACE " /W[0-4]" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
  string(REGEX REPLACE " /W[0-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  string(REGEX REPLACE " /M[TD]d?" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
  string(REGEX REPLACE " /M[TD]d?" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()

if(WIN32)
  # this is needed, because Windows can be weird, man.
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

option(NOVELRT_BUILD_SAMPLES "Build NovelRT samples" ON)
option(NOVELRT_BUILD_DOCUMENTATION "Build NovelRT documentation" ON)
option(NOVELRT_BUILD_TESTS "Build NovelRT tests" ON)
option(NOVELRT_BUILD_INTEROP "Build NovelRT's Interop library" ON)
option(NOVELRT_INCLUDE_CONAN_PATHS "Include conan_paths toolchain" ON)

set(NOVELRT_BZIP2_VERSION "1.0.8" CACHE STRING "BZip2 version")
set(NOVELRT_DOXYGEN_VERSION "1.8.17" CACHE STRING "Doxygen version")
set(NOVELRT_FLAC_VERSION "1.3.3" CACHE STRING "FLAC version")
set(NOVELRT_FREETYPE_VERSION "2.10.1" CACHE STRING "Freetype version")
set(NOVELRT_GLM_VERSION "0.9.9.7" CACHE STRING "GLM version")
set(NOVELRT_GSL_VERSION "3.1.0" CACHE STRING "ms-gsl version")
set(NOVELRT_OGG_VERSION "1.3.5" CACHE STRING "Ogg version")
set(NOVELRT_ONETBB_VERSION "2021.3.0" CACHE STRING "OneTBB version")
set(NOVELRT_OPENAL_VERSION "1.21.1" CACHE STRING "OpenAL version")
set(NOVELRT_OPUS_VERSION "1.3.1" CACHE STRING "Opus version")
set(NOVELRT_PNG_VERSION "1.6.37" CACHE STRING "PNG version")
set(NOVELRT_SNDFILE_VERSION "1.0.30" CACHE STRING "Sndfile version")
set(NOVELRT_VORBIS_VERSION "1.3.7" CACHE STRING "Opus version")
set(NOVELRT_VULKAN_VERSION "1.2.198" CACHE STRING "Vulkan version")
set(NOVELRT_VULKAN_MEMORY_ALLOCATOR_VERSION "2.3.0" CACHE STRING "VulkanMemoryAllocator version")

if (NOVELRT_INCLUDE_CONAN_PATHS)
  set(CONAN_CMAKE_SILENT_OUTPUT ON)
  include(${CMAKE_BINARY_DIR}/conan_paths.cmake)
endif()

find_package(Doxygen ${NOVELRT_DOXYGEN_VERSION}
  COMPONENTS dot
)

if(NOT DOXYGEN_FOUND)
  message("Doxygen ${NOVELRT_DOXYGEN_VERSION} was not found, building documentation is disabled.")
  set(NOVELRT_BUILD_DOCUMENTATION OFF)
endif()

add_subdirectory(resources)
add_subdirectory(internal)
add_subdirectory(src)

if(NOT NOVELRT_BUILD_INTEROP)
  message("NovelRT Interop library building is disabled.")
endif()

if(NOVELRT_BUILD_SAMPLES)
  add_subdirectory(samples)
endif()

if(NOVELRT_BUILD_DOCUMENTATION)
  add_subdirectory(doxygen)
endif()

if(NOVELRT_BUILD_TESTS)
  add_subdirectory(tests)
endif()

install(
  EXPORT NovelRT
  NAMESPACE NovelRT::
  DESTINATION lib
)
