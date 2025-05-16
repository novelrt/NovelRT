add_library(NovelRT-UI STATIC
    ${imgui_SOURCES}
    ImGui/ImGuiUIProvider.cpp
)

target_sources(NovelRT-UI
  PUBLIC
    FILE_SET public_headers
    TYPE HEADERS
    BASE_DIRS include
    FILES
        include/NovelRT/UI/UIProvider.hpp
        include/NovelRT/UI/ImGui/ImGuiUIProvider.hpp
)

set_target_properties(NovelRT-UI
  PROPERTIES
    EXPORT_NAME UI
    POSITION_INDEPENDENT_CODE ON
)

target_compile_definitions(NovelRT-UI
  PUBLIC
    GLM_ENABLE_EXPERIMENTAL=1
)

target_compile_features(NovelRT-UI
  PUBLIC
    cxx_std_17
)

target_compile_options(NovelRT-UI
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

target_include_directories(NovelRT-UI PRIVATE 
"$<TARGET_PROPERTY:Engine,INCLUDE_DIRECTORIES>"
$<BUILD_INTERFACE:${imgui_SOURCE_DIR}>
$<BUILD_INTERFACE:${imgui_SOURCE_DIR}/backends>
)
target_link_libraries(NovelRT-UI
  PUBLIC
    spdlog
    NovelRT-Graphics
)

install(
  TARGETS NovelRT-UI
  EXPORT NovelRTConfig
  LIBRARY DESTINATION lib
  FILE_SET public_headers DESTINATION include
)