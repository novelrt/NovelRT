include(FetchContent)
message(STATUS "Fetching Vulkan Loader")

FetchContent_Declare(vulkan-loader
        URL https://github.com/KhronosGroup/Vulkan-Loader/archive/refs/tags/v1.3.216.tar.gz
        URL_HASH SHA512=a42e1c48a5c2832df7ee94aaa0a7c517b9f5d3289df91ba52157db44f20757d904f552ddd9b1720fc5752303ef390e637de107308b119d52edecda2d70229049

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

FetchContent_GetProperties(vulkan-loader)
if(NOT vulkan-loader_POPULATED)
  FetchContent_Populate(vulkan-loader)

  # Workaround to force onevulkanloader to build shared and not always export symbols
  # Causes failures during builds so we forcefully change these for onevulkanloader only
  # Credit: https://stackoverflow.com/a/62103349
  set(BUILD_SHARED_LIBS_OLD ${BUILD_SHARED_LIBS})
  # Make subproject to use 'BUILD_SHARED_LIBS=ON' setting.
  set(BUILD_SHARED_LIBS ON CACHE INTERNAL "Build SHARED libraries")
  add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/src ${CMAKE_CURRENT_BINARY_DIR}/bin)
  # Set the values back to what they originally were
  set(BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS_OLD} CACHE BOOL "Type of libraries to build" FORCE)
endif()
