// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICS_H
#define NOVELRT_GRAPHICS_H

// Graphics dependencies
#include "NovelRT/EngineConfig.h"
#include "NovelRT/Maths/Maths.h"
#include "NovelRT/ResourceManagement/ResourceManagement.h"
#include "NovelRT/SceneGraph/SceneGraph.h"
#include "NovelRT/Threading/Threading.h"
#include "NovelRT/Utilities/Event.h"
#include "NovelRT/Utilities/Lazy.h"
#include "NovelRT/Utilities/Memory.h"
#include "NovelRT/Utilities/Misc.h"
#include <NovelRT/Graphics/RGBAColour.hpp>
#include <chrono>
#include <cstdint>
#include <filesystem>
#include <list>
#include <memory>
#include <mutex>
#include <optional>
#include <string>
#include <typeindex>
#include <utility>
#include <vector>

/**
 * @brief The experimental Graphics plugin API. Comes with built-in support for the ECS.
 */
namespace NovelRT::Graphics
{
    enum class ShaderProgramKind : uint32_t;
    enum class GraphicsResourceAccess : uint32_t;
    enum class GraphicsSurfaceKind : uint32_t;
    enum class GraphicsTextureAddressMode : uint32_t;
    enum class GraphicsPipelineBlendFactor : uint32_t;
    enum class GraphicsPipelineInputElementKind : uint32_t;
    enum class GraphicsPipelineResourceKind : uint32_t;
    enum class ShaderProgramVisibility : uint32_t;
    enum class GraphicsTextureKind : uint32_t;
    enum class GraphicsMemoryRegionAllocationFlags : uint32_t;
    enum class GraphicsMemoryRegionAllocationFlags : uint32_t;
    enum class GraphicsBufferKind : uint32_t;
    enum class TexelFormat : uint32_t;
    struct GraphicsMemoryAllocatorSettings;
    class GraphicsDeviceObject;
    class IGraphicsSurface;
    class GraphicsAdapter;
    class GraphicsDevice;
    class GraphicsResource;
    class GraphicsBuffer;
    class GraphicsTexture;
    class ShaderProgram;
    class GraphicsPipeline;
    class GraphicsPipelineSignature;
    class GraphicsPipelineInput;
    class GraphicsPipelineResource;
    class GraphicsPipelineInputElement;
    class GraphicsContext;
    class GraphicsFence;
    class GraphicsPrimitive;
    class GraphicsProvider;
    class GraphicsMemoryAllocator;
    class IGraphicsAdapterSelector;
    class GraphicsMemoryBlockCollection;
    class GraphicsMemoryBlock;
    class GraphicsMemoryBudget;
    class GraphicsSurfaceContext;
    class GraphicsResourceManager;
}

// Graphics types
// clang-format off
          
#include <NovelRT/Graphics/ShaderProgramKind.hpp>
#include <NovelRT/Graphics/GraphicsAdapter.hpp>
#include <NovelRT/Graphics/GraphicsDeviceObject.hpp>
#include <NovelRT/Graphics/GraphicsContext.hpp>
#include <NovelRT/Graphics/GraphicsFence.hpp>
#include <NovelRT/Graphics/GraphicsMemoryAllocatorSettings.hpp>
#include <NovelRT/Graphics/GraphicsMemoryRegion.hpp>
#include <NovelRT/Graphics/IGraphicsMemoryRegionCollection.hpp>
#include <NovelRT/Graphics/GraphicsMemoryRegionAllocationFlags.hpp>
#include <NovelRT/Graphics/TexelFormat.hpp>
#include <NovelRT/Graphics/GraphicsMemoryAllocator.hpp>
#include <NovelRT/Graphics/GraphicsMemoryBlockCollection.hpp>
#include <NovelRT/Graphics/GraphicsMemoryBudget.hpp>
#include <NovelRT/Graphics/GraphicsMemoryBlock.hpp>
#include <NovelRT/Graphics/GraphicsResourceAccess.hpp>
#include <NovelRT/Graphics/GraphicsSurfaceKind.hpp>
#include <NovelRT/Graphics/GraphicsTextureKind.hpp>
#include <NovelRT/Graphics/IGraphicsSurface.hpp>
#include <NovelRT/Graphics/GraphicsSurfaceContext.hpp>
#include <NovelRT/Graphics/GraphicsDevice.hpp>
#include <NovelRT/Graphics/GraphicsResource.hpp>
#include <NovelRT/Graphics/GraphicsBufferKind.hpp>
#include <NovelRT/Graphics/GraphicsBuffer.hpp>
#include <NovelRT/Graphics/GraphicsTextureAddressMode.hpp>
#include <NovelRT/Graphics/GraphicsTexture.hpp>
#include <NovelRT/Graphics/IGraphicsAdapterSelector.hpp>
#include <NovelRT/Graphics/ShaderProgram.hpp>
#include <NovelRT/Graphics/GraphicsPipelineBlendFactor.hpp>
#include <NovelRT/Graphics/GraphicsPipeline.hpp>
#include <NovelRT/Graphics/GraphicsPipelineSignature.hpp>
#include <NovelRT/Graphics/GraphicsPrimitive.hpp>
#include <NovelRT/Graphics/GraphicsProvider.hpp>
#include <NovelRT/Graphics/GraphicsPipelineInput.hpp>
#include <NovelRT/Graphics/GraphicsPipelineInputElement.hpp>
#include <NovelRT/Graphics/GraphicsPipelineInputElementKind.hpp>
#include <NovelRT/Graphics/GraphicsPipelineResource.hpp>
#include <NovelRT/Graphics/GraphicsPipelineResourceKind.hpp>
#include <NovelRT/Graphics/ShaderProgramVisibility.hpp>
#include <NovelRT/Graphics/GraphicsResourceManager.hpp>

// clang-format on

#endif // !NOVELRT_GRAPHICS_H
