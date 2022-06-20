add_subdirectory(Fabulist)
add_subdirectory(glfw)
add_subdirectory(glm)
add_subdirectory(GSL)
add_subdirectory(jsoncons)
add_subdirectory(oneTBB)
add_subdirectory(spdlog)

#Ordering this way required as libpng depends on zlib, and freetype depends on both
add_subdirectory(zlib-ng)
add_subdirectory(libpng)
add_subdirectory(freetype)

if(NOVELRT_BUILD_TESTS)
  add_subdirectory(gtest)
endif()
