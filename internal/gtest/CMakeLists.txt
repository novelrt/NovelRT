include(FetchContent)
include(functions/NovelRTDeps_Populate)
message(STATUS "Fetching Google Test...")

# For Windows: Prevent overriding the parent project's compiler/linker settings
if(WIN32)
  set(gtest_force_shared_crt ON)
endif()

set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

FetchContent_Declare(GoogleTest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
  URL_HASH SHA512=5d8518ccd783943a03dfbbc06c9001d2a657dfae531e2353ca9b557cf4eac02399a6a2d661500ad5e57fd93b8cd257b6d4a5e8b703d30bd9a9b5fbb85d451b5e

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

NovelRTDeps_Populate(GoogleTest)
