include(FetchContent)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_DOCS OFF)

FetchContent_MakeAvailable(glfw3)
