// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICS_VULKAN_H
#define NOVELRT_GRAPHICS_VULKAN_H

// Graphics.Vulkan dependencies
#include "../../EngineConfig.h"
#include "../../Exceptions/Exceptions.h"
#include "../../LoggingService.h"
#include "../../PluginManagement/PluginManagement.h"
#include "../../Utilities/Lazy.h"
#include "../../Utilities/Misc.h"
#include "../Graphics.h"
#include <array>
#include <map>
#include <optional>
#include <set>
#include <vector>
#include <vulkan/vulkan.h>

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
    class VulkanGraphicsProvider;
    class VulkanGraphicsAdapter;
    class VulkanGraphicsAdapterSelector;
    class VulkanGraphicsSurfaceContext;
    class VulkanGraphicsPluginProvider;
}

// Graphics.Vulkan types

// clang-format off

#include "QueueFamilyIndices.h"
#include "SwapChainSupportDetails.h"
#include "NovelRT/Graphics/Vulkan/Utilities/Graphics.Vulkan.Utilities.h"
#include "VulkanGraphicsAdapter.h"
#include "VulkanGraphicsSurfaceContext.h"
#include "VulkanGraphicsAdapterSelector.h"
#include "VulkanGraphicsFence.h"
#include "VulkanGraphicsDevice.h"
#include "VulkanGraphicsContext.h"
#include "VulkanShaderProgram.h"
#include "VulkanGraphicsPipeline.h"
#include "VulkanGraphicsPipelineSignature.h"
#include "VulkanGraphicsProvider.h"
#include "VulkanShaderProgram.h"
#include "VulkanGraphicsPluginProvider.h"

// clang-format on

#endif // NOVELRT_GRAPHICS_VULKAN_H
