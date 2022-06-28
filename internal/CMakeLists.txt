add_subdirectory(Fabulist)
add_subdirectory(glfw)
add_subdirectory(glm)
add_subdirectory(GSL)
add_subdirectory(stduuid)
add_subdirectory(jsoncons)
#Ordering this way required as libpng depends on zlib, and freetype depends on both
add_subdirectory(zlib-ng)
add_subdirectory(libpng)
add_subdirectory(freetype)
add_subdirectory(oneTBB)
add_subdirectory(spdlog)


if(NOVELRT_BUILD_TESTS)
  add_subdirectory(gtest)
endif()
