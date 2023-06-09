// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICS_H
#define NOVELRT_GRAPHICS_H

// Graphics dependencies
#include "NovelRT/Core/Core.h"
#include "NovelRT/Maths/Maths.h"
#include "NovelRT/ResourceManagement/ResourceManagement.h"
#include "NovelRT/SceneGraph/SceneGraph.h"
#include "NovelRT/Threading/Threading.h"
#include "NovelRT/Utilities/Event.h"
#include "NovelRT/Utilities/Lazy.h"
#include "NovelRT/Utilities/Misc.h"
#include "RGBAColour.h"
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

#include "ShaderProgramKind.h"
#include "GraphicsAdapter.h"
#include "GraphicsDeviceObject.h"
#include "GraphicsContext.h"
#include "GraphicsFence.h"
#include "GraphicsMemoryAllocatorSettings.h"
#include "GraphicsMemoryRegion.h"
#include "IGraphicsMemoryRegionCollection.h"
#include "GraphicsMemoryRegionAllocationFlags.h"
#include "TexelFormat.h"
#include "GraphicsMemoryAllocator.h"
#include "GraphicsMemoryBlockCollection.h"
#include "GraphicsMemoryBudget.h"
#include "GraphicsMemoryBlock.h"
#include "GraphicsResourceAccess.h"
#include "GraphicsSurfaceKind.h"
#include "GraphicsTextureKind.h"
#include "IGraphicsSurface.h"
#include "GraphicsSurfaceContext.h"
#include "GraphicsDevice.h"
#include "GraphicsResource.h"
#include "GraphicsBufferKind.h"
#include "GraphicsBuffer.h"
#include "GraphicsTextureAddressMode.h"
#include "GraphicsTexture.h"
#include "IGraphicsAdapterSelector.h"
#include "ShaderProgram.h"
#include "GraphicsPipelineBlendFactor.h"
#include "GraphicsPipeline.h"
#include "GraphicsPipelineSignature.h"
#include "GraphicsPrimitive.h"
#include "GraphicsProvider.h"
#include "GraphicsPipelineInput.h"
#include "GraphicsPipelineInputElement.h"
#include "GraphicsPipelineInputElementKind.h"
#include "GraphicsPipelineResource.h"
#include "GraphicsPipelineResourceKind.h"
#include "ShaderProgramVisibility.h"
#include "GraphicsResourceManager.h"

// clang-format on

#endif // !NOVELRT_GRAPHICS_H
