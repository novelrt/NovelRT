include(FetchContent)
include(functions/NovelRTDeps_Populate)
message(STATUS "Fetching Vulkan Loader...")

set(BUILD_WSI_WAYLAND_SUPPORT OFF CACHE INTERNAL "")
set(LOADER_STANDARD_C_PROPERTIES PROPERTIES C_STANDARD 11)

FetchContent_Declare(VulkanLoader
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

NovelRTDeps_PopulateExplicit(VulkanLoader SHARED)

add_library(Vulkan::Vulkan ALIAS vulkan)

# For 1.3.211 - Vulkan is specifying C99 to compile its ASM target which breaks due to redefinitions.
target_compile_features(loader_common_options INTERFACE c_std_11)

set(NOVELRT_VULKAN_TARGET "vulkan" CACHE STRING "Vulkan Dependencies to attach to NovelRT Engine" FORCE)
set(NOVELRT_VULKAN_DEPS "vulkan" CACHE STRING "Vulkan Dependencies to attach to NovelRT Engine" FORCE)
