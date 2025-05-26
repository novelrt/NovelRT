// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InitialisationFailureException.hpp>

#include <NovelRT/Graphics/Vulkan/VulkanGraphicsContext.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDescriptorSet.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsFence.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsPipelineSignature.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsCmdList.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDescriptorSet.hpp>

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
    template <template <typename> typename TResource>
    using VulkanGraphicsResourceMemoryRegion = GraphicsResourceMemoryRegion<TResource, Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsTexture = GraphicsTexture<Vulkan::VulkanGraphicsBackend>;

    void VulkanGraphicsContext::OnGraphicsSurfaceSizeChanged(Maths::GeoVector2F /*newSize*/)
    {
        if (_vulkanFramebuffer.HasValue())
        {
            VkFramebuffer vulkanFramebuffer = _vulkanFramebuffer.Get();
            DisposeVulkanFramebuffer(vulkanFramebuffer);
            _vulkanFramebuffer.Reset();
        }

        if (_vulkanSwapChainImageView.HasValue())
        {
            VkImageView vulkanSwapChainImageView = _vulkanSwapChainImageView.Get();
            DisposeVulkanSwapChainImageView(vulkanSwapChainImageView);
            _vulkanSwapChainImageView.Reset();
        }

        if (_vulkanCommandBuffer.HasValue())
        {
            VkCommandBuffer commandBuffer = _vulkanCommandBuffer.Get();
            DisposeVulkanCommandBuffer(commandBuffer);
            _vulkanCommandBuffer.Reset();
        }

        if (_vulkanCommandPool.HasValue())
        {
            VkCommandPool pool = _vulkanCommandPool.Get();
            DisposeVulkanCommandPool(pool);
            _vulkanCommandPool.Reset();
        }
    }

    VkCommandBuffer VulkanGraphicsContext::CreateVulkanCommandBuffer() const
    {
        VkCommandBuffer vulkanCommandBuffer = VK_NULL_HANDLE;

        VkCommandBufferAllocateInfo commandBufferAllocateInfo{};
        commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        commandBufferAllocateInfo.commandPool = GetVulkanCommandPool();
        commandBufferAllocateInfo.commandBufferCount = 1;

        auto device = GetDevice().lock();

        VkResult result =
            vkAllocateCommandBuffers(device->GetVulkanDevice(), &commandBufferAllocateInfo, &vulkanCommandBuffer);

        if (result != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException(
                "Failed to initialise the VkCommandBuffer instance with the given parameters and VkDevice.", result);
        }

        return vulkanCommandBuffer;
    }

    VkCommandPool VulkanGraphicsContext::CreateVulkanCommandPool() const
    {
        VkCommandPool vulkanCommandPool = VK_NULL_HANDLE;

        auto device = GetDevice().lock();

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

    VkFramebuffer VulkanGraphicsContext::CreateVulkanFramebuffer() const
    {
        VkFramebuffer vulkanFramebuffer = VK_NULL_HANDLE;
        auto device = GetDevice().lock();
        IGraphicsSurface* surface = device->GetSurface();
        VkImageView swapChainImageView = GetVulkanSwapChainImageView();

        VkFramebufferCreateInfo framebufferCreateInfo{};
        framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferCreateInfo.renderPass = device->GetVulkanRenderPass();
        framebufferCreateInfo.attachmentCount = 1;
        framebufferCreateInfo.pAttachments = &swapChainImageView;
        framebufferCreateInfo.width = static_cast<uint32_t>(surface->GetWidth());
        framebufferCreateInfo.height = static_cast<uint32_t>(surface->GetHeight());
        framebufferCreateInfo.layers = 1;

        const VkResult result = vkCreateFramebuffer(device->GetVulkanDevice(), &framebufferCreateInfo, nullptr, &vulkanFramebuffer);

        if (result != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException(
                "Failed to initialise the VkFramebuffer instance with the given parameters and VkDevice.", result);
        }

        return vulkanFramebuffer;
    }

    VkImageView VulkanGraphicsContext::CreateVulkanSwapChainImageView() const
    {
        VkImageView swapChainImageView = VK_NULL_HANDLE;
        auto device = GetDevice().lock();

        VkComponentMapping componentMapping{};
        componentMapping.r = VK_COMPONENT_SWIZZLE_R;
        componentMapping.g = VK_COMPONENT_SWIZZLE_G;
        componentMapping.b = VK_COMPONENT_SWIZZLE_B;
        componentMapping.a = VK_COMPONENT_SWIZZLE_A;

        VkImageSubresourceRange subresourceRange{};
        subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        subresourceRange.levelCount = 1;
        subresourceRange.layerCount = 1;

        VkImageViewCreateInfo swapChainImageViewCreateInfo{};
        swapChainImageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        swapChainImageViewCreateInfo.image = device->GetVulkanSwapChainImages()[GetIndex()];
        swapChainImageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        swapChainImageViewCreateInfo.format = device->GetVulkanSwapChainFormat();
        swapChainImageViewCreateInfo.components = componentMapping;
        swapChainImageViewCreateInfo.subresourceRange = subresourceRange;

        VkResult result =
            vkCreateImageView(device->GetVulkanDevice(), &swapChainImageViewCreateInfo, nullptr, &swapChainImageView);

        if (result != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException(
                "Failed to initialise VkImageView instance with the given parameters and VkDevice.", result);
        }

        return swapChainImageView;
    }

    void VulkanGraphicsContext::DisposeVulkanCommandBuffer(VkCommandBuffer vulkanCommandBuffer) const noexcept
    {
        if (vulkanCommandBuffer != VK_NULL_HANDLE)
        {
            auto device = GetDevice().lock();
            vkFreeCommandBuffers(device->GetVulkanDevice(), GetVulkanCommandPool(), 1, &vulkanCommandBuffer);
        }
    }

    void VulkanGraphicsContext::DisposeVulkanCommandPool(VkCommandPool vulkanCommandPool) const noexcept
{
        if (vulkanCommandPool != VK_NULL_HANDLE)
        {
            auto device = GetDevice().lock();
            vkDestroyCommandPool(device->GetVulkanDevice(), vulkanCommandPool, nullptr);
        }
    }

    void VulkanGraphicsContext::DisposeVulkanFramebuffer(VkFramebuffer vulkanFramebuffer) const noexcept
{
        if (vulkanFramebuffer != VK_NULL_HANDLE)
        {
            auto device = GetDevice().lock();
            vkDestroyFramebuffer(device->GetVulkanDevice(), vulkanFramebuffer, nullptr);
        }
    }

    void VulkanGraphicsContext::DisposeVulkanSwapChainImageView(VkImageView vulkanSwapChainImageView) const noexcept
    {
        if (vulkanSwapChainImageView != VK_NULL_HANDLE)
        {
            auto device = GetDevice().lock();
            vkDestroyImageView(device->GetVulkanDevice(), vulkanSwapChainImageView, nullptr);
        }
    }

    VulkanGraphicsContext::GraphicsContext(std::shared_ptr<VulkanGraphicsDevice> device, size_t index) noexcept
        : _device(device)
        , _index(index)
        , _fence(std::make_shared<VulkanGraphicsFence>(device, /* isSignaled*/ true))
        , _waitForExecuteCompletionFence(std::make_shared<VulkanGraphicsFence>(device, /* isSignaled*/ false))
        , _vulkanCommandBuffer([&]() { return CreateVulkanCommandBuffer(); })
        , _vulkanCommandPool([&]() { return CreateVulkanCommandPool(); })
        , _vulkanFramebuffer([&]() { return CreateVulkanFramebuffer(); })
        , _vulkanSwapChainImageView([&]() { return CreateVulkanSwapChainImageView(); })
    {
        static_cast<void>(_state.Transition(Threading::VolatileState::Initialised));
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

    void VulkanGraphicsContext::RegisterDescriptorSetForFrame(VulkanGraphicsPipelineSignature* signature, VulkanGraphicsDescriptorSet* set)
    {
        if (_vulkanDescriptorSets.find(signature) == _vulkanDescriptorSets.end())
        {
            _vulkanDescriptorSets.emplace(signature, std::vector<VulkanGraphicsDescriptorSet*>{set});
            return;
        }

        _vulkanDescriptorSets[signature].emplace_back(set);
    }

    void VulkanGraphicsContext::EndFrame() const
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

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffer;

        auto executeGraphicsFence = GetWaitForExecuteCompletionFence().lock();
        auto device = GetDevice().lock();

        const VkResult queueSubmitResult = vkQueueSubmit(device->GetVulkanGraphicsQueue(), 1, &submitInfo,
                                                   executeGraphicsFence->GetVulkanFence());

        if (queueSubmitResult != VK_SUCCESS)
        {
            throw std::runtime_error("vkQueueSubmit failed! Reason: " + std::to_string(queueSubmitResult));
        }

        executeGraphicsFence->Wait();
        executeGraphicsFence->Reset();
    }

    void VulkanGraphicsContext::ResetContext()
    {
        if (_vulkanFramebuffer.HasValue())
        {
            DisposeVulkanFramebuffer(_vulkanFramebuffer.Get());
            _vulkanFramebuffer.Reset();
        }

        if (_vulkanSwapChainImageView.HasValue())
        {
            DisposeVulkanSwapChainImageView(_vulkanSwapChainImageView.Get());
            _vulkanSwapChainImageView.Reset();
        }
    }

    VulkanGraphicsContext::~GraphicsContext()
    {
        DestroyDescriptorSets();

        if (_vulkanCommandBuffer.HasValue())
        {
            DisposeVulkanCommandBuffer(_vulkanCommandBuffer.Get());
            _vulkanCommandBuffer.Reset();
        }

        if (_vulkanCommandPool.HasValue())
        {
            DisposeVulkanCommandPool(_vulkanCommandPool.Get());
            _vulkanCommandPool.Reset();
        }

        ResetContext();
    }

    void VulkanGraphicsContext::DestroyDescriptorSets()
    {
        //for (auto&& pair : _vulkanDescriptorSets)
        //{
        //    std::vector<VkDescriptorSet> sets(pair.second.size());

        //    std::transform(pair.second.begin(), pair.second.end(), sets.begin(), [](const VulkanGraphicsDescriptorSet* set){ return set->GetVulkanDescriptorSet(); });

        //    pair.first->DestroyDescriptorSets(sets);
        //}

        _vulkanDescriptorSets.clear();
    }
}
