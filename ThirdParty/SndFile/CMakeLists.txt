include(FetchContent)

set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

set(BUILD_SHARED_LIBS ON)
set(ENABLE_PACKAGE_CONFIG ON)

# HACK: sndfile uses export(...) but this causes issues, so we skip it.
macro(export)
endmacro()

FetchContent_MakeAvailable(sndfile)
