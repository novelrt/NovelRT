include(FindPackageHandleStandardArgs)

find_path(nethost_INCLUDE_DIR NAMES nethost.h)
find_library(nethost_LIBRARY NAMES libnethost nethost)

find_package_handle_standard_args(nethost
  REQUIRED_VARS nethost_INCLUDE_DIR nethost_LIBRARY)

mark_as_advanced(nethost_INCLUDE_DIR nethost_LIBRARY)

if(nethost_FOUND)
  set(NETHOST_INCLUDE_DIR ${nethost_INCLUDE_DIR})
  set(NETHOST_LIBRARIES ${nethost_LIBRARY})
endif()
