include(FetchContent)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

set(OPUS_INSTALL_CMAKE_CONFIG_MODULE ON)
set(BUILD_TESTING OFF)

FetchContent_MakeAvailable(Opus)

set_target_properties(opus
  PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)

if(NOT TARGET Opus::opus)
  add_library(Opus::opus ALIAS opus)
endif()
