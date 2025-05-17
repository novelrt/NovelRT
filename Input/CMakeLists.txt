add_library(NovelRT-Input STATIC
  KeyStateFrameChangeLog.cpp
  NovelKey.cpp
  Glfw/GlfwInputDevice.cpp
  Glfw/GlfwInputPluginProvider.cpp
)

target_sources(NovelRT-Input
  PUBLIC
    FILE_SET public_headers
    TYPE HEADERS
    BASE_DIRS include
    FILES
      include/NovelRT/Input/IInputDevice.hpp
      include/NovelRT/Input/InputAction.hpp
      include/NovelRT/Input/KeyState.hpp
      include/NovelRT/Input/KeyStateFrameChangeLog.hpp
      include/NovelRT/Input/NovelKey.hpp
      include/NovelRT/Input/Glfw/GlfwInputDevice.hpp
      include/NovelRT/Input/Glfw/GlfwInputPluginProvider.hpp
)

set_target_properties(NovelRT-Input
  PROPERTIES
    EXPORT_NAME Input
    POSITION_INDEPENDENT_CODE ON
)

target_compile_features(NovelRT-Input
  PUBLIC
    cxx_std_17
)

target_compile_options(NovelRT-Input
  PRIVATE
    $<$<CXX_COMPILER_ID:GNU>:-Wall>
    $<$<CXX_COMPILER_ID:GNU>:-Wabi>
    $<$<CXX_COMPILER_ID:GNU>:-Werror>
    $<$<CXX_COMPILER_ID:GNU>:-Wextra>
    $<$<CXX_COMPILER_ID:GNU>:-Wpedantic>
    $<$<CXX_COMPILER_ID:GNU>:-pedantic-errors>

    $<$<CXX_COMPILER_ID:Clang>:-Wall>
    $<$<CXX_COMPILER_ID:Clang>:-Werror>
    $<$<CXX_COMPILER_ID:Clang>:-Wextra>
    $<$<CXX_COMPILER_ID:Clang>:-Wpedantic>
    $<$<CXX_COMPILER_ID:Clang>:-pedantic-errors>

    $<$<CXX_COMPILER_ID:MSVC>:/W4>
    $<$<CXX_COMPILER_ID:MSVC>:/WX>
    $<$<CXX_COMPILER_ID:MSVC>:/permissive->
)

target_compile_definitions(NovelRT-Input PUBLIC GLM_ENABLE_EXPERIMENTAL=1)

target_include_directories(NovelRT-Input PRIVATE "$<TARGET_PROPERTY:Engine,INCLUDE_DIRECTORIES>")
target_link_libraries(NovelRT-Input
  PUBLIC
    spdlog
    glfw
    tbb
)

install(
  TARGETS NovelRT-Input
  EXPORT NovelRTConfig
  LIBRARY DESTINATION lib
  FILE_SET public_headers DESTINATION include
)
