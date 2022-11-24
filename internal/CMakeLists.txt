add_subdirectory(Fabulist)
add_subdirectory(glfw)
add_subdirectory(glm)
add_subdirectory(GSL)
add_subdirectory(nlohmannJson)

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
add_subdirectory(vulkan)

if(NOVELRT_BUILD_TESTS)
  add_subdirectory(gtest)
endif()
