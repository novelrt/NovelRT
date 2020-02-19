cmake_minimum_required(VERSION 3.13)

project(vcpkg)

include(ExternalProject)

set(_vcpkg_root "vcpkg")
mark_as_advanced(_vcpkg_root)

if(${CMAKE_HOST_WIN32})
  set(_vcpkg_configure_command "$<SHELL_PATH:${CMAKE_BINARY_DIR}/src/${_vcpkg_root}/bootstrap-vcpkg.bat>")
else()
  set(_vcpkg_configure_command "$<SHELL_PATH:${CMAKE_BINARY_DIR}/src/${_vcpkg_root}/bootstrap-vcpkg.sh>")
endif()

mark_as_advanced(_vcpkg_configure_command)

ExternalProject_Add(vcpkg
  PREFIX "."

  GIT_REPOSITORY https://github.com/capnkenny/vcpkg
  GIT_TAG c4a13e2a13d6cf84bc64041fb702c9e863747f6d
  GIT_SHALLOW true

  CONFIGURE_COMMAND ""
  BUILD_COMMAND "${_vcpkg_configure_command}"
  INSTALL_COMMAND ""
  TEST_COMMAND "")
