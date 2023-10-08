include(FetchContent)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

set(UUID_USING_CXX20_SPAN TRUE)
set(UUID_ENABLE_INSTALL TRUE)

FetchContent_MakeAvailable(stduuid)
