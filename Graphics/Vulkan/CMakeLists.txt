add_library(NovelRT-Graphics-Vulkan OBJECT
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
)

target_sources(NovelRT-Graphics-Vulkan
  PUBLIC
    FILE_SET public_headers
    TYPE HEADERS
    BASE_DIRS include
    FILES
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
      include/NovelRT/Graphics/Vulkan/Utilities/PipelineBlendFactor.hpp
      include/NovelRT/Graphics/Vulkan/Utilities/Support.hpp
      include/NovelRT/Graphics/Vulkan/Utilities/Texel.hpp
      include/NovelRT/Graphics/Vulkan/Utilities/TextureAddressMode.hpp
)

set_target_properties(NovelRT-Graphics-Vulkan
  PROPERTIES
    EXPORT_NAME Graphics-Core
    POSITION_INDEPENDENT_CODE ON
)

target_compile_features(NovelRT-Graphics-Vulkan
  PUBLIC
    cxx_std_17
)

target_compile_options(NovelRT-Graphics-Vulkan
  PRIVATE
    $<$<CXX_COMPILER_ID:GNU>:-Wall>
    $<$<CXX_COMPILER_ID:GNU>:-Wabi>
    $<$<CXX_COMPILER_ID:GNU>:-Werror>
    $<$<CXX_COMPILER_ID:GNU>:-Wextra>
    $<$<CXX_COMPILER_ID:GNU>:-Wpedantic>
    $<$<CXX_COMPILER_ID:GNU>:-pedantic-errors>

    $<$<CXX_COMPILER_ID:Clang>:-Wall>
    $<$<CXX_COMPILER_ID:Clang>:-Werror>
    $<$<CXX_COMPILER_ID:Clang>:-Wextra>
    $<$<CXX_COMPILER_ID:Clang>:-Wpedantic>
    $<$<CXX_COMPILER_ID:Clang>:-pedantic-errors>

    $<$<CXX_COMPILER_ID:MSVC>:/W4>
    $<$<CXX_COMPILER_ID:MSVC>:/WX>
    $<$<CXX_COMPILER_ID:MSVC>:/permissive->
)

target_include_directories(NovelRT-Graphics-Vulkan
  PRIVATE
    "$<TARGET_PROPERTY:Engine,INCLUDE_DIRECTORIES>")
target_link_libraries(NovelRT-Graphics-Vulkan
  PUBLIC
    NovelRT-Graphics-Core
    Vulkan::Vulkan
  PRIVATE
    GPUOpen::VulkanMemoryAllocator
)

install(
  TARGETS NovelRT-Graphics-Vulkan
  EXPORT NovelRTConfig
  LIBRARY DESTINATION lib
  FILE_SET public_headers DESTINATION include
)
