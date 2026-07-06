# Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT).
# See LICENCE.md in the repository root for more information.

#[=======================================================================[.rst:
XCFrameworkUtilities
-------------

This module defines utilities for handling XCFrameworks.
#]=======================================================================]

block(SCOPE_FOR POLICIES)
cmake_policy(VERSION 3.29..3.31)

#[=======================================================================[.rst:
.. command:: xcframework_select_libraries

  This function selects libraries from the given framework that function on the
  given platform/variant combination.
#]=======================================================================]
function(xcframework_select_libraries framework outputVariable platform variant)
  # This mostly mirrors the logic in cmXcFramework.cpp used for parsing xcframework info plists.
  execute_process(
    COMMAND "/usr/bin/plutil" "-convert" "json" "-o" "-" "${framework}/Info.plist"
    OUTPUT_VARIABLE infoJson)

  string(JSON packageType GET "${infoJson}" "CFBundlePackageType")
  string(JSON formatVersion GET "${infoJson}" "XCFrameworkFormatVersion")

  if(NOT "${packageType}" STREQUAL "XFWK" OR NOT "${formatVersion}" STREQUAL "1.0")
    message(FATAL_ERROR [[Expected:]] "\n" "${framework}/Info.plist" "\n" [[to have CFBundlePackageType "XFWK" and XCFrameworkFormatVersion "1.0"]])
  endif()

  string(JSON availableLibraries GET "${infoJson}" "AvailableLibraries")
  string(JSON numberOfLibraries LENGTH "${availableLibraries}")
  foreach(libraryIndex RANGE "${numberOfLibraries}")
    string(JSON library GET "${availableLibraries}" "${libraryIndex}")

    string(JSON libraryIdentifier GET "${library}" "LibraryIdentifier")
    string(JSON libraryPath GET "${library}" "LibraryPath")
    string(JSON headersPath GET "${library}" "HeadersPath")
    string(JSON supportedArchitectures GET "${library}" "SupportedArchitectures")
    string(JSON supportedPlatforms GET "${library}" "SupportedPlatforms")
    string(JSON supportedPlatformVariants GET "${library}" "SupportedPlatformVariant")

    message(STATUS "LIBRARY: ${libraryIdentifier}")
    message(STATUS "  PATH: ${libraryPath}")
    message(STATUS "  HEADERS: ${headersPath}")
    message(STATUS "  ARCHITECTURES: ${supportedArchitectures}")
    message(STATUS "  PLATFORMS: ${supportedPlatforms}")
    message(STATUS "  VARIANTS: ${supportedPlatformVariants}")
  endforeach()

  set("${outputVariable}" "" PARENT_SCOPE)
endfunction()

endblock()
