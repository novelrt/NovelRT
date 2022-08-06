include(FetchContent)
include(functions/NovelRTDeps_Populate)
message(STATUS "Fetching Vulkan Headers...")

FetchContent_Declare(VulkanHeaders
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

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS OFF)

NovelRTDeps_PopulateExplicit(VulkanHeaders ${type})
