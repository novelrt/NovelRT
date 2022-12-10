include(FetchContent)
message(STATUS "Fetching Dear ImGui...")

FetchContent_Declare(imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  #GIT_TAG Comes from the latest CI-passing commit on 'docking' branch for viewport/docking support
  GIT_TAG c191faf0ba478e9c58a69c63306986a21ebfb6e4

  PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
  TMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/tmp"
  STAMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/stamp"
  DOWNLOAD_DIR "${CMAKE_CURRENT_BINARY_DIR}/dl"
  SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/src"
  SUBBUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/build"
  BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/bin"
  INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/inst"
  LOG_DIR "${CMAKE_CURRENT_BINARY_DIR}/log"
)

FetchContent_MakeAvailable(imgui)

set(imgui_SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/src" CACHE INTERNAL "Set source directory for imgui")

install(
  DIRECTORY ${imgui_SOURCE_DIR}
  DESTINATION include/imgui
  PATTERN "CMakeLists.txt" EXCLUDE
)
