cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(NovelRT
  VERSION 0.1.0
  DESCRIPTION "NovelRT game engine"
  HOMEPAGE_URL "https://github.com/novelrt/NovelRT"
  LANGUAGES C CXX
)

# Added Clang-format custom target so that we can run it locally if needed.
include(cmake/clang-format.cmake)

if(MSVC)
  # CMake by default appends /W3, so we need to strip it to prevent warnings (D9025)
  string(REGEX REPLACE " /W[0-4]" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
  string(REGEX REPLACE " /W[0-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()

if(WIN32)
  # this is needed, because Windows can be weird, man.
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

option(NOVELRT_BUILD_SAMPLES "Build NovelRT samples" ON)
option(NOVELRT_BUILD_DOCUMENTATION "Build NovelRT documentation" ON)
option(NOVELRT_BUILD_TESTS "Build NovelRT tests" ON)

find_package(Doxygen 1.8.8
  COMPONENTS dot)

if(NOT DOXYGEN_FOUND)
  message("Doxygen 1.8.8 was not found, building documentation is disabled.")
  set(NOVELRT_BUILD_DOCUMENTATION OFF)
endif()

add_subdirectory(src)

if(NOVELRT_BUILD_SAMPLES)
  add_subdirectory(samples)
endif()

if(NOVELRT_BUILD_DOCUMENTATION)
  add_subdirectory(doxygen)
endif()

if(NOVELRT_BUILD_TESTS)
  enable_testing()

  add_subdirectory(tests)
endif()

add_subdirectory(resources)
