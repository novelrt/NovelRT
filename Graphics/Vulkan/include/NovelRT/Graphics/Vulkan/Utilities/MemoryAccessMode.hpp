#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsMemoryAccessMode.hpp>

#include <algorithm>
#include <array>
#include <utility>
#include <vulkan/vulkan.h>

namespace NovelRT::Graphics::Vulkan::Utilities
{
    [[nodiscard]] inline VkAccessFlags GetVulkanAccessFlags(Graphics::GraphicsMemoryAccessMode accessFlag) noexcept
    {
        using Access = Graphics::GraphicsMemoryAccessMode;

        static constexpr auto accessFlags = std::to_array<std::pair<Access, VkAccessFlags>>({
            {Access::None, 0},
            {Access::IndirectCommandRead, VK_ACCESS_INDIRECT_COMMAND_READ_BIT},
            {Access::IndexRead, VK_ACCESS_INDEX_READ_BIT},
            {Access::VertexAttributeRead, VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT},
            {Access::UniformRead, VK_ACCESS_UNIFORM_READ_BIT},
            {Access::InputAttachmentRead, VK_ACCESS_INPUT_ATTACHMENT_READ_BIT},
            {Access::ShaderRead, VK_ACCESS_SHADER_READ_BIT},
            {Access::ShaderWrite, VK_ACCESS_SHADER_WRITE_BIT},
            {Access::ColorAttachmentRead, VK_ACCESS_COLOR_ATTACHMENT_READ_BIT},
            {Access::ColorAttachmentWrite, VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT},
            {Access::DepthStencilAttachmentRead, VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT},
            {Access::DepthStencilAttachmentWrite, VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT},
            {Access::TransferRead, VK_ACCESS_TRANSFER_READ_BIT},
            {Access::TransferWrite, VK_ACCESS_TRANSFER_WRITE_BIT},
            {Access::HostRead, VK_ACCESS_HOST_READ_BIT},
            {Access::HostWrite, VK_ACCESS_HOST_WRITE_BIT},
            {Access::MemoryRead, VK_ACCESS_MEMORY_READ_BIT},
            {Access::MemoryWrite, VK_ACCESS_MEMORY_WRITE_BIT},
        });

        static_assert(std::ranges::all_of(accessFlags,
                                          [](const auto& flag)
                                          { return static_cast<VkAccessFlags>(flag.first) == flag.second; }),
                      "Graphics memory access modes must match Vulkan access flags.");

        return static_cast<VkAccessFlags>(accessFlag);
    }
}
