include(FetchContent)

FetchContent_MakeAvailable(imgui)

set(imgui_SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/src" CACHE INTERNAL "Set source directory for imgui")
set(imgui_SOURCES
  "${imgui_SOURCE_DIR}/imgui.cpp"
  "${imgui_SOURCE_DIR}/imgui_draw.cpp"
  "${imgui_SOURCE_DIR}/imgui_tables.cpp"
  "${imgui_SOURCE_DIR}/imgui_widgets.cpp"
  "${imgui_SOURCE_DIR}/imgui_demo.cpp"
  CACHE INTERNAL "Set imgui source files"
)

install(
  DIRECTORY ${imgui_SOURCE_DIR}
  DESTINATION include/imgui
  PATTERN "CMakeLists.txt" EXCLUDE
)