include(FetchContent)

FetchContent_MakeAvailable(fmt)

set_property(TARGET fmt PROPERTY POSITION_INDEPENDENT_CODE ON)
