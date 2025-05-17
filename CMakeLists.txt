cmake_minimum_required(VERSION 3.24...3.31)

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

list(PREPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

option(NOVELRT_FETCH_DEPENDENCIES "Fetch and build NovelRT dependencies instead of providing system-based ones" ON)
option(NOVELRT_BUILD_SAMPLES "Build NovelRT samples" ON)
option(NOVELRT_BUILD_DOCUMENTATION "Build NovelRT documentation" OFF)
option(NOVELRT_BUILD_TESTS "Build NovelRT tests" ON)
option(NOVELRT_BUILD_INTEROP "Build NovelRT's Interop library" ON)
option(NOVELRT_VERBOSE_BUILD "Build NovelRT using verbose output" OFF)
option(NOVELRT_INSTALL "Generate installation targets" ON)
option(NOVELRT_USE_STD_SPAN "Alias \"NovelRT::Utilities::Misc:Span\" to \"std::span\" instead of \"gsl::span\"." OFF)
option(NOVELRT_BUILD_DEPS_WITH_MAX_CPU "Use all available CPU processing power when scaffolding/building the NovelRT internal dependences" OFF)

if(NOVELRT_USE_STD_SPAN)
  add_compile_definitions(NOVELRT_USE_STD_SPAN=true)
endif()

#
# Documentation Generation target
#
if(NOVELRT_BUILD_DOCUMENTATION)
  find_package(Doxygen ${NOVELRT_DOXYGEN_VERSION}
    COMPONENTS dot
  )
  if(DOXYGEN_FOUND)
    add_subdirectory(doxygen)
  endif()
endif()

add_subdirectory(ThirdParty)
add_subdirectory(Resources)
add_subdirectory(Graphics)
add_subdirectory(Audio)
add_subdirectory(Input)
add_subdirectory(UI)

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
