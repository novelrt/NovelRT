include(FetchContent)
message(STATUS "Fetching Vulkan Loader")

FetchContent_Declare(vulkan-loader
        URL https://github.com/KhronosGroup/Vulkan-Loader/archive/refs/tags/v1.2.198.tar.gz
        URL_HASH SHA512=39c2b49a73b031cd4039cc7cc00a24bdcd0ec6dbb06a62943d534a7b5c48c70c6ca0d3359834c98f294199e253ad3e523225f30179914abeb2b2df9a49c1580a

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
