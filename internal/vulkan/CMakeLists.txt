message(STATUS "Searching for Vulkan SDK...")

if(NOT ${NOVELRT_VULKAN_SDK_PATH} STREQUAL "")
  set(ENV{VULKAN_SDK} ${NOVELRT_VULKAN_SDK_PATH})
endif()

find_package(Vulkan ${NOVELRT_VULKAN_VERSION})

option(NOVELRT_VULKAN_SDK "NovelRT will use the Vulkan SDK instead of vendored libs" OFF)
set(NOVELRT_VULKAN_DEPS "" CACHE STRING "Vulkan Dependencies to attach to NovelRT Engine")
set(NOVELRT_VULKAN_TARGET "" CACHE STRING "Vulkan target NovelRT will refer to")

if(NOT Vulkan_FOUND)
  message(STATUS "Vulkan SDK not found! Attempting to vendor required Vulkan dependencies.")
  add_subdirectory(vulkan-headers)
  add_subdirectory(vulkan-loader)
  set(NOVELRT_VULKAN_TARGET "vulkan" CACHE STRING "Vulkan Dependencies to attach to NovelRT Engine" FORCE)
  set(NOVELRT_VULKAN_DEPS "vulkan" CACHE STRING "Vulkan Dependencies to attach to NovelRT Engine" FORCE)
  
  if(APPLE)
    add_subdirectory(moltenvk)
    set(NOVELRT_VULKAN_DEPS "${NOVELRT_VULKAN_DEPS} moltenvk")
  endif()
else()
  set(NOVELRT_VULKAN_SDK ON CACHE BOOL "NovelRT will use the Vulkan SDK instead of vendored libs" FORCE)
  set(NOVELRT_VULKAN_DEPS "Vulkan::Vulkan" CACHE STRING "Vulkan Dependencies to attach to NovelRT Engine" FORCE)
  set(NOVELRT_VULKAN_TARGET "Vulkan::Vulkan" CACHE STRING "Vulkan Dependencies to attach to NovelRT Engine" FORCE)
  set(NOVELRT_MOLTENVK_VENDORED OFF CACHE BOOL "Setting to indicate if NovelRT is vendoring MoltenVK" FORCE)
endif()
