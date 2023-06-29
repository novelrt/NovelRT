cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

cmake_policy(SET CMP0077 NEW) # option() honors normal variables
cmake_policy(SET CMP0083 NEW) # control generation of PIE
cmake_policy(SET CMP0091 NEW) # MSVC runtime library flags
cmake_policy(SET CMP0135 NEW) # ExternalProject_Add respects timestamps

project(NovelRT
  VERSION 1.0.0
  DESCRIPTION "NovelRT Game Engine"
  HOMEPAGE_URL "https://novelrt.dev/"
  LANGUAGES CXX
)

include(CheckPIESupported)
check_pie_supported()

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/NovelRTConfigVersion.cmake
  COMPATIBILITY SameMajorVersion
)

enable_testing()
add_subdirectory(core)

install(
  EXPORT NovelRTConfig
  NAMESPACE NovelRT::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/NovelRT
)
install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/NovelRTConfigVersion.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/NovelRT
)
