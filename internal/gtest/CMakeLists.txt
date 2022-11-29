include(FetchContent)
message(STATUS "Fetching Google Test")

FetchContent_Declare(googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
  URL_HASH SHA512=1479ea2f3172c622c0ca305f5b2bc45a42941221ec0ac7865e6d6d020ec4d008d952fc64e01a4c5138d7bed4148cf75596f25bb9e9044a98bbbf5662053ea11c

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

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(INSTALL_GTEST ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
if(APPLE)
  set_target_properties(gtest PROPERTIES NO_SONAME TRUE)
  set_target_properties(gtest_main PROPERTIES NO_SONAME TRUE)
  target_link_options(gtest PRIVATE -install_name @rpath/libgtest.dylib)
  target_link_options(gtest_main PRIVATE -install_name @rpath/libgtest_main.dylib)
endif()
