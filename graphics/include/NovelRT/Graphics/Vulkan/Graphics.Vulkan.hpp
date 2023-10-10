// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICS_VULKAN_H
#define NOVELRT_GRAPHICS_VULKAN_H

// Graphics.Vulkan dependencies
// clang-format off

#include <NovelRT/EngineConfig.h>
#include <NovelRT/Exceptions/Exceptions.h>
#include <NovelRT/LoggingService.h>
#include <NovelRT/PluginManagement/PluginManagement.h>
#include <NovelRT/Utilities/Lazy.h>
#include <NovelRT/Utilities/Memory.h>
#include <NovelRT/Utilities/Misc.h>
#include <NovelRT/Graphics/Graphics.hpp>
#include <array>
#include <map>
#include <optional>
#include <set>
#include <vector>
#include <vulkan/vulkan.h>
#include <vk_mem_alloc.h>

// clang-format on

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

// Graphics.Vulkan types

// clang-format off

#include <NovelRT/Graphics/Vulkan/QueueFamilyIndices.hpp>
#include <NovelRT/Graphics/Vulkan/SwapChainSupportDetails.hpp>
#include <NovelRT/Graphics/Vulkan/Utilities/Graphics.Vulkan.Utilities.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsAdapter.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsSurfaceContext.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsAdapterSelector.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsFence.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsMemoryAllocator.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsMemoryBlock.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsMemoryBlockCollection.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsContext.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsBuffer.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanShaderProgram.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsPipeline.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsPipelineSignature.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsPrimitive.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsProvider.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanShaderProgram.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsTexture.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsPluginProvider.hpp>

// clang-format on

#endif // NOVELRT_GRAPHICS_VULKAN_H
