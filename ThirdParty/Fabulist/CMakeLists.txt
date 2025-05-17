include(FetchContent)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

set(FABULIST_THIRDPARTY_JSON OFF)
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(FABULIST_THIRDPARTY_JSON OFF)

FetchContent_MakeAvailable(Fabulist)


# Appears to be a bug, doing this until established and/or resolved
install(DIRECTORY
      ${fabulist_SOURCE_DIR}/runtime/include/fabulist/runtime/
   DESTINATION include/fabulist/runtime
)

install(FILES
      ${fabulist_BINARY_DIR}/runtime/fabulist_runtime_export.hpp
   DESTINATION include/fabulist/runtime/actions
)
