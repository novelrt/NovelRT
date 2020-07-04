# Finds the .NET Core host library

# This can be configured with the following cmake variables:
# nethost_ROOT_DIR
# nethost_INCLUDE_DIR
# nethost_LIBRARY

# Or, alternatively, the following environment variables:
# nethost_INSTALL_DIR
# LIBRARY_PATH


include(FindPackageHandleStandardArgs)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  set(nethost_DEFAULT_SEARCH_DIR "C:/Program Files/dotnet/shared/Microsoft.NETCore.App")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  message(FATAL_ERROR "Findnethost does not yet support Darwin")
  set(nethost_DEFAULT_SEARCH_DIR)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(nethost_DEFAULT_SEARCH_DIR "/usr/share/dotnet/shared/Microsoft.NETCore.App")
endif()

file(GLOB nethost_versions
  LIST_DIRECTORIES true
  RELATIVE "${nethost_DEFAULT_SEARCH_DIR}"
  "${nethost_DEFAULT_SEARCH_DIR}/*"
)

foreach(version ${nethost_versions})
  string(REGEX REPLACE "[0-9]+\\.[0-9]+\\.[0-9]+\\-" "" nethost_semver "${nethost_VERSION}")
  string(REGEX REPLACE "[0-9]+\\.[0-9]+\\.[0-9]+\\-" "" version_semver "${version}")
  if(nethost_VERSION VERSION_LESS version)
    set(nethost_VERSION ${version})
  elseif(nethost_semver STRLESS version_semver)
    set(nethost_VERSION ${version})
  endif()
endforeach()

set(nethost_DEFAULT_SEARCH_DIR
  "${nethost_DEFAULT_SEARCH_DIR}/${nethost_VERSION}/")

set(nethost_SEARCH_DIR ${nethost_ROOT_DIR} $ENV{nethost_INSTALL_DIR})

find_path(nethost_INCLUDE_DIRS nethost.h
  HINTS ${nethost_INCLUDE_DIR} ${nethost_SEARCH_DIR}
  PATHS ${nethost_DEFAULT_SEARCH_DIR}
  PATH_SUFFIXES include)

find_library(nethost_LIBRARIES
  NAMES nethost libnethost
  HINTS ${nethost_LIBRARY} ${nethost_SEARCH_DIR}
  PATHS ${nethost_DEFAULT_SEARCH_DIR} ENV LIBRARY_PATH
  PATH_SUFFIXES ${nethost_LIB_PATH_SUFFIX})

find_package_handle_standard_args(nethost
  REQUIRED_VARS nethost_INCLUDE_DIRS nethost_LIBRARIES)

if(nethost_FOUND)
  add_library(nethost SHARED IMPORTED)
  set_target_properties(nethost PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES ${nethost_INCLUDE_DIRS}
    IMPORTED_LOCATION ${nethost_LIBRARIES})
endif()
