#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsBufferKind.hpp>
#include <NovelRT/Graphics/GraphicsResourceAccess.hpp>
#include <NovelRT/Graphics/GraphicsTextureKind.hpp>
#include <NovelRT/Graphics/Vulkan/Utilities/Vma.hpp>
#include <NovelRT/Utilities/Operators.hpp>

#include <cstdint>

#include <vulkan/vulkan.h>

namespace NovelRT::Graphics::Vulkan::Utilities
{
    [[nodiscard]] inline uint32_t GetVulkanBufferUsageKind(GraphicsBufferKind kind,
                                                           GraphicsResourceAccess resourceAccessType) noexcept
    {
        VkBufferUsageFlagBits vulkanBufferUsageKind = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;

        switch (kind)
        {
            case GraphicsBufferKind::Vertex:
                vulkanBufferUsageKind = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
                break;
            case GraphicsBufferKind::Index:
                vulkanBufferUsageKind = VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
                break;
            case GraphicsBufferKind::Constant:
                vulkanBufferUsageKind = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
                break;
            default:
            case GraphicsBufferKind::Default:
                vulkanBufferUsageKind = static_cast<VkBufferUsageFlagBits>(0);
                break;
        }

        VkBufferUsageFlagBits cpuAccessBit = VK_BUFFER_USAGE_TRANSFER_DST_BIT;

        switch (resourceAccessType)
        {
            case GraphicsResourceAccess::Read:
                cpuAccessBit = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
                break;
            case GraphicsResourceAccess::Write:
                cpuAccessBit = VK_BUFFER_USAGE_TRANSFER_DST_BIT;
                break;
            case GraphicsResourceAccess::ReadWrite:
                cpuAccessBit = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
                break;
            default:
            case GraphicsResourceAccess::None:
                cpuAccessBit = static_cast<VkBufferUsageFlagBits>(0);
                break;
        }

        vulkanBufferUsageKind |= cpuAccessBit;
        return static_cast<uint32_t>(vulkanBufferUsageKind);
    }

    [[nodiscard]] inline uint32_t GetVulkanImageUsageKind(GraphicsTextureKind /*kind*/,
                                                          GraphicsResourceAccess resourceAccessType) noexcept
    {
        VkImageUsageFlagBits cpuAccessBit = VK_IMAGE_USAGE_TRANSFER_DST_BIT;

        switch (resourceAccessType)
        {
            case GraphicsResourceAccess::Read:
                cpuAccessBit = VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
                break;
            case GraphicsResourceAccess::Write:
                cpuAccessBit = VK_IMAGE_USAGE_TRANSFER_DST_BIT;
                break;
            case GraphicsResourceAccess::ReadWrite:
                cpuAccessBit = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
                break;
            default:
            case GraphicsResourceAccess::None:
                cpuAccessBit = static_cast<VkImageUsageFlagBits>(0);
                break;
        }

        cpuAccessBit |= static_cast<VkImageUsageFlagBits>(VK_IMAGE_USAGE_SAMPLED_BIT);
        return static_cast<uint32_t>(cpuAccessBit);
    }

    [[nodiscard]] inline VmaAllocationCreateFlagBits GetVmaAllocationKind(GraphicsResourceAccess resourceAccessType) noexcept
    {
        switch (resourceAccessType)
        {
            default:
            case GraphicsResourceAccess::None:
                // If we're neither reading nor writing, we don't care
                return static_cast<VmaAllocationCreateFlagBits>(0);
            case GraphicsResourceAccess::Read:
                // If we're planning on reading from the buffer, assume any reads can be random
                return VMA_ALLOCATION_CREATE_HOST_ACCESS_RANDOM_BIT;
            case GraphicsResourceAccess::Write:
                // If we're planning on writing to the buffer, assume it's going to be block-copies
                return VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT;
            case GraphicsResourceAccess::ReadWrite:
                // If we're doing both, assume random access for safety.
                return VMA_ALLOCATION_CREATE_HOST_ACCESS_RANDOM_BIT;
        }
    }
}
