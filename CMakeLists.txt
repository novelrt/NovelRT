cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

cmake_policy(SET CMP0091 NEW)
if(POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif()
if(POLICY CMP0092)
  cmake_policy(SET CMP0092 NEW)
endif()
if(POLICY CMP0083)
  cmake_policy(SET CMP0083 NEW)
endif()
if(POLICY CMP0111)
  cmake_policy(SET CMP0111 NEW)
endif()
if(POLICY CMP0126)
  cmake_policy(SET CMP0126 NEW)
endif()

# Projects added via `add_subdirectory` or `FetchContent` may have a lower
# `cmake_minimum_required` than we set here. Set policies that we require
# to their new value so that they still apply.
set(CMAKE_POLICY_DEFAULT_CMP0048 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0069 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0074 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR [[In-source build detected, please create a new directory (i.e. build) and use `cmake ..`]])
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

project(NovelRT
  VERSION 0.1.0
  DESCRIPTION "NovelRT game engine"
  HOMEPAGE_URL "https://github.com/novelrt/NovelRT"
  LANGUAGES C CXX
)

include(Platforms)

option(NOVELRT_BUILD_SAMPLES "Build NovelRT samples" ON)
option(NOVELRT_BUILD_DOCUMENTATION "Build NovelRT documentation" ON)
option(NOVELRT_BUILD_TESTS "Build NovelRT tests" ON)
option(NOVELRT_BUILD_INTEROP "Build NovelRT's Interop library" ON)
option(NOVELRT_INSTALL "NovelRT install targets will be generated" ON)
option(NOVELRT_PIE "Generate position independent code" OFF)

set(NOVELRT_BZIP2_VERSION "1.0.8" CACHE STRING "BZip2 version")
set(NOVELRT_DOXYGEN_VERSION "1.8.17" CACHE STRING "Doxygen version")
set(NOVELRT_FREETYPE_VERSION "2.12.1" CACHE STRING "Freetype version")
set(NOVELRT_GSL_VERSION "4.0.0" CACHE STRING "ms-gsl version")
set(NOVELRT_ONETBB_VERSION "2021.5.0" CACHE STRING "OneTBB version")
set(NOVELRT_OPENAL_VERSION "1.21.1" CACHE STRING "OpenAL version")
set(NOVELRT_PNG_VERSION "1.6.35" CACHE STRING "PNG version")
set(NOVELRT_VULKAN_VERSION "1.3.211" CACHE STRING "Vulkan version")
set(NOVELRT_VULKAN_MEMORY_ALLOCATOR_VERSION "2.3.0" CACHE STRING "VulkanMemoryAllocator version")
set(NOVELRT_VULKAN_SDK_PATH "" CACHE STRING "Directory for NovelRT to find the Vulkan SDK (mainly for macOS support)")

if(NOVELRT_PIE)
  set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)
endif()

# Remove unused symbols in non-debug mode.
# This is useful even with LTO (-84 KiB with MinSizeRel).
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  # For some reason, adding to CMAKE_CXX_FLAGS results in a slightly smaller
  # binary than using `add_compile/link_options`

  set(_extra_flags "-ffunction-sections -fdata-sections")
  if(APPLE)
    set(_extra_flags "${_extra_flags} -Wl,-dead_strip")
  else()
    set(_extra_flags "${_extra_flags} -Wl,--gc-sections,--as-needed")
  endif()

  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${_extra_flags}")
  set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} ${_extra_flags}")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} ${_extra_flags}")
  set(CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELWITHDEBINFO} ${_extra_flags}")
  set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} ${_extra_flags}")
  set(CMAKE_C_FLAGS_MINSIZEREL "${CMAKE_C_FLAGS_MINSIZEREL} ${_extra_flags}")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies must be included after Platforms
# to ensure that proper flags are set.
include(Dependencies)

add_subdirectory(resources)
add_subdirectory(src)

if(NOT NOVELRT_BUILD_INTEROP)
  message("NovelRT Interop library building is disabled.")
endif()

if(NOVELRT_BUILD_SAMPLES)
  add_subdirectory(samples)
endif()

if(NOVELRT_BUILD_TESTS)
  add_subdirectory(tests)
endif()

if(NOVELRT_BUILD_DOCUMENTATION)
  find_package(Doxygen ${NOVELRT_DOXYGEN_VERSION}
    COMPONENTS dot
    QUIET
  )
  if(NOT DOXYGEN_FOUND)
    message("Doxygen ${NOVELRT_DOXYGEN_VERSION} was not found, building documentation is disabled.")
    set(NOVELRT_BUILD_DOCUMENTATION OFF)
  else()
    add_subdirectory(doxygen)
  endif()
endif()
