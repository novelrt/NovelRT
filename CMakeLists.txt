cmake_minimum_required(VERSION 3.13)

project(NovelRT VERSION 0.0.1)

option(NOVELRT_BUILD_SAMPLES "Build NovelRT samples" ON)
option(NOVELRT_BUILD_DOCUMENTATION "Build NovelRT documentation" OFF)
option(NOVELRT_BUILD_TESTS "Build NovelRT tests" ON)

option(NOVELRT_SUPPORT_DOTNET "Build .NET support" ON)
option(NOVELRT_SUPPORT_LUA "Build Lua support" ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set(CMAKE_CXX_STANDARD 17)

find_package(vcpkg REQUIRED
  COMPONENTS freetype glad glfw3 glm gtest libsndfile lua nethost openal-soft
  spdlog gtest)

if (MSVC)
  add_compile_options(/W4 /WX /wd4611)
else()
  add_compile_options(-pedantic -pedantic-errors -Wall -Wextra -Weverything -Werror -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-float-equal -Wno-padded -Wno-reserved-id-macro)
endif()

include_directories(include)

add_subdirectory(src)

if(NOVELRT_BUILD_SAMPLES)
  add_subdirectory(samples)
endif()

if(NOVELRT_BUILD_DOCUMENTATION)
  add_subdirectory(doxygen)
endif()

if (NOVELRT_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
