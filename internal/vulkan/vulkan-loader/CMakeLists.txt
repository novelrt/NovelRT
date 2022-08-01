include(FetchContent)
message(STATUS "Fetching Vulkan Loader")

FetchContent_Declare(vulkan-loader
        URL https://github.com/KhronosGroup/Vulkan-Loader/archive/refs/tags/v1.3.211.tar.gz
        URL_HASH SHA512=b4c9716a0cb3d6748f69b91735e43a5fe51599f44c21f9c4d90e69daa05bddcfd354978e53e95d64cb6a6bcca640c48974d61893590ab443b230294d4668f245

        PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
        TMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/tmp"
        STAMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/stamp"
        DOWNLOAD_DIR "${CMAKE_CURRENT_BINARY_DIR}/dl"
        SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/src"
        SUBBUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/build"
        BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/bin"
        INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/inst"
        LOG_DIR "${CMAKE_CURRENT_BINARY_DIR}/log"
)

set(BUILD_WSI_WAYLAND_SUPPORT OFF CACHE INTERNAL "Enable Wayland support for OSes that support it")
set(ENABLE_WERROR OFF CACHE BOOL "Enable warnings as errors" FORCE)

NovelRTDeps_PopulateShared(vulkan-loader)

# Vulkan-loader's common options cause redefs if not explicitly defined like this for 1.3.211
target_compile_features(loader_common_options INTERFACE c_std_11)
set(LOADER_STANDARD_C_PROPERTIES PROPERTIES C_STANDARD 11)

