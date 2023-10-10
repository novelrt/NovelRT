cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

cmake_policy(SET CMP0077 NEW) # option() honors normal variables
cmake_policy(SET CMP0083 NEW) # control generation of PIE
cmake_policy(SET CMP0091 NEW) # MSVC runtime library flags
cmake_policy(SET CMP0135 NEW) # ExternalProject_Add respects timestamps

# Hacky hack hack for Windows
# Needs to be set before project is called. -__-
# We require windows SDK version: v10.0.22621 due to the D3D12 enum values
# we want only being available from this version onwards.
if(WIN32)
  set(CMAKE_SYSTEM_VERSION 10.0.22621.0)
endif()

project(NovelRT
  VERSION 1.0.0 #MVP Version
  DESCRIPTION "NovelRT game engine"
  HOMEPAGE_URL "https://novelrt.dev"
  LANGUAGES C CXX
)

include(CheckPIESupported)
check_pie_supported()

#
# Set the proper backend target for NovelRT
#
set(NOVELRT_TARGET_OPTIONS "Win32" "Linux" "macOS")
set(NOVELRT_TARGET_OPTIONS "${NOVELRT_TARGET_OPTIONS}" CACHE INTERNAL "List of valid platforms for NovelRT")
if(NOT DEFINED NOVELRT_TARGET)
  message(STATUS "No backend specified - setting default based on detected OS.")
  if(WIN32)
    set(NOVELRT_TARGET "Win32" CACHE STRING "")
  elseif(APPLE)
    set(NOVELRT_TARGET "macOS" CACHE STRING "")
  elseif(UNIX)
    set(NOVELRT_TARGET "Linux" CACHE STRING "")
  else()
    set(NOVELRT_TARGET "Unknown" CACHE STRING "")
  endif()
endif()

#
# Prepend so that our FindVulkan gets picked up first when needed
#
list(PREPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

#
# Defining options
#
option(NOVELRT_FETCH_DEPENDENCIES "Fetch and build NovelRT dependencies instead of providing system-based ones" ON)
option(NOVELRT_BUILD_SAMPLES "Build NovelRT samples" ON)
option(NOVELRT_BUILD_DOCUMENTATION "Build NovelRT documentation" OFF)
option(NOVELRT_BUILD_TESTS "Build NovelRT tests" ON)
option(NOVELRT_BUILD_INTEROP "Build NovelRT's Interop library" ON)
option(NOVELRT_VERBOSE_BUILD "Build NovelRT using verbose output" OFF)
option(NOVELRT_INSTALL "Generate installation targets" ON)
option(NOVELRT_USE_STD_SPAN "Alias \"NovelRT::Utilities::Misc:Span\" to \"std::span\" instead of \"gsl::span\"." OFF)
option(NOVELRT_BUILD_DEPS_WITH_MAX_CPU "Use all available CPU processing power when scaffolding/building the NovelRT internal dependences" OFF)

#
# Dependency Version Constraints
#
set(NOVELRT_DOXYGEN_VERSION "1.8.17" CACHE STRING "Doxygen version")
set(NOVELRT_FLAC_VERSION "1.3.4" CACHE STRING "FLAC version")
set(NOVELRT_GLFW_VERSION "3.3.7" CACHE STRING "GLFW3 version")
set(NOVELRT_GSL_VERSION "4.0.0" CACHE STRING "Microsoft.GSL version")
set(NOVELRT_ONETBB_VERSION "2021.5.0" CACHE STRING "OneTBB version")
set(NOVELRT_OPENAL_VERSION "1.21.1" CACHE STRING "OpenAL version")
set(NOVELRT_OGG_VERSION "1.3.5" CACHE STRING "Ogg version")
set(NOVELRT_OPUS_VERSION "1.3.1" CACHE STRING "Opus version")
set(NOVELRT_PNG_VERSION "1.6.35" CACHE STRING "PNG version")
set(NOVELRT_SNDFILE_VERSION "1.1.0" CACHE STRING "SndFile version")
set(NOVELRT_SPDLOG_VERSION "1.10.0" CACHE STRING "spdlog version")
set(NOVELRT_VORBIS_VERSION "1.3.7" CACHE STRING "Vorbis version")
set(NOVELRT_VULKAN_VERSION "1.3.231" CACHE STRING "Vulkan version")
set(NOVELRT_SDL2_VERSION "2.26.0" CACHE STRING "SDL2 version")

#
# Alias "NovelRT::Utilities::Misc:Span" to "std::span" instead of "gsl::span".
# If enabled, you need to make sure you current configuration supports "std::span".
#
if(NOVELRT_USE_STD_SPAN)
  add_compile_definitions(NOVELRT_USE_STD_SPAN=true)
endif()

#
# Setup Debug Output
#
if(NOVELRT_VERBOSE_BUILD)
  set(CMAKE_VERBOSE_MAKEFILE TRUE)
  set(VERBOSE TRUE)
  message(VERBOSE "NovelRT - Target Link Libs:")
  message(VERBOSE ${NOVELRT_ENGINE_LINK_LIBS})
  message(VERBOSE "NovelRT - Target Compile Definitions:")
  message(VERBOSE ${NOVELRT_TARGET_COMPILE_DEFS})
  message(VERBOSE "NovelRT - Target Compile Options:")
  message(VERBOSE ${NOVELRT_TARGET_COMPILE_OPTIONS})
endif()


#
# Documentation Generation target
#
include(ProcessorCount)
ProcessorCount(CORES)
if(CORES EQUAL 0)
  set(CORES_AMT 1)
else()
  math(EXPR CORES_AMT "${CORES} / 2")
  if(CORES_AMT LESS 1)
    set(CORES_AMT 1)
  endif()
endif()
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

    if(NOVELRT_BUILD_DEPS_WITH_MAX_CPU)
      set(NOVELRT_DEPENDENCY_CORE_COUNT ${CORES})
    else()
      set(NOVELRT_DEPENDENCY_CORE_COUNT ${CORES_AMT})
    endif()

    execute_process(
      COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/depbuild --config Release -j${NOVELRT_DEPENDENCY_CORE_COUNT}
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

# Packages w/o version specified typically break as they don't support
# versioning like the others do.
find_package(spdlog ${NOVELRT_SPDLOG_VERSION} REQUIRED)
find_package(TBB ${NOVELRT_ONETBB_VERSION} CONFIG REQUIRED)
find_package(Microsoft.GSL ${NOVELRT_GSL_VERSION} REQUIRED)
find_package(stduuid CONFIG REQUIRED)
find_package(glfw3 ${NOVELRT_GLFW_VERSION} CONFIG REQUIRED)
find_package(glm REQUIRED)
find_package(Ogg ${NOVELRT_OGG_VERSION} REQUIRED)
find_package(OpenAL CONFIG REQUIRED)
find_package(Opus REQUIRED)
find_package(Vorbis ${NOVELRT_VORBIS_VERSION} REQUIRED)
find_package(flac ${NOVELRT_FLAC_VERSION} REQUIRED)
find_package(SndFile REQUIRED)
find_package(nlohmann_json REQUIRED)



if(NOVELRT_DEPS_INSTALLED)
  #CMake-standard FindZLIB breaks runtime deps for Windows
  #So we just use our version that doesn't :)
  find_package(ZLIB CONFIG REQUIRED)
  include(${NOVELRT_DEPS_PATH}/lib/libpng/libpng16.cmake)
else()
  find_package(ZLIB REQUIRED)
  find_package(PNG ${NOVELRT_PNG_VERSION} REQUIRED)
endif()

find_package(Vulkan ${NOVElRT_VULKAN_VERSION} REQUIRED
  OPTIONAL_COMPONENTS MoltenVK)
if(APPLE AND NOT Vulkan_MoltenVK_FOUND)
  message(SEND_ERROR "Could not find MoltenVK, which is required for graphics support")
endif()

#
# Add subdirectories
#
add_subdirectory(thirdparty)
add_subdirectory(resources)
add_subdirectory(graphics)
add_subdirectory(audio)
add_subdirectory(src)

if(NOVELRT_BUILD_SAMPLES)
  add_subdirectory(samples)
endif()

if(NOVELRT_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()


#
# Install files other than the libraries themselves
# Targets' CMakeLists contains respective installations
#
if(NOVELRT_INSTALL)
  install(
    EXPORT NovelRTConfig
    EXPORT_LINK_INTERFACE_LIBRARIES
    NAMESPACE NovelRT::
    DESTINATION lib
  )

  #Moved to main CMakeLists as headers should always be distributed for now
  install(
    DIRECTORY ${PROJECT_SOURCE_DIR}/include/NovelRT/
    DESTINATION include/NovelRT
    FILES_MATCHING PATTERN "*.h"
  )

  if(NOVELRT_BUILD_INTEROP)
    install(
      DIRECTORY ${PROJECT_SOURCE_DIR}/include/NovelRT.Interop/
      DESTINATION include/NovelRT.Interop
      FILES_MATCHING PATTERN "*.h"
    )
  endif()

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
