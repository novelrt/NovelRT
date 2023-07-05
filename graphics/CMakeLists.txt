add_library(NovelRT-Graphics STATIC
  GraphicsPipeline.cpp
  GraphicsPipelineInput.cpp
  GraphicsPipelineInputElement.cpp
  GraphicsPipelineResource.cpp
  GraphicsPipelineSignature.cpp
  ShaderProgram.cpp
  Vulkan/VulkanGraphicsAdapter.cpp
  Vulkan/VulkanGraphicsAdapterSelector.cpp
  Vulkan/VulkanGraphicsContext.cpp
  Vulkan/VulkanGraphicsDevice.cpp
  Vulkan/VulkanGraphicsFence.cpp
  Vulkan/VulkanGraphicsPipeline.cpp
  Vulkan/VulkanGraphicsPipelineSignature.cpp
  Vulkan/VulkanGraphicsPluginProvider.cpp
  Vulkan/VulkanGraphicsProvider.cpp
  Vulkan/VulkanGraphicsSurfaceContext.cpp
  Vulkan/VulkanShaderProgram.cpp
)

target_sources(NovelRT-Graphics
  PUBLIC
    FILE_SET public_headers
    TYPE HEADERS
    BASE_DIRS include
    FILES
      include/NovelRT/Graphics/GraphicsAdapter.hpp
      include/NovelRT/Graphics/GraphicsBuffer.hpp
      include/NovelRT/Graphics/GraphicsBufferKind.hpp
      include/NovelRT/Graphics/GraphicsContext.hpp
      include/NovelRT/Graphics/GraphicsDevice.hpp
      include/NovelRT/Graphics/GraphicsDeviceObject.hpp
      include/NovelRT/Graphics/GraphicsFence.hpp
      include/NovelRT/Graphics/GraphicsMemoryRegionAllocationFlags.hpp
      include/NovelRT/Graphics/GraphicsPipeline.hpp
      include/NovelRT/Graphics/GraphicsPipelineBlendFactor.hpp
      include/NovelRT/Graphics/GraphicsPipelineInput.hpp
      include/NovelRT/Graphics/GraphicsPipelineInputElement.hpp
      include/NovelRT/Graphics/GraphicsPipelineInputElementKind.hpp
      include/NovelRT/Graphics/GraphicsPipelineResource.hpp
      include/NovelRT/Graphics/GraphicsPipelineResourceKind.hpp
      include/NovelRT/Graphics/GraphicsPipelineSignature.hpp
      include/NovelRT/Graphics/GraphicsProvider.hpp
      include/NovelRT/Graphics/GraphicsResource.hpp
      include/NovelRT/Graphics/GraphicsResourceAccess.hpp
      include/NovelRT/Graphics/GraphicsSurfaceContext.hpp
      include/NovelRT/Graphics/GraphicsSurfaceKind.hpp
      include/NovelRT/Graphics/GraphicsTexture.hpp
      include/NovelRT/Graphics/GraphicsTextureAddressMode.hpp
      include/NovelRT/Graphics/GraphicsTextureKind.hpp
      include/NovelRT/Graphics/IGraphicsAdapterSelector.hpp
      include/NovelRT/Graphics/IGraphicsSurface.hpp
      include/NovelRT/Graphics/RGBAColour.hpp
      include/NovelRT/Graphics/ShaderProgram.hpp
      include/NovelRT/Graphics/ShaderProgramKind.hpp
      include/NovelRT/Graphics/ShaderProgramVisibility.hpp
      include/NovelRT/Graphics/TexelFormat.hpp
      include/NovelRT/Graphics/D3D12/Utilities/PipelineBlendFactor.hpp
      include/NovelRT/Graphics/Metal/Utilities/PipelineBlendFactor.hpp
      include/NovelRT/Graphics/Vulkan/QueueFamilyIndices.hpp
      include/NovelRT/Graphics/Vulkan/SwapChainSupportDetails.hpp
      include/NovelRT/Graphics/Vulkan/VulkanGraphicsAdapter.hpp
      include/NovelRT/Graphics/Vulkan/VulkanGraphicsAdapterSelector.hpp
      include/NovelRT/Graphics/Vulkan/VulkanGraphicsContext.hpp
      include/NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp
      include/NovelRT/Graphics/Vulkan/VulkanGraphicsFence.hpp
      include/NovelRT/Graphics/Vulkan/VulkanGraphicsPipeline.hpp
      include/NovelRT/Graphics/Vulkan/VulkanGraphicsPipelineSignature.hpp
      include/NovelRT/Graphics/Vulkan/VulkanGraphicsPluginProvider.hpp
      include/NovelRT/Graphics/Vulkan/VulkanGraphicsProvider.hpp
      include/NovelRT/Graphics/Vulkan/VulkanGraphicsSurfaceContext.hpp
      include/NovelRT/Graphics/Vulkan/VulkanShaderProgram.hpp
      include/NovelRT/Graphics/Vulkan/Utilities/BufferUsageKind.hpp
      include/NovelRT/Graphics/Vulkan/Utilities/PipelineBlendFactor.hpp
      include/NovelRT/Graphics/Vulkan/Utilities/Support.hpp
      include/NovelRT/Graphics/Vulkan/Utilities/Texel.hpp
      include/NovelRT/Graphics/Vulkan/Utilities/TextureAddressMode.hpp
)

set_target_properties(NovelRT-Graphics
  PROPERTIES
    EXPORT_NAME Graphics
    POSITION_INDEPENDENT_CODE ON
)

target_compile_features(NovelRT-Graphics
  PUBLIC
    cxx_std_17
)

target_compile_options(NovelRT-Graphics
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

target_include_directories(NovelRT-Graphics PRIVATE "$<TARGET_PROPERTY:Engine,INCLUDE_DIRECTORIES>")
target_link_libraries(NovelRT-Graphics
  PUBLIC
    spdlog
    tbb
    Vulkan::Vulkan
    VulkanMemoryAllocator
)

install(
  TARGETS NovelRT-Graphics
  EXPORT NovelRTConfig
  LIBRARY DESTINATION lib
  FILE_SET public_headers DESTINATION include
)