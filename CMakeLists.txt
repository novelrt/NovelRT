cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(novelrt
  VERSION 0.1.0
  DESCRIPTION NovelRT game engine
  HOMEPAGE_URL https://github.com/novelrt/NovelRT
)

option(NOVELRT_BUILD_SAMPLES "Build NovelRT samples" ON)
option(NOVELRT_BUILD_DOCUMENTATION "Build NovelRT documentation" ON)
option(NOVELRT_BUILD_TESTS "Build NovelRT tests" ON)

include_directories(include)

add_subdirectory(src)

if(NOVELRT_BUILD_SAMPLES)
  add_subdirectory(samples)
endif()

if(NOVELRT_BUILD_DOCUMENTATION)
  add_subdirectory(doxygen)
endif()

if(NOVELRT_BUILD_TESTS)
  add_subdirectory(tests)
endif()
