// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICS_VULKAN_H
#define NOVELRT_GRAPHICS_VULKAN_H

/**
 * @brief The default Vulkan implementation for the Graphics plugin API.
 */
namespace NovelRT::Graphics::Vulkan
{
    struct QueueFamilyIndices;
    struct SwapChainSupportDetails;
    class VulkanGraphicsDevice;
    class VulkanGraphicsPipeline;
    class VulkanShaderProgram;
    class VulkanGraphicsPipeline;
    class VulkanGraphicsPipelineSignature;
    class VulkanGraphicsContext;
    class VulkanGraphicsFence;
    class VulkanGraphicsBuffer;
    class VulkanGraphicsTexture;
    class VulkanGraphicsPrimitive;
    class VulkanGraphicsProvider;
    class VulkanGraphicsMemoryAllocator;
    class VulkanGraphicsMemoryBlockCollection;
    class VulkanGraphicsMemoryBlock;
    class VulkanGraphicsAdapter;
    class VulkanGraphicsAdapterSelector;
    class VulkanGraphicsSurfaceContext;
    class VulkanGraphicsPluginProvider;
}

// Graphics.Vulkan dependencies
#include "NovelRT/Exceptions/Exceptions.h"
#include "NovelRT/LoggingService.h"
#include "NovelRT/PluginManagement/PluginManagement.h"
#include "NovelRT/Utilities/Lazy.h"
#include "NovelRT/Utilities/Misc.h"
#include "NovelRT/EngineConfig.h"
#include "NovelRT/Graphics/Graphics.h"
#include <array>
#include <map>
#include <optional>
#include <set>
#include <vector>
#include <vulkan/vulkan.h>

// Graphics.Vulkan types

// clang-format off

#include "QueueFamilyIndices.h"
#include "SwapChainSupportDetails.h"
#include "NovelRT/Graphics/Vulkan/Utilities/Graphics.Vulkan.Utilities.h"
#include "VulkanGraphicsAdapter.h"
#include "VulkanGraphicsSurfaceContext.h"
#include "VulkanGraphicsAdapterSelector.h"
#include "VulkanGraphicsFence.h"
#include "VulkanGraphicsMemoryAllocator.h"
#include "VulkanGraphicsDevice.h"
#include "VulkanGraphicsMemoryBlock.h"
#include "VulkanGraphicsMemoryBlockCollection.h"
#include "VulkanGraphicsContext.h"
#include "VulkanGraphicsBuffer.h"
#include "VulkanShaderProgram.h"
#include "VulkanGraphicsPipeline.h"
#include "VulkanGraphicsPipelineSignature.h"
#include "VulkanGraphicsPrimitive.h"
#include "VulkanGraphicsProvider.h"
#include "VulkanShaderProgram.h"
#include "VulkanGraphicsTexture.h"
#include "VulkanGraphicsPluginProvider.h"

// clang-format on

#endif // NOVELRT_GRAPHICS_VULKAN_H
