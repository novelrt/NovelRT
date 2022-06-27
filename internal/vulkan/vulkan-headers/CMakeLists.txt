include(FetchContent)
message(STATUS "Fetching Vulkan Headers")

FetchContent_Declare(vulkan-headers
        URL https://github.com/KhronosGroup/Vulkan-Headers/archive/refs/tags/v1.2.198.tar.gz
        URL_HASH SHA512=12b0e50807f04dbfb2f7d448b09d037422dcf0d613fc4943c8cb086c23c257e79025c9078ae89d6d8f68bd38aa8123f37a98d80894df308880b101083ae520c6

        PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
        TMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/tmp"
        STAMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/stamp"
        DOWNLOAD_DIR "${CMAKE_CURRENT_BINARY_DIR}/dl"
        SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/src"
        SUBBUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/build"
        INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/inst"
        LOG_DIR "${CMAKE_CURRENT_BINARY_DIR}/log"
)

FetchContent_GetProperties(vulkan-headers)
if(NOT vulkan-headers_POPULATED)
  FetchContent_Populate(vulkan-headers)

  # Workaround to force onevulkan-headers to build shared and not always export symbols
  # Causes failures during builds so we forcefully change these for onevulkan-headers only
  # Credit: https://stackoverflow.com/a/62103349
  set(BUILD_SHARED_LIBS_OLD ${BUILD_SHARED_LIBS})
  # Make subproject to use 'BUILD_SHARED_LIBS=ON' setting.
  set(BUILD_SHARED_LIBS ON CACHE INTERNAL "Build SHARED libraries")
  add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/src ${CMAKE_CURRENT_BINARY_DIR}/bin)
  # Set the values back to what they originally were
  set(BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS_OLD} CACHE BOOL "Type of libraries to build" FORCE)
endif()
