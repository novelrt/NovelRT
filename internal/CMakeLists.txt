include(FetchContent)
include(../cmake/Dependency_Options.cmake)
include(../cmake/NovelRTDeps_Populate.cmake)

add_subdirectory(Fabulist)
add_subdirectory(glfw)
add_subdirectory(glm)
add_subdirectory(GSL)

add_subdirectory(jsoncons)

#Ordering this way required as libpng depends on zlib, and freetype depends on both
Dependency_Options("zlib" NOVELRT_SYSTEM_ZLIB ON NOVELRT_STATIC_ZLIB)
if(NOT NOVELRT_SYSTEM_ZLIB)
  add_subdirectory(zlib-ng)
endif()

set(NOVELRT_STATIC_PNG OFF)
Dependency_Options("libpng" NOVELRT_SYSTEM_PNG ON NOVELRT_STATIC_PNG)
if(NOVELRT_SYSTEM_PNG)
  find_package(PNG REQUIRED)
else()
  add_subdirectory(libpng)
endif()

set(NOVELRT_STATIC_FREETYPE OFF)
Dependency_Options("libpng" NOVELRT_SYSTEM_FREETYPE ON NOVELRT_STATIC_FREETYPE)
if(NOT NOVELRT_SYSTEM_FREETYPE)
  add_subdirectory(freetype)
endif()

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
add_subdirectory(vulkan)

if(NOVELRT_BUILD_TESTS)
  add_subdirectory(gtest)
endif()
