// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_H
#define NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_H

/**
 * @brief The default Vulkan implementation for the Graphics plugin API.
 */
namespace NovelRT::Experimental::Graphics::Vulkan
{
    struct QueueFamilyIndices;
    struct SwapChainSupportDetails;
    class VulkanGraphicsDevice;
}

//Graphics.Vulkan dependencies
#include <optional>
#include <vector>
#include <vulkan/vulkan.h>
#include "../Graphics.h"
#include "../../../LoggingService.h"

// Graphics.Vulkan types
#include "QueueFamilyIndices.h"
#include "SwapChainSupportDetails.h"
#include "VulkanGraphicsDevice.h"

#endif // NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_H
