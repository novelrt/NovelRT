include(FetchContent)

FetchContent_MakeAvailable(imgui)

add_library(imgui INTERFACE)

target_sources(imgui
  INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/src/imgui.cpp>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/src/imgui_draw.cpp>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/src/imgui_tables.cpp>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/src/imgui_widgets.cpp>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/src/imgui_demo.cpp>"
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
