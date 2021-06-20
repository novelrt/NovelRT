// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_H
#define NOVELRT_EXPERIMENTAL_GRAPHICS_H

//Graphics dependencies
#include <cstdint>
#include <vector>
#include <memory>
#include <optional>
#include <filesystem>
#include <gsl/span>
#include <string>
#include <utility>
#include <typeindex>
#include <chrono>
#include <mutex>
#include "../Threading/Threading.h"
#include "../../Graphics/RGBAConfig.h"
#include "../../Maths/GeoVector2F.h"
#include "../../Maths/GeoVector3F.h"
#include "../../Maths/GeoVector4F.h"
#include "../../Maths/GeoMatrix4x4F.h"
#include "../../Graphics/RGBAConfig.h"
#include "../../Utilities/Event.h"

/**
 * @brief The experimental Graphics plugin API. Comes with built-in support for the ECS.
 */
namespace NovelRT::Experimental::Graphics
{
    enum class ShaderProgramKind : uint32_t;
    class GraphicsDeviceObject;
    enum class GraphicsResourceCpuAccessKind : uint32_t;
    enum class GraphicsSurfaceKind : uint32_t;
    class IGraphicsSurface;
    class ILLGraphicsDevice;
    class LLGraphicsResource;
    class LLGraphicsBuffer;
    class LLGraphicsTexture;
    class ShaderProgram;
    class GraphicsPipeline;
    class GraphicsPipelineSignature;
    class GraphicsPipelineInput;
    class GraphicsPipelineResource;
    class GraphicsPipelineInputElement;
    enum class GraphicsPipelineInputElementKind : uint32_t;
    enum class GraphicsPipelineResourceKind : uint32_t;
    enum class ShaderProgramVisibility : uint32_t;
    class GraphicsContext;
    class GraphicsFence;
    class GraphicsPrimitive;
    class GraphicsMemoryAllocator;
    class GraphicsMemoryAllocatorSettings;
    enum class GraphicsTextureKind : uint32_t;
    struct GraphicsMemoryAllocatorSettings;
    enum class GraphicsMemoryRegionAllocationFlags : uint32_t;
    class GraphicsMemoryBlockCollection;
    class GraphicsMemoryBlock;
    enum class GraphicsMemoryRegionAllocationFlags : uint32_t;
}

//Graphics types
#include "ShaderProgramKind.h"
#include "EcsDefaultRenderingComponentTypes.h"
#include "EcsDefaultRenderingSystem.h"
#include "GraphicsDeviceObject.h"
#include "GraphicsContext.h"
#include "GraphicsFence.h"
#include "GraphicsMemoryAllocatorSettings.h"
#include "GraphicsMemoryAllocator.h"
#include "GraphicsMemoryRegionAllocationFlags.h"
#include "GraphicsMemoryBlockCollection.h"
#include "IGraphicsMemoryRegionCollection.h"
#include "GraphicsMemoryBlock.h"
#include "GraphicsResourceCpuAccessKind.h"
#include "GraphicsSurfaceKind.h"
#include "GraphicsTextureKind.h"
#include "IGraphicsSurface.h"
#include "ILLGraphicsDevice.h"
#include "LLGraphicsResource.h"
#include "LLGraphicsBuffer.h"
#include "LLGraphicsResourceViewContainer.h"
#include "LLGraphicsTexture.h"
#include "ShaderProgram.h"
#include "GraphicsPipeline.h"
#include "GraphicsPipelineSignature.h"
#include "GraphicsPrimitive.h"
#include "GraphicsPipelineInput.h"
#include "GraphicsPipelineInputElement.h"
#include "GraphicsPipelineInputElementKind.h"
#include "GraphicsPipelineResource.h"
#include "GraphicsPipelineResourceKind.h"
#include "ShaderProgramVisibility.h"

#endif // !NOVELRT_EXPERIMENTAL_GRAPHICS_H
