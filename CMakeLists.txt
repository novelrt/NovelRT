cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(NovelRT
  VERSION 0.1.0
  DESCRIPTION "NovelRT game engine"
  HOMEPAGE_URL "https://github.com/novelrt/NovelRT"
  LANGUAGES C CXX
)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

option(NOVELRT_BUILD_SAMPLES "Build NovelRT samples" ON)
option(NOVELRT_BUILD_DOCUMENTATION "Build NovelRT documentation" ON)
option(NOVELRT_BUILD_TESTS "Build NovelRT tests" ON)

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
