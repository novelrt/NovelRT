include(FetchContent)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

set(JSON_BuildTests OFF)
set(JSON_Install ON)

FetchContent_MakeAvailable(nlohmann_json)
