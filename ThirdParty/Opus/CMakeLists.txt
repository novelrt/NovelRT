include(FetchContent)

set(OPUS_INSTALL_CMAKE_CONFIG_MODULE ON)
set(OPUS_BUILD_PROGRAMS OFF)
set(BUILD_TESTING OFF)

FetchContent_MakeAvailable(Opus)

set_target_properties(opus
  PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)

