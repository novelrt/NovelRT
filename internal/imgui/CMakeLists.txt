include(FetchContent)
message(STATUS "Fetching imgui")

FetchContent_Declare(imgui
        URL https://github.com/ocornut/imgui/archive/refs/tags/v1.88.zip
        URL_HASH SHA512=4140903a7d04b5ff7226044b2da2473cabc6f00aa94cb7b0663f36a8ea009b62991a33e16b7387cafdf19ea9c70ce588670cb2ad35583edbc09bbe95e3df258c

        PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
        TMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/tmp"
        STAMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/stamp"
        DOWNLOAD_DIR "${CMAKE_CURRENT_BINARY_DIR}/dl"
        SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/src"
        SUBBUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}"
        INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/inst"
        LOG_DIR "${CMAKE_CURRENT_BINARY_DIR}/log"
        )

FetchContent_MakeAvailable(imgui)

set(imgui_SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/src" CACHE INTERNAL "Set source directory for imgui")
set(imgui_SOURCES
  "${imgui_SOURCE_DIR}/imgui.cpp"
  "${imgui_SOURCE_DIR}/imgui_draw.cpp"
  "${imgui_SOURCE_DIR}/imgui_tables.cpp"
  "${imgui_SOURCE_DIR}/imgui_widgets.cpp"
  CACHE INTERNAL "Set imgui source files"
)

install(
        DIRECTORY ${imgui_SOURCE_DIR}
        DESTINATION include/imgui
        PATTERN "CMakeLists.txt" EXCLUDE
)
