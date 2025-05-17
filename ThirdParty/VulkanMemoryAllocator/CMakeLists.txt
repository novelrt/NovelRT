include(FetchContent)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

set(VMA_ENABLE_INSTALL ON)
set(VMA_BUILD_DOCUMENTATION OFF)
set(VMA_BUILD_SAMPLES OFF)

FetchContent_MakeAvailable(VulkanMemoryAllocator)
