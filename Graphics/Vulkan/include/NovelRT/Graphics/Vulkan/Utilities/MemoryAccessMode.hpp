#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <vulkan/vulkan.h>
#include <NovelRT/Graphics/GraphicsMemoryAccessMode.hpp>
#include <NovelRT/Utilities/Misc.h>

namespace NovelRT::Graphics::Vulkan::Utilities
{
    [[nodiscard]] inline VkAccessFlags GetVulkanAccessFlags(Graphics::GraphicsMemoryAccessMode accessFlag) noexcept
    {
        VkAccessFlags accessFlags = VK_ACCESS_NONE;

        if ((accessFlag & Graphics::GraphicsMemoryAccessMode::IndexRead) == Graphics::GraphicsMemoryAccessMode::IndexRead)
        {
            accessFlags |= VK_ACCESS_INDEX_READ_BIT;
        }

        if ((accessFlag & Graphics::GraphicsMemoryAccessMode::VertexAttributeRead) == Graphics::GraphicsMemoryAccessMode::VertexAttributeRead)
        {
            accessFlags |= VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT;
        }

        if ((accessFlag & Graphics::GraphicsMemoryAccessMode::TransferRead) == Graphics::GraphicsMemoryAccessMode::TransferRead)
        {
            accessFlags |= VK_ACCESS_TRANSFER_READ_BIT;
        }

        if ((accessFlag & Graphics::GraphicsMemoryAccessMode::TransferWrite) == Graphics::GraphicsMemoryAccessMode::TransferWrite)
        {
            accessFlags |= VK_ACCESS_TRANSFER_WRITE_BIT;
        }

        return accessFlags;
    }
}
