include(FetchContent)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON)
set(BUILD_GMOCK OFF)
set(INSTALL_GTEST ON)

FetchContent_MakeAvailable(GTest)
