include(FetchContent)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

set(BUILD_CXXLIBS OFF)
set(BUILD_PROGRAMS OFF)
set(BUILD_EXAMPLES OFF)
set(BUILD_TESTING OFF)
set(BUILD_DOCS OFF)
set(INSTALL_MANPAGES OFF)
set(INSTALL_PKGCONFIG_MODULES OFF)
set(INSTALL_CMAKE_CONFIG_MODULE ON)

FetchContent_MakeAvailable(flac)

set_target_properties(FLAC
  PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)

target_compile_options(FLAC
  PRIVATE
    $<$<CXX_COMPILER_ID:GNU>:-Wno-cast-align>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-cast-align>
    $<$<CXX_COMPILER_ID:AppleClang>:-Wno-cast-align>
)

if(APPLE)
  set_target_properties(FLAC PROPERTIES NO_SONAME TRUE)
  target_link_options(FLAC PRIVATE -install_name @rpath/libFLAC.dylib)
endif()
