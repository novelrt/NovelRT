message(STATUS "Building NovelRT for macOS")

set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15" CACHE STRING "Minimum macOS / OS X deployment version")

include(../NovelRTBuildDeps.cmake)

find_package(Vulkan ${NOVELRT_VULKAN_VERSION} REQUIRED COMPONENTS MoltenVK)
find_library(COREFOUNDATION CoreFoundation "/")
if(NOVELRT_DEPS_INSTALLED)
  #CMake-standard FindZLIB breaks runtime deps for Windows
  #So we just use our version that doesn't :)
  find_package(ZLIB CONFIG REQUIRED)
  include(${NOVELRT_DEPS_PATH}/lib/libpng/libpng16.cmake)
else()
  find_package(ZLIB REQUIRED)
  find_package(PNG ${NOVELRT_PNG_VERSION} REQUIRED)
endif()


set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH "@loader_path/")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "@loader_path/" isSystemDir)
if("${isSystemDir}" STREQUAL "-1")
  set(CMAKE_INSTALL_RPATH "@loader_path/")
endif("${isSystemDir}" STREQUAL "-1")

if(NOVELRT_VERBOSE_BUILD)
  set(CMAKE_VERBOSE_MAKEFILE TRUE)
  set(VERBOSE TRUE)
endif()
