include(FetchContent)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

set(ALSOFT_UTILS OFF)
set(ALSOFT_NO_CONFIG_UTIL ON)
set(ALSOFT_EXAMPLES OFF)
set(ALSOFT_INSTALL_EXAMPLES OFF)
set(ALSOFT_INSTALL_UTILS OFF)
set(ALSOFT_TESTS OFF)

set(BUILD_SHARED_LIBS ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS OFF)

FetchContent_MakeAvailable(OpenAL)

# Due to a bug(?) in OpenAL, uint8_t is sometimes used without its corresponding definition.
# To work around this, we force an include to it.
file(GENERATE
  OUTPUT novelrt-cstdint-include.hpp
  CONTENT [[#include <cstdint>]])

# These warnings are outside our scope as we do not manage the libraries themselves.
# We'll silence the warnings so that output is a little cleaner.
target_compile_options(OpenAL
  PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/wd4127>
    $<$<CXX_COMPILER_ID:MSVC>:/wd4834>

    $<$<CXX_COMPILER_ID:GNU>:-Wno-deprecated-copy>
    $<$<CXX_COMPILER_ID:GNU>:-Wno-deprecated-declarations>
    $<$<CXX_COMPILER_ID:GNU>:-Wno-deprecated-literal-operator>
    $<$<CXX_COMPILER_ID:GNU>:-Wno-switch>

    $<$<CXX_COMPILER_ID:Clang>:-Wno-deprecated-copy>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-deprecated-declarations>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-deprecated-literal-operator>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-switch>

    $<$<CXX_COMPILER_ID:AppleClang>:-Wno-deprecated-copy>
    $<$<CXX_COMPILER_ID:AppleClang>:-Wno-deprecated-declarations>

    $<$<CXX_COMPILER_ID:MSVC>:/FI ${CMAKE_CURRENT_BINARY_DIR}/novelrt-cstdint-include.hpp>
    $<$<CXX_COMPILER_ID:GNU>:-include ${CMAKE_CURRENT_BINARY_DIR}/novelrt-cstdint-include.hpp>
    $<$<CXX_COMPILER_ID:Clang>:-include ${CMAKE_CURRENT_BINARY_DIR}/novelrt-cstdint-include.hpp>
    $<$<CXX_COMPILER_ID:AppleClang>:-include ${CMAKE_CURRENT_BINARY_DIR}/novelrt-cstdint-include.hpp>
)
target_compile_options(alcommon
  PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/wd4127>
    $<$<CXX_COMPILER_ID:MSVC>:/wd4834>

    $<$<CXX_COMPILER_ID:GNU>:-Wno-deprecated-copy>
    $<$<CXX_COMPILER_ID:GNU>:-Wno-deprecated-declarations>
    $<$<CXX_COMPILER_ID:GNU>:-Wno-deprecated-literal-operator>
    $<$<CXX_COMPILER_ID:GNU>:-Wno-switch>

    $<$<CXX_COMPILER_ID:Clang>:-Wno-deprecated-copy>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-deprecated-declarations>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-deprecated-literal-operator>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-switch>

    $<$<CXX_COMPILER_ID:AppleClang>:-Wno-deprecated-copy>
    $<$<CXX_COMPILER_ID:AppleClang>:-Wno-deprecated-declarations>

    $<$<CXX_COMPILER_ID:MSVC>:/FI ${CMAKE_CURRENT_BINARY_DIR}/novelrt-cstdint-include.hpp>
    $<$<CXX_COMPILER_ID:GNU>:-include ${CMAKE_CURRENT_BINARY_DIR}/novelrt-cstdint-include.hpp>
    $<$<CXX_COMPILER_ID:Clang>:-include ${CMAKE_CURRENT_BINARY_DIR}/novelrt-cstdint-include.hpp>
    $<$<CXX_COMPILER_ID:AppleClang>:-include ${CMAKE_CURRENT_BINARY_DIR}/novelrt-cstdint-include.hpp>
)
