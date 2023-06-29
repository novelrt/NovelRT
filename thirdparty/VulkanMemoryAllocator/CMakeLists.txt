include(FetchContent)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

#set(VMA_STATIC_VULKAN_FUNCTIONS ON) #todo: I have no idea if this is doing what I want, not even sure we need it, I saw it in the VMA CMake and got desperate. :)
set(BUILD_SHARED_LIBS OFF)

FetchContent_MakeAvailable(VulkanMemoryAllocator)
