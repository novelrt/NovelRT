include(FetchContent)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0048 NEW)

FetchContent_MakeAvailable(Ogg)

set_target_properties(ogg
  PROPERTIES
    POSITION_INDEPENDENT_CODE ON)
