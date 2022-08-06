# Windows won't have these as system libraries by default so we disable them.
set(NOVELRT_SYSTEM_FABULIST OFF)
set(NOVELRT_SYSTEM_ZLIB OFF)
set(NOVELRT_SYSTEM_PNG OFF)
set(NOVELRT_SYSTEM_FREETYPE OFF)
set(NOVELRT_SYSTEM_OGG OFF)
set(NOVELRT_SYSTEM_OPUS OFF)
set(NOVELRT_SYSTEM_VORBIS OFF)
set(NOVELRT_SYSTEM_FLAC OFF)
set(NOVELRT_SYSTEM_SNDFILE OFF)
set(NOVELRT_SYSTEM_OPENAL OFF)
set(NOVELRT_SYSTEM_GSL OFF)

set(NOVELRT_BUILD_SHARED_LIBS ON)

set(NOVELRT_LIB_SUFFIX "dll")

list(APPEND NOVELRT_PLATFORM_LINK_LIBRARIES
  Winmm
)

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
# CMake by default appends /W3, so we need to strip it to prevent warnings (D9025)
  string(REGEX REPLACE " /W[0-4]" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
  string(REGEX REPLACE " /W[0-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  string(REGEX REPLACE " /M[TD]d?" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
  string(REGEX REPLACE " /M[TD]d?" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
  list(APPEND NOVELRT_PLATFORM_COMPILE_DEFINITIONS -D__TBB_NO_IMPLICIT_LINKAGE=$<IF:$<CONFIG:DEBUG>,1,0>)
  list(APPEND NOVELRT_PLATFORM_COMPILE_OPTIONS
    /W4
    /WX
    /wd4611
    /wd4100
    /MP
  )
endif()

# _insert_dependency_here_ had defined this but Windows does not require it so
# we redefine it to ensure Windows does not try to link it
set(LIBM_REQUIRED FALSE)
