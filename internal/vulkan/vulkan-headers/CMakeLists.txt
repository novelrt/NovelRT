include(FetchContent)
message(STATUS "Fetching Vulkan Headers")

FetchContent_Declare(vulkan-headers
        URL https://github.com/KhronosGroup/Vulkan-Headers/archive/refs/tags/v1.3.216.tar.gz
        URL_HASH SHA512=25bd561227145e144866749c6a8b83eab9f67a03d62b5277758d93125b2283facff74ad1876280d357a4ae67f20b5b17a2a6168514c4b7fad3d9c3ff8a2ba51f

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
