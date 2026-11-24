// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InitialisationFailureException.hpp>

#include <NovelRT/Graphics/Vulkan/VulkanGraphicsCmdList.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsContext.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDescriptorSet.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsFence.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsPipelineSignature.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsRenderPass.hpp>
#include <NovelRT/Utilities/Macros.hpp>

#include <vulkan/vulkan.h>

#include <algorithm>

namespace NovelRT::Graphics
{
    using VulkanGraphicsCmdList = GraphicsCmdList<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsContext = GraphicsContext<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsDevice = GraphicsDevice<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsDescriptorSet = GraphicsDescriptorSet<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsFence = GraphicsFence<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsPipeline = GraphicsPipeline<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsPipelineSignature = GraphicsPipelineSignature<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsRenderPass = GraphicsRenderPass<Vulkan::VulkanGraphicsBackend>;
    template<template<typename> typename TResource>
    using VulkanGraphicsResourceMemoryRegion = GraphicsResourceMemoryRegion<TResource, Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsTexture = GraphicsTexture<Vulkan::VulkanGraphicsBackend>;

    VkCommandPool VulkanGraphicsContext::CreateVulkanCommandPool() const
    {
        VkCommandPool vulkanCommandPool = VK_NULL_HANDLE;

        auto device = GetDevice();

        VkCommandPoolCreateInfo commandPoolCreateInfo{};
        commandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        commandPoolCreateInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
        commandPoolCreateInfo.queueFamilyIndex = _queueFamilyIndex;

        const VkResult result =
            vkCreateCommandPool(device->GetVulkanDevice(), &commandPoolCreateInfo, nullptr, &vulkanCommandPool);

        if (result != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException(
                "Failed to initialise the VkCommandPool instance with the given parameters and VkDevice.", result);
        }

        return vulkanCommandPool;
    }

    VkCommandBuffer VulkanGraphicsContext::CreateVulkanCommandBuffer(bool primary) const
    {
        VkCommandBuffer vulkanCommandBuffer = VK_NULL_HANDLE;

        std::span<const std::string> extensions = _device->GetEnabledExtensions();

        const bool supportsMixedRecording =
            std::ranges::any_of(extensions,
                                [](const std::string& extension)
                                {
                                    return extension == VK_EXT_NESTED_COMMAND_BUFFER_EXTENSION_NAME ||
                                           extension == VK_KHR_MAINTENANCE_7_EXTENSION_NAME;
                                });

        if (!supportsMixedRecording && !primary)
        {
            // should be VK_NULL_HANDLE here. - Matt J.
            return vulkanCommandBuffer;
        }

        VkCommandBufferAllocateInfo commandBufferAllocateInfo{};
        commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        commandBufferAllocateInfo.commandPool = GetVulkanCommandPool();
        commandBufferAllocateInfo.level = primary ? VK_COMMAND_BUFFER_LEVEL_PRIMARY : VK_COMMAND_BUFFER_LEVEL_SECONDARY;
        commandBufferAllocateInfo.commandBufferCount = 1;

        auto device = GetDevice();

        VkResult result =
            vkAllocateCommandBuffers(device->GetVulkanDevice(), &commandBufferAllocateInfo, &vulkanCommandBuffer);

        if (result != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException(
                "Failed to initialise the VkCommandBuffer instance with the given parameters and VkDevice.", result);
        }

        return vulkanCommandBuffer;
    }

    // NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
    std::shared_ptr<VulkanGraphicsContext> VulkanGraphicsContext::shared_from_this()
    {
        return std::static_pointer_cast<VulkanGraphicsContext>(GraphicsDeviceObject::shared_from_this());
    }

    // NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
    std::shared_ptr<const VulkanGraphicsContext> VulkanGraphicsContext::shared_from_this() const
    {
        return std::static_pointer_cast<const VulkanGraphicsContext>(GraphicsDeviceObject::shared_from_this());
    }

    VulkanGraphicsContext::GraphicsContext(std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> device,
                                           uint32_t queueFamilyIndex) noexcept
        : _device(std::move(device)),
          _queueFamilyIndex(queueFamilyIndex),
          _vulkanCommandPool([this]() { return CreateVulkanCommandPool(); })
    {
        unused(_state.Transition(Threading::VolatileState::Initialised));
    }

    VulkanGraphicsContext::~GraphicsContext()
    {
        VkDevice device = GetDevice()->GetVulkanDevice();

        if (_vulkanCommandPool.HasValue())
        {
            VkCommandPool pool = _vulkanCommandPool.Get();
            vkDestroyCommandPool(device, pool, nullptr);
            _vulkanCommandPool.Reset();
        }
    }

    std::shared_ptr<VulkanGraphicsDevice> VulkanGraphicsContext::GetDevice() const
    {
        return _device;
    }

    void VulkanGraphicsContext::BeginFrame()
    {
    }

    std::shared_ptr<VulkanGraphicsCmdList> VulkanGraphicsContext::CreateCmdList(
        std::optional<SecondaryCmdListInfo<Vulkan::VulkanGraphicsBackend>> secondaryContextData)
    {
        return std::make_shared<VulkanGraphicsCmdList>(this->GetDevice(),
                                                       CreateVulkanCommandBuffer(!secondaryContextData.has_value()),
                                                       shared_from_this(), secondaryContextData);
    }

    void VulkanGraphicsContext::EndFrame() // TODO: WTF?
    {
    }

    VkCommandPool VulkanGraphicsContext::GetVulkanCommandPool() const
    {
        return _vulkanCommandPool.Get();
    }
}
