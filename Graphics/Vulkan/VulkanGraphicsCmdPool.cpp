// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InvalidOperationException.hpp>

#include <NovelRT/Graphics/Vulkan/VulkanGraphicsCmdList.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsCmdPool.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp>

#include <vulkan/vulkan.h>

namespace NovelRT::Graphics
{
    using VulkanGraphicsCmdList = GraphicsCmdList<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsCmdPool = GraphicsCmdPool<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsDevice = GraphicsDevice<Vulkan::VulkanGraphicsBackend>;

    VulkanGraphicsCmdPool::GraphicsCmdPool(
        std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> device,
        uint32_t queueFamilyIndex)
        : _device(std::move(device)),
          _commandPool(VK_NULL_HANDLE)
    {
        VkCommandPoolCreateInfo createInfo{};

        createInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        createInfo.queueFamilyIndex = queueFamilyIndex;

        auto result = vkCreateCommandPool(_device->GetVulkanDevice(), &createInfo, nullptr, &_commandPool);

        if (result != VK_SUCCESS)
            throw NovelRT::Exceptions::InvalidOperationException("Failed to allocate command pool");
    }

    VulkanGraphicsCmdPool::~GraphicsCmdPool()
    {
        vkDestroyCommandPool(_device->GetVulkanDevice(), _commandPool, nullptr);
    }

    static VkCommandBufferLevel GetCommandBufferLevel(CommandListLevel level)
    {
        switch (level)
        {
            case CommandListLevel::Primary:
                return VK_COMMAND_BUFFER_LEVEL_PRIMARY;
            case CommandListLevel::Secondary:
                return VK_COMMAND_BUFFER_LEVEL_SECONDARY;
            default:
                throw NovelRT::Exceptions::InvalidOperationException("Unknown command list level");
        }
    }

    std::shared_ptr<VulkanGraphicsCmdList> VulkanGraphicsCmdPool::AllocateCommandList(CommandListLevel level)
    {
        VkCommandBufferAllocateInfo allocateInfo{};

        allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocateInfo.commandPool = _commandPool;
        allocateInfo.level = GetCommandBufferLevel(level);

        VkCommandBuffer buffer;
        auto result = vkAllocateCommandBuffers(_device->GetVulkanDevice(), &allocateInfo, &buffer);

        if (result != VK_SUCCESS)
            throw NovelRT::Exceptions::InvalidOperationException("Failed to allocate command list");

        return std::make_shared<VulkanGraphicsCmdList>(_device, buffer);
    }
}
