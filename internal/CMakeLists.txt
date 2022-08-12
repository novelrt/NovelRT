cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

cmake_policy(SET CMP0091 NEW)
cmake_policy(SET CMP0135 NEW) #for users of 3.24, DOWNLOAD_TIMESTAMP will follow new behaviour

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

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/dist" CACHE STRING "Forced directory to install NovelRT's Dependencies" FORCE)

add_subdirectory(Fabulist)
add_subdirectory(glfw)
add_subdirectory(glm)
add_subdirectory(GSL)

add_subdirectory(jsoncons)
#Ordering this way required as libpng depends on zlib, and freetype depends on both
add_subdirectory(zlib-ng)
add_subdirectory(libpng)
add_subdirectory(freetype)

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

