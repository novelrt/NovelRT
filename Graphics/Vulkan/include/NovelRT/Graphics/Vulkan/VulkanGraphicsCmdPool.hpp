#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsCmdPool.hpp>

#include <vulkan/vulkan.h>

namespace NovelRT::Graphics::Vulkan
{
    struct VulkanGraphicsBackend;
}

namespace NovelRT::Graphics
{
    template<>
    class GraphicsCmdPool<Vulkan::VulkanGraphicsBackend>
    : std::enable_shared_from_this<GraphicsCmdPool<Vulkan::VulkanGraphicsBackend>>
    {
    private:
        std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> _device;
        VkCommandPool _commandPool;

    public:
        GraphicsCmdPool(std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> device, uint32_t queueFamilyIndex);
        ~GraphicsCmdPool();

        std::shared_ptr<GraphicsCmdList<Vulkan::VulkanGraphicsBackend>> AllocateCommandList(CommandListLevel level);
    };
}
