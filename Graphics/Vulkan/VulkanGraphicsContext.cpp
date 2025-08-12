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

    VkCommandPool CreateVulkanCommandPool(VulkanGraphicsContext* context)
    {
        VkCommandPool vulkanCommandPool = VK_NULL_HANDLE;

        auto device = context->GetDevice();

        VkCommandPoolCreateInfo commandPoolCreateInfo{};
        commandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        commandPoolCreateInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
        commandPoolCreateInfo.queueFamilyIndex = device->GetIndicesData().graphicsFamily.value();

        const VkResult result =
            vkCreateCommandPool(device->GetVulkanDevice(), &commandPoolCreateInfo, nullptr, &vulkanCommandPool);

        if (result != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException(
                "Failed to initialise the VkCommandPool instance with the given parameters and VkDevice.", result);
        }

        return vulkanCommandPool;
    }

    VkCommandBuffer CreateVulkanCommandBuffer(VulkanGraphicsContext* context)
    {
        VkCommandBuffer vulkanCommandBuffer = VK_NULL_HANDLE;

        VkCommandBufferAllocateInfo commandBufferAllocateInfo{};
        commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        commandBufferAllocateInfo.commandPool = context->GetVulkanCommandPool();
        commandBufferAllocateInfo.commandBufferCount = 1;

        auto device = context->GetDevice();

        VkResult result =
            vkAllocateCommandBuffers(device->GetVulkanDevice(), &commandBufferAllocateInfo, &vulkanCommandBuffer);

        if (result != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException(
                "Failed to initialise the VkCommandBuffer instance with the given parameters and VkDevice.", result);
        }

        return vulkanCommandBuffer;
    }

    void VulkanGraphicsContext::DestroyDescriptorSets()
    {
        _vulkanDescriptorSets.clear();
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

    VulkanGraphicsContext::GraphicsContext(
        std::shared_ptr<GraphicsSwapchainImage<Vulkan::VulkanGraphicsBackend>> image) noexcept
        : _swapchainImage(std::move(image)),
          _vulkanDescriptorSets(),
          _vulkanCommandBuffer([this]() { return CreateVulkanCommandBuffer(this); }),
          _vulkanCommandPool([this]() { return CreateVulkanCommandPool(this); })
    {
        static_cast<void>(_state.Transition(Threading::VolatileState::Initialised));
    }

    VulkanGraphicsContext::~GraphicsContext()
    {
        DestroyDescriptorSets();

        VkDevice device = GetDevice()->GetVulkanDevice();

        if (_vulkanCommandBuffer.HasValue() && _vulkanCommandPool.HasValue())
        {
            VkCommandBuffer commandBuffer = _vulkanCommandBuffer.Get();
            VkCommandPool pool = _vulkanCommandPool.Get();
            vkFreeCommandBuffers(device, pool, 1, &commandBuffer);
            _vulkanCommandBuffer.Reset();
        }

        if (_vulkanCommandPool.HasValue())
        {
            VkCommandPool pool = _vulkanCommandPool.Get();
            vkDestroyCommandPool(device, pool, nullptr);
            _vulkanCommandPool.Reset();
        }
    }

    std::shared_ptr<VulkanGraphicsDevice> VulkanGraphicsContext::GetDevice() const
    {
        return _swapchainImage->GetDevice();
    }

    std::shared_ptr<VulkanGraphicsRenderPass> VulkanGraphicsContext::CreateRenderPass()
    {
        return std::make_shared<VulkanGraphicsRenderPass>(shared_from_this(), _swapchainImage);
    }

    std::shared_ptr<VulkanGraphicsCmdList> VulkanGraphicsContext::BeginFrame()
    {
        DestroyDescriptorSets();

        VkCommandBufferBeginInfo commandBufferBeginInfo{};
        commandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        const VkResult result = vkBeginCommandBuffer(GetVulkanCommandBuffer(), &commandBufferBeginInfo);

        if (result != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException(
                "Failed to initialise on the VkCommandBuffer instance correctly.", result);
        }

        return std::make_shared<VulkanGraphicsCmdList>(shared_from_this(), GetVulkanCommandBuffer());
    }

    void VulkanGraphicsContext::EndFrame()
    {
        VkCommandBuffer commandBuffer = GetVulkanCommandBuffer();

        const VkResult endCommandBufferResult = vkEndCommandBuffer(commandBuffer);

        if (endCommandBufferResult != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException(
                "Failed to finalise initialisation for the VkCommandBuffer Instance. This instance cannot be "
                "submitted.",
                endCommandBufferResult);
        }
    }

    VkCommandBuffer VulkanGraphicsContext::GetVulkanCommandBuffer() const
    {
        return _vulkanCommandBuffer.Get();
    }

    VkCommandPool VulkanGraphicsContext::GetVulkanCommandPool() const
    {
        return _vulkanCommandPool.Get();
    }

    void VulkanGraphicsContext::RegisterDescriptorSetForFrame(std::weak_ptr<VulkanGraphicsPipelineSignature> signature,
                                                              std::shared_ptr<VulkanGraphicsDescriptorSet> set)
    {
        auto it = _vulkanDescriptorSets.find(signature);
        if (it == _vulkanDescriptorSets.end())
        {
            _vulkanDescriptorSets.emplace_hint(it, signature, std::vector{set});
            return;
        }

        it->second.emplace_back(set);
    }
}
