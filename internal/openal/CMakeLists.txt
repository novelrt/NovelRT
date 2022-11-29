include(FetchContent)
message(STATUS "Fetching OpenAL...")

FetchContent_Declare(OpenAL
        URL https://github.com/kcat/openal-soft/archive/refs/tags/1.21.1.zip
        URL_HASH SHA512=bc17d628548e59d0db3996917d207a4af0bbbf615ba3ba10ae8e99b28213e845e967a0510c8aad74e551aa66ddfb11499fe26082725af82160ac5d2db4e7e69d

        PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
        TMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/tmp"
        STAMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/stamp"
        DOWNLOAD_DIR "${CMAKE_CURRENT_BINARY_DIR}/dl"
        SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/src"
        SUBBUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/build"
        BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/bin"
        INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/inst"
        LOG_DIR "${CMAKE_CURRENT_BINARY_DIR}/log"
        )

set(ALSOFT_UTILS OFF CACHE BOOL "" FORCE)
set(ALSOFT_NO_CONFIG_UTIL ON CACHE BOOL "" FORCE)
set(ALSOFT_EXAMPLES OFF CACHE BOOL "" FORCE)
set(ALSOFT_INSTALL_EXAMPLES OFF CACHE BOOL "" FORCE)
set(ALSOFT_INSTALL_UTILS OFF CACHE BOOL "" FORCE)
set(ALSOFT_TESTS OFF CACHE BOOL "" FORCE)

set(BUILD_SHARED_LIBS_OLD ${BUILD_SHARED_LIBS})
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS_OLD ${CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS})
set(BUILD_SHARED_LIBS ON CACHE INTERNAL "Build SHARED libraries")
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS OFF CACHE INTERNAL "Don't export symbols for Windows")

FetchContent_MakeAvailable(OpenAL)

set(BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS_OLD} CACHE BOOL "Type of libraries to build" FORCE)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ${CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS_OLD} CACHE BOOL "Tell CMake to always export symbols on Windows" FORCE)

if(APPLE)
  set_target_properties(OpenAL PROPERTIES NO_SONAME TRUE)
  target_link_options(OpenAL PRIVATE -install_name @rpath/libopenal.dylib)
endif()

# These warnings are outside our scope as we do not manage the libraries themselves.
# We'll silence the warnings so that output is a little cleaner.
if(WIN32)
  target_compile_options(OpenAL
    PRIVATE
      $<$<CXX_COMPILER_ID:MSVC>:/wd4127>
      $<$<CXX_COMPILER_ID:MSVC>:/wd4834>
  )
endif()
