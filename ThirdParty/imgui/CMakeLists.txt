include(FetchContent)

FetchContent_MakeAvailable(imgui)

add_library(imgui OBJECT)

target_sources(imgui
  PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}/src/imgui.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/src/imgui_draw.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/src/imgui_tables.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/src/imgui_widgets.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/src/imgui_demo.cpp
  INTERFACE FILE_SET interface_headers TYPE HEADERS BASE_DIRS "${CMAKE_CURRENT_BINARY_DIR}/src" FILES
    "${CMAKE_CURRENT_BINARY_DIR}/src/imgui.h"
    "${CMAKE_CURRENT_BINARY_DIR}/src/imgui_internal.h")

add_library(imgui::imgui ALIAS imgui)

install(
  TARGETS imgui
  EXPORT IMGUIExports
  FILE_SET interface_headers DESTINATION include
)
install(
  EXPORT IMGUIExports
  NAMESPACE imgui::
  DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/lib"
)
