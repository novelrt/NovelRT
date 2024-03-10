include(FetchContent)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

set(BUILD_SHARED_LIBS ON)
set(LIBSAMPLERATE_INSTALL ON)

FetchContent_MakeAvailable(samplerate)
