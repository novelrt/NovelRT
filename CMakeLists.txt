cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(NovelRT)

option(NOVELRT_SUPPORT_DOTNET ".NET support for NovelRT" ON)
option(NOVELRT_SUPPORT_LUA "Lua support for NovelRT" ON)

option(NOVELRT_BUILD_SAMPLES "Build samples" ON)
option(NOVELRT_BUILD_TESTS "Build tests" ON)
option(NOVELRT_BUILD_DOCUMENTATION "Build documentation" OFF)

add_subdirectory(thirdparty)

add_subdirectory(src)
