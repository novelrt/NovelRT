include(FetchContent)
message(STATUS "Fetching VulkanMemoryAllocator")

FetchContent_Declare(VulkanMemoryAllocator
        URL https://github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator/archive/0aa3989b8f382f185fdf646cc83a1d16fa31d6ab.zip
        URL_HASH SHA512=e9eeed2f5cc1130613b9440bf375e5574b58e800f4615cc771176644951eadc9e49cff91c5d303e63831fbdc76f354d2ad9a9da11826588ede76a7252c7a636a

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

#set(VMA_STATIC_VULKAN_FUNCTIONS ON) #todo: I have no idea if this is doing what I want, not even sure we need it, I saw it in the VMA CMake and got desperate. :)
set(BUILD_SHARED_LIBS OFF)

FetchContent_MakeAvailable(VulkanMemoryAllocator)
