cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

#CMP0048 - a few packages don't set versions
#CMP0077 - prevent clearing of certain variables
#CMP0091 - Use CMAKE_MSVC_RUNTIME_LIBRARY Abstraction
#CMP0135 - DOWNLOAD_TIMESTAMP follows new behaviour for CMake 3.24+
foreach(policy CMP0048 CMP0077 CMP0091 CMP0135)
  if(POLICY ${policy})
    cmake_policy(SET ${policy} NEW)
    set(CMAKE_POLICY_DEFAULT_${policy} NEW)
  endif()
endforeach()

message(STATUS "NovelRT - Set dependencies install location to: ${CMAKE_INSTALL_PREFIX}")

#
# Platform-specific settings
#
if(${NOVELRT_TARGET} STREQUAL "Win32")
  if(MSVC)
    # CMake by default appends /W3, so we need to strip it to prevent warnings (D9025)
    string(REGEX REPLACE " /W[0-4]" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
    string(REGEX REPLACE " /W[0-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    string(REGEX REPLACE " /M[TD]d?" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
    string(REGEX REPLACE " /M[TD]d?" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  endif()
elseif(${NOVELRT_TARGET} STREQUAL "macOS")
  set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15" CACHE STRING "Minimum macOS / OS X deployment version")
# Override RPATH on macOS so that we can load in the same folder
  set(CMAKE_MACOSX_RPATH 1)
  set(CMAKE_INSTALL_RPATH "@loader_path/")
endif()

#
# Common dependencies
#
add_subdirectory(glfw)
add_subdirectory(glm)
add_subdirectory(GSL)
add_subdirectory(gtest)
add_subdirectory(nlohmann)
add_subdirectory(oneTBB)
add_subdirectory(openal)
add_subdirectory(spdlog)
add_subdirectory(stduuid)

add_subdirectory(zlib-ng)     # Leave here for ordering purposes lest you disturb the libpng-kraken
add_subdirectory(libpng)      # Leave here for ordering purposes lest you disturb the Loch Ness Freetype Monster
#add_subdirectory(freetype)   # Removed until further notice
add_subdirectory(ogg)         # Leave here for ordering purposes - libsndfile
add_subdirectory(opus)        # Leave here for ordering purposes - libsndfile
add_subdirectory(vorbis)      # Leave here for ordering purposes - libsndfile
add_subdirectory(flac)        # Leave here for ordering purposes - libsndfile
add_subdirectory(libsndfile)
add_subdirectory(VulkanMemoryAllocator)
add_subdirectory(Fabulist)
