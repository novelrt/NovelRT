#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <vulkan/vulkan.h>
#include <NovelRT/Graphics/GraphicsMemoryAccessFlag.hpp>
#include <NovelRT/Utilities/Misc.h>

namespace NovelRT::Graphics::Vulkan::Utilities
{
    [[nodiscard]] inline VkAccessFlags GetVulkanMemoryAccessFlags(Graphics::GraphicsMemoryAccessFlag accessFlag) noexcept
    {
        VkAccessFlags accessFlags = VK_ACCESS_NONE;

        if ((accessFlag & Graphics::GraphicsMemoryAccessFlag::IndexRead) == Graphics::GraphicsMemoryAccessFlag::IndexRead)
        {
            accessFlags |= VK_ACCESS_INDEX_READ_BIT;
        }

        if ((accessFlag & Graphics::GraphicsMemoryAccessFlag::VertexAttributeRead) == Graphics::GraphicsMemoryAccessFlag::VertexAttributeRead)
        {
            accessFlags |= VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT;
        }

        if ((accessFlag & Graphics::GraphicsMemoryAccessFlag::TransferRead) == Graphics::GraphicsMemoryAccessFlag::TransferRead)
        {
            accessFlags |= VK_ACCESS_TRANSFER_READ_BIT;
        }

        if ((accessFlag & Graphics::GraphicsMemoryAccessFlag::TransferWrite) == Graphics::GraphicsMemoryAccessFlag::TransferWrite)
        {
            accessFlags |= VK_ACCESS_TRANSFER_WRITE_BIT;
        }

        return accessFlags;
    }
}
