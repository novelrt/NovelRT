include(FetchContent)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

set(SPDLOG_INSTALL ON)
set(SPDLOG_ENABLE_PCH ON)

FetchContent_MakeAvailable(spdlog)

set_property(TARGET spdlog PROPERTY POSITION_INDEPENDENT_CODE ON)

if(APPLE)
  set_target_properties(spdlog PROPERTIES NO_SONAME TRUE)
  target_link_options(spdlog PRIVATE -install_name @rpath/libspdlog.dylib)
endif()
