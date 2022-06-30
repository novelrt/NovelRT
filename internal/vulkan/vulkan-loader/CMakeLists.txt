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

FetchContent_GetProperties(vulkan-loader)
if(NOT vulkan-loader_POPULATED)
  FetchContent_Populate(vulkan-loader)

  # Workaround to force vulkan-loader to build shared and not always export symbols
  # Causes failures during builds so we forcefully change these for vulkan-loader only
  # Credit: https://stackoverflow.com/a/62103349
  set(BUILD_SHARED_LIBS_OLD ${BUILD_SHARED_LIBS})
  # Make subproject to use 'BUILD_SHARED_LIBS=ON' setting.
  set(BUILD_SHARED_LIBS ON CACHE INTERNAL "Build SHARED libraries")
  set(BUILD_WSI_WAYLAND_SUPPORT OFF CACHE INTERNAL "")
  add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/src ${CMAKE_CURRENT_BINARY_DIR}/bin)
  # Set the values back to what they originally were
  set(BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS_OLD} CACHE BOOL "Type of libraries to build" FORCE)

  #For 1.3.211 - Vulkan is specifying C99 to compile its ASM target which breaks due to redefinitions.
  target_compile_features(loader_common_options INTERFACE c_std_11)
  set(LOADER_STANDARD_C_PROPERTIES PROPERTIES C_STANDARD 11)
endif()
