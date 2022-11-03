cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

cmake_policy(SET CMP0091 NEW)

project(NovelRT
  VERSION 1.0.0 #MVP Version
  DESCRIPTION "NovelRT game engine"
  HOMEPAGE_URL "https://novelrt.dev"
  LANGUAGES C CXX
)

if(MSVC)
  # CMake by default appends /W3, so we need to strip it to prevent warnings (D9025)
  string(REGEX REPLACE " /W[0-4]" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
  string(REGEX REPLACE " /W[0-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  string(REGEX REPLACE " /M[TD]d?" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
  string(REGEX REPLACE " /M[TD]d?" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()

if(NOT GENERATOR_IS_MULTI_CONFIG AND CMAKE_BUILD_TYPE STREQUAL "")
  message(STATUS "Defaulting to Debug build as no build type was specified")
  set(CMAKE_BUILD_TYPE "Debug")
endif()

if(WIN32)
  # this is needed, because Windows can be weird, man.
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
endif()

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

option(NOVELRT_FETCH_DEPENDENCIES "Fetch and build NovelRT dependencies instead of providing system-based ones" ON)
option(NOVELRT_BUILD_SAMPLES "Build NovelRT samples" ON)
option(NOVELRT_BUILD_DOCUMENTATION "Build NovelRT documentation" OFF)
option(NOVELRT_BUILD_TESTS "Build NovelRT tests" ON)
option(NOVELRT_BUILD_INTEROP "Build NovelRT's Interop library" ON)
option(NOVELRT_INSTALL "Generate installation targets" ON)

set(NOVELRT_DOXYGEN_VERSION "1.8.17" CACHE STRING "Doxygen version")
set(NOVELRT_FREETYPE_VERSION "2.12.1" CACHE STRING "Freetype version")
set(NOVELRT_GSL_VERSION "4.0.0" CACHE STRING "ms-gsl version")
set(NOVELRT_ONETBB_VERSION "2021.5.0" CACHE STRING "OneTBB version")
set(NOVELRT_OPENAL_VERSION "1.21.1" CACHE STRING "OpenAL version")
set(NOVELRT_PNG_VERSION "1.6.35" CACHE STRING "PNG version")
set(NOVELRT_VULKAN_VERSION "1.3.211" CACHE STRING "Vulkan version")


#
# Allow for generating documentation
#
if(NOVELRT_BUILD_DOCUMENTATION)
  find_package(Doxygen ${NOVELRT_DOXYGEN_VERSION}
    COMPONENTS dot
  )
endif()

#
# Generate and Locate NovelRT's Dependencies
#
if(NOVELRT_FETCH_DEPENDENCIES)
  if(NOT NOVELRT_DEPS_INSTALLED)
    if(${CMAKE_GENERATOR} MATCHES "Visual Studio")
      set(GENERATOR_ARCH_PARAM -A ${CMAKE_VS_PLATFORM_TOOLSET_HOST_ARCHITECTURE})
    endif()

    execute_process(
      COMMAND ${CMAKE_COMMAND} -S ${CMAKE_CURRENT_SOURCE_DIR}/internal -B ${CMAKE_CURRENT_BINARY_DIR}/depbuild -DCMAKE_BUILD_TYPE=Release -G ${CMAKE_GENERATOR} ${GENERATOR_ARCH_PARAM} -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/dist
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
      COMMAND_ERROR_IS_FATAL LAST
    )
    execute_process(
      COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/depbuild --config Release
      COMMAND_ERROR_IS_FATAL LAST
    )
    execute_process(
      COMMAND ${CMAKE_COMMAND} --install ${CMAKE_CURRENT_BINARY_DIR}/depbuild --config Release
      COMMAND_ERROR_IS_FATAL LAST
    )

    set(NOVELRT_DEPS_PATH "${CMAKE_CURRENT_BINARY_DIR}/dist" CACHE FILEPATH "Path where NovelRT's Dependencies were previously installed")
    set(NOVELRT_DEPS_INSTALLED TRUE CACHE BOOL "Indicates if NovelRT's Dependencies have been installed locally via FetchContent")
  endif()
  list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_BINARY_DIR}/dist)
  list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_BINARY_DIR}/dist/share)
  list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_BINARY_DIR}/dist/lib/cmake)
endif()

find_package(Vulkan REQUIRED)
find_package(spdlog REQUIRED)
find_package(TBB REQUIRED)
find_package(Microsoft.GSL REQUIRED)
find_package(stduuid REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm REQUIRED)
find_package(jsoncons REQUIRED)
find_package(Ogg REQUIRED)
find_package(OpenAL CONFIG REQUIRED)
find_package(Opus REQUIRED)
find_package(Vorbis REQUIRED)
find_package(flac REQUIRED)
find_package(SndFile REQUIRED)
find_package(nlohmann_json REQUIRED)

if(NOVELRT_DEPS_INSTALLED)
  #CMake-standard FindZLIB breaks runtime deps for Windows
  #So we just use our version that doesn't :)
  include(${NOVELRT_DEPS_PATH}/lib/cmake/ZLIB/ZLIBConfig.cmake)
  include(${NOVELRT_DEPS_PATH}/lib/libpng/libpng16.cmake)
  include(${NOVELRT_DEPS_PATH}/lib/fabulist.cmake)
else()
  find_package(ZLIB REQUIRED)
  find_package(PNG REQUIRED)
  find_package(fabulist REQUIRED) #Will probably break for now :^)
endif()

#
# Generate required files for install
#
include(CMakePackageConfigHelpers)
set(NOVELRT_CONFIG_PATH "${CMAKE_INSTALL_LIBDIR}/cmake/NovelRT")

configure_package_config_file(cmake/NovelRTConfig.cmake.in
                              src/NovelRTConfig.cmake
                              INSTALL_DESTINATION "${NOVELRT_CONFIG_PATH}")

write_basic_package_version_file(src/NovelRTConfigVersion.cmake
                                COMPATIBILITY SameMajorVersion)



#
# Add subdirectories
#
add_subdirectory(resources)
add_subdirectory(src)

if(NOVELRT_BUILD_SAMPLES)
  add_subdirectory(samples)
endif()

if(NOVELRT_BUILD_TESTS)
  add_subdirectory(tests)
endif()

if(DOXYGEN_FOUND AND NOVELRT_BUILD_DOCUMENTATION)
  add_subdirectory(doxygen)
endif()

#
# Install files other than the libraries themselves
# Targets' CMakeLists contains respective installations
#
if(NOVELRT_INSTALL)
  install(
    EXPORT NovelRT
    FILE NovelRTTargets.cmake
    EXPORT_LINK_INTERFACE_LIBRARIES
    NAMESPACE NovelRT::
    DESTINATION "${NOVELRT_CONFIG_PATH}"
  )

  install(
    FILES "${NOVELRT_BINARY_DIR}/src/NovelRTConfig.cmake"
          "${NOVELRT_BINARY_DIR}/src/NovelRTConfigVersion.cmake"
    DESTINATION "${NOVELRT_CONFIG_PATH}")

  #Workaround due to hierarchy destruction when installing by TARGETS
  #Moved to main CMakeLists as headers should always be distributed for now
  install(
    DIRECTORY ${PROJECT_SOURCE_DIR}/include/NovelRT/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/NovelRT
    FILES_MATCHING PATTERN "*.h"
  )

  if(NOVELRT_BUILD_INTEROP)
    install(
      DIRECTORY ${PROJECT_SOURCE_DIR}/include/NovelRT.Interop/
      DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/NovelRT
      FILES_MATCHING PATTERN "*.h"
    )
  endif()


  #TODO: Install Doxygen Docs?

  if(NOVELRT_DEPS_INSTALLED)
    install(
      DIRECTORY ${NOVELRT_DEPS_PATH}/lib/
      DESTINATION lib
      PATTERN "*gtest*" EXCLUDE
    )
    install(
      DIRECTORY ${NOVELRT_DEPS_PATH}/include/
      DESTINATION include
      PATTERN "gtest" EXCLUDE
    )
    install(
      DIRECTORY ${NOVELRT_DEPS_PATH}/share/
      DESTINATION share
      PATTERN "doc" EXCLUDE
      PATTERN "man" EXCLUDE
    )
  endif()
endif()
