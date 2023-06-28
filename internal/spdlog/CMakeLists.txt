include(FetchContent)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

set(SPDLOG_INSTALL ON)
set(SPDLOG_ENABLE_PCH ON)

FetchContent_MakeAvailable(spdlog)

set_property(TARGET spdlog PROPERTY POSITION_INDEPENDENT_CODE ON)
