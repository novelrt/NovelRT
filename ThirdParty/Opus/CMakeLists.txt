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
    "$<$<CXX_COMPILER_ID:GNU>:-Wno-#pragma-messages>"
    "$<$<CXX_COMPILER_ID:Clang>:-Wno-#pragma-messages>"
    "$<$<CXX_COMPILER_ID:AppleClang>:-Wno-#pragma-messages>"
)

# FIXME: when updating to CMake 3.30 update this to use $<C_COMPILER_FRONTEND_VARIANT>
get_property(definitions TARGET opus PROPERTY COMPILE_DEFINITIONS)
foreach(definition IN LISTS definitions)
  if((definition STREQUAL "OPUS_X86_MAY_HAVE_SSE") OR (definition STREQUAL "OPUS_X86_PRESUME_SSE"))
    target_compile_options(opus PRIVATE
      $<$<STREQUAL:${CMAKE_C_COMPILER_FRONTEND_VARIANT},GNU>:-msse>
      $<$<STREQUAL:${CMAKE_C_COMPILER_FRONTEND_VARIANT},Clang>:-msse>
      $<$<STREQUAL:${CMAKE_C_COMPILER_FRONTEND_VARIANT},MSVC>:/arch:SSE>)
  elseif((definition STREQUAL "OPUS_X86_MAY_HAVE_SSE2") OR (definition STREQUAL "OPUS_X86_PRESUME_SSE2"))
    target_compile_options(opus PRIVATE
      $<$<STREQUAL:${CMAKE_C_COMPILER_FRONTEND_VARIANT},GNU>:-msse2>
      $<$<STREQUAL:${CMAKE_C_COMPILER_FRONTEND_VARIANT},Clang>:-msse2>
      $<$<STREQUAL:${CMAKE_C_COMPILER_FRONTEND_VARIANT},MSVC>:/arch:SSE2>)
  elseif((definition STREQUAL "OPUS_X86_MAY_HAVE_SSE4_1") OR (definition STREQUAL "OPUS_X86_PRESUME_SSE4_1"))
    target_compile_options(opus PRIVATE
      $<$<STREQUAL:${CMAKE_C_COMPILER_FRONTEND_VARIANT},GNU>:-msse4.1>
      $<$<STREQUAL:${CMAKE_C_COMPILER_FRONTEND_VARIANT},Clang>:-msse4.1>
      $<$<STREQUAL:${CMAKE_C_COMPILER_FRONTEND_VARIANT},MSVC>:/arch:SSE4.2>) # n.b. it seems that MSVC doesn't have a SSE 4.1 option
  elseif((definition STREQUAL "OPUS_X86_MAY_HAVE_AVX2") OR (definition STREQUAL "OPUS_X86_PRESUME_AVX2"))
    target_compile_options(opus PRIVATE
      $<$<STREQUAL:${CMAKE_C_COMPILER_FRONTEND_VARIANT},GNU>:-mavx2>
      $<$<STREQUAL:${CMAKE_C_COMPILER_FRONTEND_VARIANT},Clang>:-mavx2>
      $<$<STREQUAL:${CMAKE_C_COMPILER_FRONTEND_VARIANT},MSVC>:/arch:AVX2>)

  # No flags needed for NEON
  # elseif((definition STREQUAL "OPUS_ARM_MAY_HAVE_NEON") OR (definition STREQUAL "OPUS_ARM_PRESUME_NEON"))
  endif()
endforeach()
