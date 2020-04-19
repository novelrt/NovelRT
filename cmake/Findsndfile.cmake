# Findsndfile
# --------
#
# Finds the sndfile library.
#
# This will define the following variables:
#   SNDFILE_FOUND   - True if the system has found sndfile
#   SNDFILE_VERSION - The full version string which was found
#
# And the following imported targets:
#  sndfile::sndfile - The sndfile library
#
# Note the lack of SNDFILE_LIBRARIES or SNDFILE_INCLUDE_DIRS.
#

cmake_policy(PUSH)
cmake_policy(SET CMP0077 NEW)

if (DEFINED PACKAGE_VERSION_EXACT)
  find_package(sndfile ${sndfile_FIND_VERSION} EXACT CONFIG QUIET)
else()
  find_package(sndfile ${sndfile_FIND_VERSION} CONFIG QUIET)
endif()

if(NOT sndfile_FOUND OR NOT TARGET sndfile-static)
  find_package(PkgConfig)
  pkg_check_modules(PC_SNDFILE QUIET sndfile)

  find_path(SNDFILE_INCLUDE_DIR
    NAMES sndfile.h
    PATHS ${PC_SNDFILE_INCLUDE_DIRS}
    PATH_SUFFIXES sndfile
  )

  find_library(SNDFILE_LIBRARY
    NAMES sndfile
    PATHS ${PC_SNDFILE_LIBRARY_DIRS}
  )

  if(PC_SNDFILE_VERSION)
    set(SNDFILE_VERSION ${PC_SNDFILE_VERSION})

    include(FindPackageHandleStandardArgs)
    find_package_handle_standard_args(sndfile
      FOUND_VAR SNDFILE_FOUND
      REQUIRED_VARS
        SNDFILE_LIBRARY
        SNDFILE_INCLUDE_DIR
      VERSION_VAR SNDFILE_VERSION
    )

    add_library(sndfile::sndfile UNKNOWN IMPORTED)
    set_target_properties(sndfile::sndfile PROPERTIES
      IMPORTED_LOCATION "${sndfile_LIBRARY}"
      INTERFACE_COMPILE_OPTIONS "${PC_SNDFILE_CFLAGS_OTHER}"
      INTERFACE_INCLUDE_DIRECTORIES "${sndfile_INCLUDE_DIR}"
    )
  elseif(SNDFILE_INCLUDE_DIR)
    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/sndfile-version.c" [[
  #include "sndfile.h"
  #include "stdio.h"

  int main()
  {
    const char *version = sf_version_string();
    printf("%s\n", version);

    return 0;
  }
  ]])

    try_run(_run_status _compile_status
      "${CMAKE_CURRENT_BINARY_DIR}/"
      "${CMAKE_CURRENT_BINARY_DIR}/sndfile-version.c"
      LINK_LIBRARIES "${SNDFILE_LIBRARY}"
      RUN_OUTPUT_VARIABLE _version)

    string(REGEX REPLACE "libsndfile\\-([0-9\\.]+).*" "\\1"
      SNDFILE_VERSION "${_version}")

    include(FindPackageHandleStandardArgs)
    find_package_handle_standard_args(sndfile
      FOUND_VAR SNDFILE_FOUND
      REQUIRED_VARS
        SNDFILE_LIBRARY
        SNDFILE_INCLUDE_DIR
      VERSION_VAR SNDFILE_VERSION
    )

    add_library(sndfile::sndfile UNKNOWN IMPORTED)
    set_target_properties(sndfile::sndfile PROPERTIES
      IMPORTED_LOCATION "${SNDFILE_LIBRARY}"
      INTERFACE_COMPILE_OPTIONS "${PC_SNDFILE_CFLAGS_OTHER}"
      INTERFACE_INCLUDE_DIRECTORIES "${sndfile_INCLUDE_DIR}"
    )
  else()
    include(FetchContent)

    FetchContent_Declare(sndfile
      GIT_REPOSITORY https://github.com/erikd/libsndfile
      GIT_TAG "${SNDFILE_FIND_VERSION}")

    FetchContent_MakeAvailable(sndfile)
    FetchContent_GetProperties(sndfile BINARY_DIR _sndfile_binary_dir)

    add_library(sndfile::sndfile ALIAS sndfile)

    include(FindPackageHandleStandardArgs)
    find_package_handle_standard_args(sndfile
      FOUND_VAR SNDFILE_FOUND
      REQUIRED_VARS _sndfile_binary_dir
      VERSION_VAR SNDFILE_VERSION
    )
  endif()

endif()

cmake_policy(POP)
