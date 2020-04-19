cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

project(NovelRT)

option(NOVELRT_SUPPORT_DOTNET ".NET support for NovelRT" ON)
option(NOVELRT_SUPPORT_LUA "Lua support for NovelRT" ON)

option(NOVELRT_BUILD_SAMPLES "Build samples" ON)
option(NOVELRT_BUILD_TESTS "Build tests" ON)
option(NOVELRT_BUILD_DOCUMENTATION "Build documentation" OFF)

add_subdirectory(src)
