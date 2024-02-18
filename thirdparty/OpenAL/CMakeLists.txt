if(NOT ${WIN32})
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

  # These warnings are outside our scope as we do not manage the libraries themselves.
  # We'll silence the warnings so that output is a little cleaner.
  target_compile_options(OpenAL
    PRIVATE
      $<$<CXX_COMPILER_ID:MSVC>:/wd4127>
      $<$<CXX_COMPILER_ID:MSVC>:/wd4834>

      $<$<CXX_COMPILER_ID:GNU>:-Wno-deprecated-copy>

      $<$<CXX_COMPILER_ID:Clang>:-Wno-deprecated-copy>

      $<$<CXX_COMPILER_ID:AppleClang>:-Wno-deprecated-copy>
  )
  target_compile_options(alcommon
    PRIVATE
      $<$<CXX_COMPILER_ID:MSVC>:/wd4127>
      $<$<CXX_COMPILER_ID:MSVC>:/wd4834>

      $<$<CXX_COMPILER_ID:GNU>:-Wno-deprecated-copy>

      $<$<CXX_COMPILER_ID:Clang>:-Wno-deprecated-copy>

      $<$<CXX_COMPILER_ID:AppleClang>:-Wno-deprecated-copy>
  )
endif()
