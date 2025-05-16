include(FetchContent)

set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

if(CMAKE_APPLE_SILICON_PROCESSOR STREQUAL "arm64")
  set(PNG_ARM_NEON "off" CACHE STRING "" FORCE)
endif()

set(PNG_SHARED ON)
set(PNG_STATIC OFF)
set(PNG_TOOLS OFF CACHE INTERNAL "")
set(PNG_TESTS OFF CACHE INTERNAL "")
set(PNG_BUILD_ZLIB OFF)

set(ZLIB_LIBRARY ZLIB::zlib)

# We can't use generator expressions to provide this because libpng uses them
# in compiler invocations at build time. It's quite a mess.
get_target_property(incl ZLIB::zlib INTERFACE_INCLUDE_DIRECTORIES)
string(REGEX MATCH [[\$<BUILD_INTERFACE:([^>]+)>?]] incl "${incl}")
string(REGEX REPLACE [[\$<BUILD_INTERFACE:([^>]+)>?]] [[\1]] incl "${incl}")
set(ZLIB_INCLUDE_DIR "${incl}")

FetchContent_MakeAvailable(PNG)

# Hack around png not setting its include directories properly
target_include_directories(png
    INTERFACE
      $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/src>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/bin>
      $<INSTALL_INTERFACE:include>
)