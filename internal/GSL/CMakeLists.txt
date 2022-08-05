include(FetchContent)
include(functions/NovelRTDeps_Populate)
message(STATUS "Fetching GSL...")

FetchContent_Declare(GSL
  URL https://github.com/microsoft/GSL/archive/refs/tags/v4.0.0.zip
  URL_HASH SHA512=710ab8b06b24dbca2cd1a8abb2eca2282548644224519784d04b1c7b70e3639f3b3e8d8f993f7f8c3dce3fcfe9ff0f3757b8d2625b676df36c84caa6f684133e

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

NovelRTDeps_PopulateHeaderOnly(GSL)

install(
  DIRECTORY ${GSL_SOURCE_DIR}/include/
  DESTINATION include
  PATTERN "CMakeLists.txt" EXCLUDE
)
