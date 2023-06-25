include(FetchContent)
message(STATUS "Fetching VulkanMemoryAllocator")

FetchContent_Declare(VulkanMemoryAllocator
        URL https://github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator/archive/refs/tags/v3.0.1.zip
        URL_HASH SHA512=1BE4D3A84C9206944E40975D839C85998D14FAEA6B0CA81CD1A2F9D49EFDE4E5D5E7096052DDA509EF11856A80C0F4E345A97DB9D0F9BA1EA9C6279E590A13AF

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

set(VMA_STATIC_VULKAN_FUNCTIONS ON) #todo: I have no idea if this is doing what I want, not even sure we need it, I saw it in the VMA CMake and got desperate. :)
set(BUILD_SHARED_LIBS OFF)

FetchContent_MakeAvailable(VulkanMemoryAllocator)