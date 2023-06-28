include(FetchContent)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON)
set(BUILD_GMOCK OFF)
set(INSTALL_GTEST ON)

FetchContent_MakeAvailable(GTest)

if(APPLE)
  set_target_properties(gtest PROPERTIES NO_SONAME TRUE)
  set_target_properties(gtest_main PROPERTIES NO_SONAME TRUE)
  target_link_options(gtest PRIVATE -install_name @rpath/libgtest.dylib)
  target_link_options(gtest_main PRIVATE -install_name @rpath/libgtest_main.dylib)
endif()
