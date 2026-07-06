include(NovelRTBuildSystem)

set(previousFindFramework "${CMAKE_FIND_FRAMEWORK}")
set(CMAKE_FIND_FRAMEWORK LAST)
find_package(Vulkan "1.2" REQUIRED
  OPTIONAL_COMPONENTS MoltenVK)
if(APPLE)
  if(NOT Vulkan_MoltenVK_FOUND)
    message(SEND_ERROR "Could not find MoltenVK, which is required for graphics support")
  endif()
endif()
set(CMAKE_FIND_FRAMEWORK "${previousFindFramework}")


NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Graphics::Vulkan
  DEPENDS
    NovelRT::Exceptions
    NovelRT::Logging
    NovelRT::Threading
    NovelRT::Utilities

    NovelRT::Graphics::Core

  SOURCES
    VulkanGraphicsAdapter.cpp
    VulkanGraphicsAdapterSelector.cpp
    VulkanGraphicsBackendTraits.cpp
    VulkanGraphicsBuffer.cpp
    VulkanGraphicsCmdList.cpp
    VulkanGraphicsContext.cpp
    VulkanGraphicsDescriptorSet.cpp
    VulkanGraphicsDevice.cpp
    VulkanGraphicsFence.cpp
    VulkanGraphicsMemoryAllocator.cpp
    VulkanGraphicsPipeline.cpp
    VulkanGraphicsPipelineSignature.cpp
    VulkanGraphicsProvider.cpp
    VulkanGraphicsRenderPass.cpp
    VulkanGraphicsRenderTarget.cpp
    VulkanGraphicsResource.cpp
    VulkanGraphicsResourceMemoryRegion.cpp
    VulkanGraphicsSurfaceContext.cpp
    VulkanGraphicsSemaphore.cpp
    VulkanGraphicsSwapchain.cpp
    VulkanGraphicsSwapchainImage.cpp
    VulkanGraphicsTexture.cpp
    VulkanShaderProgram.cpp

  HEADERS
    include/NovelRT/Graphics/Vulkan/QueueFamilyIndices.hpp
    include/NovelRT/Graphics/Vulkan/SwapChainSupportDetails.hpp
    include/NovelRT/Graphics/Vulkan/VulkanGraphicsAdapter.hpp
    include/NovelRT/Graphics/Vulkan/VulkanGraphicsAdapterSelector.hpp
    include/NovelRT/Graphics/Vulkan/VulkanGraphicsBuffer.hpp
    include/NovelRT/Graphics/Vulkan/VulkanGraphicsCmdList.hpp
    include/NovelRT/Graphics/Vulkan/VulkanGraphicsContext.hpp
    include/NovelRT/Graphics/Vulkan/VulkanGraphicsDescriptorSet.hpp
    include/NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp
    include/NovelRT/Graphics/Vulkan/VulkanGraphicsFence.hpp
    include/NovelRT/Graphics/Vulkan/VulkanGraphicsMemoryAllocator.hpp
    include/NovelRT/Graphics/Vulkan/VulkanGraphicsPipeline.hpp
    include/NovelRT/Graphics/Vulkan/VulkanGraphicsPipelineSignature.hpp
    include/NovelRT/Graphics/Vulkan/VulkanGraphicsProvider.hpp
    include/NovelRT/Graphics/Vulkan/VulkanGraphicsRenderPass.hpp
    include/NovelRT/Graphics/Vulkan/VulkanGraphicsRenderTarget.hpp
    include/NovelRT/Graphics/Vulkan/VulkanGraphicsResource.hpp
    include/NovelRT/Graphics/Vulkan/VulkanGraphicsResourceMemoryRegion.hpp
    include/NovelRT/Graphics/Vulkan/VulkanGraphicsSurfaceContext.hpp
    include/NovelRT/Graphics/Vulkan/VulkanGraphicsSemaphore.hpp
    include/NovelRT/Graphics/Vulkan/VulkanGraphicsSwapchain.hpp
    include/NovelRT/Graphics/Vulkan/VulkanGraphicsSwapchainImage.hpp
    include/NovelRT/Graphics/Vulkan/VulkanGraphicsTexture.hpp
    include/NovelRT/Graphics/Vulkan/VulkanShaderProgram.hpp
    include/NovelRT/Graphics/Vulkan/Utilities/BufferUsageKind.hpp
    include/NovelRT/Graphics/Vulkan/Utilities/ImageLayout.hpp
    include/NovelRT/Graphics/Vulkan/Utilities/MemoryAccessMode.hpp
    include/NovelRT/Graphics/Vulkan/Utilities/PipelineBlendFactor.hpp
    include/NovelRT/Graphics/Vulkan/Utilities/PipelineVisibility.hpp
    include/NovelRT/Graphics/Vulkan/Utilities/ShaderProgramVisibility.hpp
    include/NovelRT/Graphics/Vulkan/Utilities/Support.hpp
    include/NovelRT/Graphics/Vulkan/Utilities/Texel.hpp
    include/NovelRT/Graphics/Vulkan/Utilities/TextureAddressMode.hpp

  PRECOMPILE_HEADERS
    INTERFACE
      $<BUILD_INTERFACE:<NovelRT/Graphics/Vulkan/QueueFamilyIndices.hpp$<ANGLE-R>>
      $<BUILD_INTERFACE:<NovelRT/Graphics/Vulkan/SwapChainSupportDetails.hpp$<ANGLE-R>>
      $<BUILD_INTERFACE:<NovelRT/Graphics/Vulkan/VulkanGraphicsAdapter.hpp$<ANGLE-R>>
      $<BUILD_INTERFACE:<NovelRT/Graphics/Vulkan/VulkanGraphicsAdapterSelector.hpp$<ANGLE-R>>
      $<BUILD_INTERFACE:<NovelRT/Graphics/Vulkan/VulkanGraphicsBuffer.hpp$<ANGLE-R>>
      $<BUILD_INTERFACE:<NovelRT/Graphics/Vulkan/VulkanGraphicsCmdList.hpp$<ANGLE-R>>
      $<BUILD_INTERFACE:<NovelRT/Graphics/Vulkan/VulkanGraphicsContext.hpp$<ANGLE-R>>
      $<BUILD_INTERFACE:<NovelRT/Graphics/Vulkan/VulkanGraphicsDescriptorSet.hpp$<ANGLE-R>>
      $<BUILD_INTERFACE:<NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp$<ANGLE-R>>
      $<BUILD_INTERFACE:<NovelRT/Graphics/Vulkan/VulkanGraphicsFence.hpp$<ANGLE-R>>
      $<BUILD_INTERFACE:<NovelRT/Graphics/Vulkan/VulkanGraphicsMemoryAllocator.hpp$<ANGLE-R>>
      $<BUILD_INTERFACE:<NovelRT/Graphics/Vulkan/VulkanGraphicsPipeline.hpp$<ANGLE-R>>
      $<BUILD_INTERFACE:<NovelRT/Graphics/Vulkan/VulkanGraphicsPipelineSignature.hpp$<ANGLE-R>>
      $<BUILD_INTERFACE:<NovelRT/Graphics/Vulkan/VulkanGraphicsProvider.hpp$<ANGLE-R>>
      $<BUILD_INTERFACE:<NovelRT/Graphics/Vulkan/VulkanGraphicsRenderPass.hpp$<ANGLE-R>>
      $<BUILD_INTERFACE:<NovelRT/Graphics/Vulkan/VulkanGraphicsRenderTarget.hpp$<ANGLE-R>>
      $<BUILD_INTERFACE:<NovelRT/Graphics/Vulkan/VulkanGraphicsResource.hpp$<ANGLE-R>>
      $<BUILD_INTERFACE:<NovelRT/Graphics/Vulkan/VulkanGraphicsResourceMemoryRegion.hpp$<ANGLE-R>>
      $<BUILD_INTERFACE:<NovelRT/Graphics/Vulkan/VulkanGraphicsSurfaceContext.hpp$<ANGLE-R>>
      $<BUILD_INTERFACE:<NovelRT/Graphics/Vulkan/VulkanGraphicsSemaphore.hpp$<ANGLE-R>>
      $<BUILD_INTERFACE:<NovelRT/Graphics/Vulkan/VulkanGraphicsSwapchain.hpp$<ANGLE-R>>
      $<BUILD_INTERFACE:<NovelRT/Graphics/Vulkan/VulkanGraphicsSwapchainImage.hpp$<ANGLE-R>>
      $<BUILD_INTERFACE:<NovelRT/Graphics/Vulkan/VulkanGraphicsTexture.hpp$<ANGLE-R>>
      $<BUILD_INTERFACE:<NovelRT/Graphics/Vulkan/VulkanShaderProgram.hpp$<ANGLE-R>>
      $<BUILD_INTERFACE:<NovelRT/Graphics/Vulkan/Utilities/BufferUsageKind.hpp$<ANGLE-R>>
      $<BUILD_INTERFACE:<NovelRT/Graphics/Vulkan/Utilities/ImageLayout.hpp$<ANGLE-R>>
      $<BUILD_INTERFACE:<NovelRT/Graphics/Vulkan/Utilities/MemoryAccessMode.hpp$<ANGLE-R>>
      $<BUILD_INTERFACE:<NovelRT/Graphics/Vulkan/Utilities/PipelineBlendFactor.hpp$<ANGLE-R>>
      $<BUILD_INTERFACE:<NovelRT/Graphics/Vulkan/Utilities/PipelineVisibility.hpp$<ANGLE-R>>
      $<BUILD_INTERFACE:<NovelRT/Graphics/Vulkan/Utilities/ShaderProgramVisibility.hpp$<ANGLE-R>>
      $<BUILD_INTERFACE:<NovelRT/Graphics/Vulkan/Utilities/Support.hpp$<ANGLE-R>>
      $<BUILD_INTERFACE:<NovelRT/Graphics/Vulkan/Utilities/Texel.hpp$<ANGLE-R>>
      $<BUILD_INTERFACE:<NovelRT/Graphics/Vulkan/Utilities/TextureAddressMode.hpp$<ANGLE-R>>

  LINK_LIBRARIES
    PUBLIC
      Vulkan::Vulkan
      GPUOpen::VulkanMemoryAllocator

  DYNAMIC_LIBRARIES
    $<$<TARGET_EXISTS:Vulkan::MoltenVK>:$<TARGET_FILE:Vulkan::MoltenVK>>
)
