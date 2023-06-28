include(FetchContent)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

set(ZLIB_COMPAT ON)
set(ZLIB_ENABLE_TESTS OFF)

FetchContent_MakeAvailable(ZLIB)

set_target_properties(zlib
  PROPERTIES
    POSITION_INDEPENDENT_CODE ON)

install(
  TARGETS zlib
  EXPORT ZLIBExports
)
install(
  EXPORT ZLIBExports
  NAMESPACE ZLIB::
  DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/lib"
)

if(NOT TARGET ZLIB::zlib)
  add_library(ZLIB::zlib ALIAS zlib)
endif()

if(APPLE)
  set_target_properties(zlib PROPERTIES NO_SONAME TRUE)
  target_link_options(zlib PRIVATE -install_name @rpath/libz.dylib)
endif()

#install(EXPORT ZLIBConfig
#  DESTINATION lib/cmake/ZLIB
#  NAMESPACE ZLIB::)
#install(TARGETS zlib
#  EXPORT ZLIBConfig
#  LIBRARY DESTINATION lib)
