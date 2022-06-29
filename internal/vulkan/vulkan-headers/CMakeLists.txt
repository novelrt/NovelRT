include(FetchContent)
message(STATUS "Fetching Vulkan Headers")

FetchContent_Declare(vulkan-headers
        URL https://github.com/KhronosGroup/Vulkan-Headers/archive/refs/tags/v1.3.211.tar.gz
        URL_HASH SHA512=95fb29ad5c79809506ce3587f974baf360d21d036995dd7297f966962380cd0504e9886a549ca34dfd5e051ccc2bf96bd0401eeac9c37ae76a2979d921572398

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

  # Workaround to force vulkan-headers to build shared and not always export symbols
  # Causes failures during builds so we forcefully change these for vulkan-headers only
  # Credit: https://stackoverflow.com/a/62103349
  set(BUILD_SHARED_LIBS_OLD ${BUILD_SHARED_LIBS})
  # Make subproject to use 'BUILD_SHARED_LIBS=ON' setting.
  set(BUILD_SHARED_LIBS ON CACHE INTERNAL "Build SHARED libraries")
  add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/src ${CMAKE_CURRENT_BINARY_DIR}/bin)
  # Set the values back to what they originally were
  set(BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS_OLD} CACHE BOOL "Type of libraries to build" FORCE)
endif()
