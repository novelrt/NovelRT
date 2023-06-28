include(FetchContent)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_DOCS OFF)

FetchContent_MakeAvailable(glfw3)

if(APPLE)
  set_target_properties(glfw PROPERTIES NO_SONAME TRUE)
  target_link_options(glfw PRIVATE -install_name @rpath/libglfw.dylib)
endif()
