include(FetchContent)

set(OPUS_INSTALL_CMAKE_CONFIG_MODULE ON)
set(OPUS_BUILD_PROGRAMS OFF)
set(BUILD_TESTING OFF)

FetchContent_MakeAvailable(Opus)

set_target_properties(opus
  PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)

target_compile_options(opus
  PRIVATE
    $<$<CXX_COMPILER_ID:GNU>:-Wno-cast-align>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-cast-align>
    $<$<CXX_COMPILER_ID:AppleClang>:-Wno-cast-align>
    $<$<CXX_COMPILER_ID:GNU>:-Wno-#pragma-messages>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-#pragma-messages>
    $<$<CXX_COMPILER_ID:AppleClang>:-Wno-#pragma-messages>
)
