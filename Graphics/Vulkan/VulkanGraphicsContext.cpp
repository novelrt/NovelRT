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

    VkCommandPool CreateVulkanCommandPool(VulkanGraphicsContext* context)
    {
        VkCommandPool vulkanCommandPool = VK_NULL_HANDLE;

        auto device = context->GetDevice().lock();

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

        auto device = context->GetDevice().lock();

        VkResult result = vkAllocateCommandBuffers(device->GetVulkanDevice(), &commandBufferAllocateInfo, &vulkanCommandBuffer);

        if (result != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException(
                "Failed to initialise the VkCommandBuffer instance with the given parameters and VkDevice.", result);
        }

        return vulkanCommandBuffer;
    }

    VkFramebuffer CreateVulkanFramebuffer(VulkanGraphicsContext* context)
    {
        VkFramebuffer vulkanFramebuffer = VK_NULL_HANDLE;
        auto device = context->GetDevice().lock();
        IGraphicsSurface* surface = device->GetSurface();
        VkImageView swapChainImageView = context->GetVulkanSwapChainImageView();

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

    VkImageView CreateVulkanSwapChainImageView(VulkanGraphicsContext* context)
    {
        VkImageView swapChainImageView = VK_NULL_HANDLE;
        auto device = context->GetDevice().lock();

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
        swapChainImageViewCreateInfo.image = device->GetVulkanSwapChainImages()[context->GetIndex()];
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

    void VulkanGraphicsContext::DestroyDescriptorSets()
    {
        /*
        for (const auto& pair : _vulkanDescriptorSets)
        {
            // If the signature has already expired, assume all of its descriptor sets have too
            if (auto signature = pair.first.lock())
            {
                std::vector<VkDescriptorSet> sets(pair.second.size());
                for (const auto& setPtr : pair.second)
                {
                    // Ignore any sets which have expired
                    if (auto set = setPtr.lock())
                    {
                        sets.push_back(set->GetVulkanDescriptorSet());
                    }
                }


                auto pool = signature->GetVulkanDescriptorPool();

                // TODO: this should likely check its result
                vkFreeDescriptorSets(_device->GetVulkanDevice(), pool, static_cast<int32_t>(sets.size()), sets.data());
            }
        }
        */

        _vulkanDescriptorSets.clear();
    }

    //NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
    std::shared_ptr<VulkanGraphicsContext> VulkanGraphicsContext::shared_from_this()
    {
        return std::static_pointer_cast<VulkanGraphicsContext>(GraphicsDeviceObject::shared_from_this());
    }
    //NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
    std::shared_ptr<const VulkanGraphicsContext> VulkanGraphicsContext::shared_from_this() const
    {
        return std::static_pointer_cast<const VulkanGraphicsContext>(GraphicsDeviceObject::shared_from_this());
    }

    VulkanGraphicsContext::GraphicsContext(std::shared_ptr<VulkanGraphicsDevice> device, size_t index) noexcept
        : _device(device)
        , _index(index)
        , _vulkanDescriptorSets()
        , _fence(std::make_shared<VulkanGraphicsFence>(device, /* isSignaled*/ true))
        , _waitForExecuteCompletionFence(std::make_shared<VulkanGraphicsFence>(device, /* isSignaled*/ false))
        , _vulkanCommandBuffer([this]() { return CreateVulkanCommandBuffer(this); })
        , _vulkanCommandPool([this]() { return CreateVulkanCommandPool(this); })
        , _vulkanFramebuffer([this]() { return CreateVulkanFramebuffer(this); })
        , _vulkanSwapChainImageView([this]() { return CreateVulkanSwapChainImageView(this); })
    {
        static_cast<void>(_state.Transition(Threading::VolatileState::Initialised));
    }

    VulkanGraphicsContext::~GraphicsContext()
    {
        DestroyDescriptorSets();

        VkDevice device = _device->GetVulkanDevice();
        if (_vulkanFramebuffer.HasValue())
        {
            VkFramebuffer framebuffer = _vulkanFramebuffer.Get();
            vkDestroyFramebuffer(device, framebuffer, nullptr);
            _vulkanFramebuffer.Reset();
        }

        if (_vulkanSwapChainImageView.HasValue())
        {
            VkImageView imageView = _vulkanSwapChainImageView.Get();
            vkDestroyImageView(device, imageView, nullptr);
            _vulkanSwapChainImageView.Reset();
        }

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

    std::weak_ptr<VulkanGraphicsFence> VulkanGraphicsContext::GetFence() const noexcept
    {
        return _fence;
    }

    size_t VulkanGraphicsContext::GetIndex() const noexcept
    {
        return _index;
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

    void VulkanGraphicsContext::OnGraphicsSurfaceSizeChanged(Maths::GeoVector2F /*newSize*/)
    {
        VkDevice device = _device->GetVulkanDevice();
        if (_vulkanFramebuffer.HasValue())
        {
            VkFramebuffer framebuffer = _vulkanFramebuffer.Get();
            vkDestroyFramebuffer(device, framebuffer, nullptr);
            _vulkanFramebuffer.Reset();
        }

        if (_vulkanSwapChainImageView.HasValue())
        {
            VkImageView imageView = _vulkanSwapChainImageView.Get();
            vkDestroyImageView(device, imageView, nullptr);
            _vulkanSwapChainImageView.Reset();
        }

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

    VkCommandBuffer VulkanGraphicsContext::GetVulkanCommandBuffer() const
    {
        return _vulkanCommandBuffer.Get();
    }
    VkCommandPool VulkanGraphicsContext::GetVulkanCommandPool() const
    {
        return _vulkanCommandPool.Get();
    }
    VkFramebuffer VulkanGraphicsContext::GetVulkanFramebuffer() const
    {
        return _vulkanFramebuffer.Get();
    }
    VkImageView VulkanGraphicsContext::GetVulkanSwapChainImageView() const
    {
        return _vulkanSwapChainImageView.Get();
    }

    std::weak_ptr<VulkanGraphicsFence> VulkanGraphicsContext::GetWaitForExecuteCompletionFence() const noexcept
    {
        return _waitForExecuteCompletionFence;
    }

    void VulkanGraphicsContext::RegisterDescriptorSetForFrame(std::weak_ptr<VulkanGraphicsPipelineSignature> signature, std::weak_ptr<VulkanGraphicsDescriptorSet> set)
    {
        auto it = _vulkanDescriptorSets.find(signature);
        if (it == _vulkanDescriptorSets.end())
        {
            _vulkanDescriptorSets.emplace_hint(it, signature, std::vector{ set });
            return;
        }

        it->second.emplace_back(set);
    }
}
