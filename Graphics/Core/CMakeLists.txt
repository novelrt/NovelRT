add_library(NovelRT-Graphics-Core STATIC
  GraphicsPipelineInput.cpp
  GraphicsPipelineInputElement.cpp
  GraphicsPipelineResource.cpp
)

target_sources(NovelRT-Graphics-Core
  PUBLIC
    FILE_SET public_headers
    TYPE HEADERS
    BASE_DIRS include
    FILES
      include/NovelRT/Graphics/GraphicsAdapter.hpp
      include/NovelRT/Graphics/GraphicsBackendTraits.hpp
      include/NovelRT/Graphics/GraphicsBuffer.hpp
      include/NovelRT/Graphics/GraphicsCmdList.hpp
      include/NovelRT/Graphics/GraphicsBufferCreateInfo.hpp
      include/NovelRT/Graphics/GraphicsBufferKind.hpp
      include/NovelRT/Graphics/GraphicsCmdList.hpp
      include/NovelRT/Graphics/GraphicsContext.hpp
      include/NovelRT/Graphics/GraphicsDescriptorSet.hpp
      include/NovelRT/Graphics/GraphicsDevice.hpp
      include/NovelRT/Graphics/GraphicsDeviceObject.hpp
      include/NovelRT/Graphics/GraphicsFence.hpp
      include/NovelRT/Graphics/GraphicsMemoryAllocator.hpp
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
      include/NovelRT/Graphics/GraphicsRenderPass.hpp
      include/NovelRT/Graphics/GraphicsResource.hpp
      include/NovelRT/Graphics/GraphicsResourceMemoryRegion.hpp
      include/NovelRT/Graphics/GraphicsResourceAccess.hpp
      include/NovelRT/Graphics/GraphicsSurfaceContext.hpp
      include/NovelRT/Graphics/GraphicsSurfaceKind.hpp
      include/NovelRT/Graphics/GraphicsTexture.hpp
      include/NovelRT/Graphics/GraphicsTextureAddressMode.hpp
      include/NovelRT/Graphics/GraphicsTextureAddressMode.hpp
      include/NovelRT/Graphics/GraphicsTextureKind.hpp
      include/NovelRT/Graphics/IGraphicsAdapterSelector.hpp
      include/NovelRT/Graphics/IGraphicsSurface.hpp
      include/NovelRT/Graphics/RGBAColour.hpp
      include/NovelRT/Graphics/ShaderProgram.hpp
      include/NovelRT/Graphics/ShaderProgramKind.hpp
      include/NovelRT/Graphics/ShaderProgramVisibility.hpp
      include/NovelRT/Graphics/TexelFormat.hpp
)

set_target_properties(NovelRT-Graphics-Core
  PROPERTIES
    EXPORT_NAME Graphics-Core
    POSITION_INDEPENDENT_CODE ON
)

target_compile_features(NovelRT-Graphics-Core
  PUBLIC
    cxx_std_17
)

target_compile_options(NovelRT-Graphics-Core
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

target_include_directories(NovelRT-Graphics-Core PRIVATE "$<TARGET_PROPERTY:Engine,INCLUDE_DIRECTORIES>")
target_link_libraries(NovelRT-Graphics-Core
  PUBLIC
    spdlog
    tbb
)

install(
  TARGETS NovelRT-Graphics-Core
  EXPORT NovelRTConfig
  LIBRARY DESTINATION lib
  FILE_SET public_headers DESTINATION include
)
