cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

cmake_policy(SET CMP0091 NEW)

project(NovelRT
  VERSION 0.1.0
  DESCRIPTION "NovelRT game engine"
  HOMEPAGE_URL "https://github.com/novelrt/NovelRT"
  LANGUAGES C CXX
)

set(BUILD_SHARED_LIBS OFF)

if(MSVC)
  # CMake by default appends /W3, so we need to strip it to prevent warnings (D9025)
  string(REGEX REPLACE " /W[0-4]" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
  string(REGEX REPLACE " /W[0-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  string(REGEX REPLACE " /M[TD]d?" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
  string(REGEX REPLACE " /M[TD]d?" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()

if(WIN32)
  # this is needed, because Windows can be weird, man.
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

option(NOVELRT_BUILD_SAMPLES "Build NovelRT samples" ON)
option(NOVELRT_BUILD_DOCUMENTATION "Build NovelRT documentation" ON)
option(NOVELRT_BUILD_TESTS "Build NovelRT tests" ON)
option(NOVELRT_BUILD_INTEROP "Build NovelRT's Interop library" ON)

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
  find_package(Doxygen ${NOVELRT_DOXYGEN_VERSION}
    COMPONENTS dot
  )

  if(NOT DOXYGEN_FOUND)
    message("Doxygen ${NOVELRT_DOXYGEN_VERSION} was not found, building documentation is disabled.")
    set(NOVELRT_BUILD_DOCUMENTATION OFF)
  else()
    add_subdirectory(doxygen)
  endif()
endif()

if(NOVELRT_BUILD_TESTS)
  add_subdirectory(tests)
endif()

install(
  EXPORT NovelRT
  NAMESPACE NovelRT::
  DESTINATION lib
)
