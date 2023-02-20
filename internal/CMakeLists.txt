cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

# Setting multiple policies for additional packages
# We set CMP0048 as a few packages don't set versions
cmake_policy(SET CMP0048 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0048 NEW)
cmake_policy(SET CMP0091 NEW)
# For users of 3.24 and onwards, DOWNLOAD_TIMESTAMP will follow new behaviour
# and use the current time instead of the archived timestamp (which can cause
# issues with not rebuilding the content)
if(POLICY CMP0135)
  cmake_policy(SET CMP0135 NEW)
  set(CMAKE_POLICY_DEFAULT_CMP0135 NEW)
endif()
# We set CMP0077 to prevent clearing of some of our variables
cmake_policy(SET CMP0077 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15" CACHE STRING "Minimum macOS / OS X deployment version")

project(NovelRTDeps
  VERSION 0.1.0
  DESCRIPTION "NovelRT's Dependencies"
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
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
endif()

# Override RPATH on macOS so that we can load in the same folder
if(APPLE)
  set(CMAKE_MACOSX_RPATH 1)
  set(CMAKE_INSTALL_RPATH "@loader_path/")
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(BUILD_SHARED_LIBS ON)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/dist" CACHE STRING "Forced directory to install NovelRT's Dependencies" FORCE)
endif()

message(STATUS "NovelRT - Set dependencies install location to: ${CMAKE_INSTALL_PREFIX}")

add_subdirectory(nlohmann)
add_subdirectory(glfw)
add_subdirectory(SDL2)
add_subdirectory(glm)
add_subdirectory(GSL)

#Ordering this way required as libpng depends on zlib, and freetype depends on both
add_subdirectory(zlib-ng)
add_subdirectory(libpng)
#Removed until later usage
#add_subdirectory(freetype)

#Ordering all of the audio file deps together before we lose sanity at a rapid pace
add_subdirectory(ogg)
add_subdirectory(opus)
add_subdirectory(vorbis)
add_subdirectory(flac)
add_subdirectory(libsndfile)

add_subdirectory(oneTBB)
add_subdirectory(openal)
add_subdirectory(spdlog)
add_subdirectory(stduuid)

add_subdirectory(gtest)

