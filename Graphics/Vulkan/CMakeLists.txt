find_package(Vulkan "1.2" REQUIRED
  OPTIONAL_COMPONENTS MoltenVK)
if(APPLE AND NOT Vulkan_MoltenVK_FOUND)
  message(SEND_ERROR "Could not find MoltenVK, which is required for graphics support")
endif()

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Graphics::Vulkan
  DEPENDS
    NovelRT::Graphics::Core

  SOURCES
    PRIVATE
      VulkanGraphicsAdapter.cpp
      VulkanGraphicsAdapterSelector.cpp
      VulkanGraphicsBuffer.cpp
      VulkanGraphicsCmdList.cpp
      VulkanGraphicsContext.cpp
      VulkanGraphicsDescriptorSet.cpp
      VulkanGraphicsDevice.cpp
      VulkanGraphicsFence.cpp
      VulkanGraphicsMemoryAllocator.cpp
      VulkanGraphicsPipeline.cpp
      VulkanGraphicsPipelineSignature.cpp
      VulkanGraphicsPluginProvider.cpp
      VulkanGraphicsResource.cpp
      VulkanGraphicsResourceMemoryRegion.cpp
      VulkanGraphicsProvider.cpp
      VulkanGraphicsRenderPass.cpp
      VulkanGraphicsSurfaceContext.cpp
      VulkanGraphicsTexture.cpp
      VulkanShaderProgram.cpp
      VulkanGraphicsBackendTraits.cpp

  HEADERS
    PUBLIC
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
      include/NovelRT/Graphics/Vulkan/VulkanGraphicsResource.hpp
      include/NovelRT/Graphics/Vulkan/VulkanGraphicsResourceMemoryRegion.hpp
      include/NovelRT/Graphics/Vulkan/VulkanGraphicsSurfaceContext.hpp
      include/NovelRT/Graphics/Vulkan/VulkanGraphicsTexture.hpp
      include/NovelRT/Graphics/Vulkan/VulkanShaderProgram.hpp
      include/NovelRT/Graphics/Vulkan/Utilities/BufferUsageKind.hpp
      include/NovelRT/Graphics/Vulkan/Utilities/MemoryAccessMode.hpp
      include/NovelRT/Graphics/Vulkan/Utilities/PipelineBlendFactor.hpp
      include/NovelRT/Graphics/Vulkan/Utilities/PipelineVisibility.hpp
      include/NovelRT/Graphics/Vulkan/Utilities/ShaderProgramVisibility.hpp
      include/NovelRT/Graphics/Vulkan/Utilities/Support.hpp
      include/NovelRT/Graphics/Vulkan/Utilities/Texel.hpp
      include/NovelRT/Graphics/Vulkan/Utilities/TextureAddressMode.hpp

  LINK_LIBRARIES
    PUBLIC
      Vulkan::Vulkan
      GPUOpen::VulkanMemoryAllocator
)
