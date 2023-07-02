// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/Vulkan/Graphics.Vulkan.hpp>

namespace NovelRT::Graphics::Vulkan
{

    void VulkanGraphicsContext::OnGraphicsSurfaceSizeChanged(Maths::GeoVector2F /*newSize*/)
    {
        if (_vulkanFramebuffer.isCreated())
        {
            VkFramebuffer vulkanFramebuffer = _vulkanFramebuffer.getActual();
            DisposeVulkanFramebuffer(vulkanFramebuffer);
            _vulkanFramebuffer.reset();
        }

        if (_vulkanSwapChainImageView.isCreated())
        {
            VkImageView vulkanSwapChainImageView = _vulkanSwapChainImageView.getActual();
            DisposeVulkanSwapChainImageView(vulkanSwapChainImageView);
            _vulkanSwapChainImageView.reset();
        }

        if (_vulkanCommandBuffer.isCreated())
        {
            VkCommandBuffer commandBuffer = _vulkanCommandBuffer.getActual();
            DisposeVulkanCommandBuffer(commandBuffer);
            _vulkanCommandBuffer.reset();
        }

        if (_vulkanCommandPool.isCreated())
        {
            VkCommandPool pool = _vulkanCommandPool.getActual();
            DisposeVulkanCommandPool(pool);
            _vulkanCommandPool.reset();
        }
    }

    VkCommandBuffer VulkanGraphicsContext::CreateVulkanCommandBuffer()
    {
        VkCommandBuffer vulkanCommandBuffer = VK_NULL_HANDLE;

        VkCommandBufferAllocateInfo commandBufferAllocateInfo{};
        commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        commandBufferAllocateInfo.commandPool = GetVulkanCommandPool();
        commandBufferAllocateInfo.commandBufferCount = 1;

        VkResult result =
            vkAllocateCommandBuffers(GetDevice()->GetVulkanDevice(), &commandBufferAllocateInfo, &vulkanCommandBuffer);

        if (result != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException(
                "Failed to initialise the VkCommandBuffer instance with the given parameters and VkDevice.", result);
        }

        return vulkanCommandBuffer;
    }

    VkCommandPool VulkanGraphicsContext::CreateVulkanCommandPool()
    {
        VkCommandPool vulkanCommandPool = VK_NULL_HANDLE;

        VkCommandPoolCreateInfo commandPoolCreateInfo{};
        commandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        commandPoolCreateInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
        commandPoolCreateInfo.queueFamilyIndex = GetDevice()->GetIndicesData().graphicsFamily.value();

        VkResult result =
            vkCreateCommandPool(GetDevice()->GetVulkanDevice(), &commandPoolCreateInfo, nullptr, &vulkanCommandPool);

        if (result != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException(
                "Failed to initialise the VkCommandPool instance with the given parameters and VkDevice.", result);
        }

        return vulkanCommandPool;
    }

    VkFramebuffer VulkanGraphicsContext::CreateVulkanFramebuffer()
    {
        VkFramebuffer vulkanFramebuffer = VK_NULL_HANDLE;
        std::shared_ptr<VulkanGraphicsDevice> device = GetDevice();
        std::shared_ptr<IGraphicsSurface> surface = device->GetSurface();
        VkImageView swapChainImageView = GetVulkanSwapChainImageView();

        VkFramebufferCreateInfo framebufferCreateInfo{};
        framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferCreateInfo.renderPass = device->GetVulkanRenderPass();
        framebufferCreateInfo.attachmentCount = 1;
        framebufferCreateInfo.pAttachments = &swapChainImageView;
        framebufferCreateInfo.width = static_cast<uint32_t>(surface->GetWidth());
        framebufferCreateInfo.height = static_cast<uint32_t>(surface->GetHeight());
        framebufferCreateInfo.layers = 1;

        VkResult result =
            vkCreateFramebuffer(device->GetVulkanDevice(), &framebufferCreateInfo, nullptr, &vulkanFramebuffer);

        if (result != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException(
                "Failed to initialise the VkFramebuffer instance with the given parameters and VkDevice.", result);
        }

        return vulkanFramebuffer;
    }

    VkImageView VulkanGraphicsContext::CreateVulkanSwapChainImageView()
    {
        VkImageView swapChainImageView = VK_NULL_HANDLE;
        std::shared_ptr<VulkanGraphicsDevice> device = GetDevice();

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

    void VulkanGraphicsContext::DisposeVulkanCommandBuffer(VkCommandBuffer vulkanCommandBuffer) noexcept
    {
        if (vulkanCommandBuffer != VK_NULL_HANDLE)
        {
            vkFreeCommandBuffers(GetDevice()->GetVulkanDevice(), GetVulkanCommandPool(), 1, &vulkanCommandBuffer);
        }
    }

    void VulkanGraphicsContext::DisposeVulkanCommandPool(VkCommandPool vulkanCommandPool) noexcept
    {
        if (vulkanCommandPool != VK_NULL_HANDLE)
        {
            vkDestroyCommandPool(GetDevice()->GetVulkanDevice(), vulkanCommandPool, nullptr);
        }
    }

    void VulkanGraphicsContext::DisposeVulkanFramebuffer(VkFramebuffer vulkanFramebuffer) noexcept
    {
        if (vulkanFramebuffer != VK_NULL_HANDLE)
        {
            vkDestroyFramebuffer(GetDevice()->GetVulkanDevice(), vulkanFramebuffer, nullptr);
        }
    }

    void VulkanGraphicsContext::DisposeVulkanSwapChainImageView(VkImageView vulkanSwapChainImageView) noexcept
    {
        if (vulkanSwapChainImageView != VK_NULL_HANDLE)
        {
            vkDestroyImageView(GetDevice()->GetVulkanDevice(), vulkanSwapChainImageView, nullptr);
        }
    }

    void VulkanGraphicsContext::BeginCopy(VkImage vulkanImage) noexcept
    {
        VkImageSubresourceRange subresourceRange{};
        subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        subresourceRange.levelCount = 1;
        subresourceRange.layerCount = 1;

        VkImageMemoryBarrier vulkanImageMemoryBarrier{};
        vulkanImageMemoryBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        vulkanImageMemoryBarrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        vulkanImageMemoryBarrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        vulkanImageMemoryBarrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
        vulkanImageMemoryBarrier.subresourceRange = subresourceRange;
        vulkanImageMemoryBarrier.image = vulkanImage;

        vkCmdPipelineBarrier(GetVulkanCommandBuffer(), VK_PIPELINE_STAGE_HOST_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0,
                             nullptr, 0, nullptr, 1, &vulkanImageMemoryBarrier);
    }

    void VulkanGraphicsContext::EndCopy(VkImage vulkanImage) noexcept
    {
        VkImageSubresourceRange subresourceRange{};
        subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        subresourceRange.levelCount = 1;
        subresourceRange.layerCount = 1;

        VkImageMemoryBarrier vulkanImageMemoryBarrier{};
        vulkanImageMemoryBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        vulkanImageMemoryBarrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        vulkanImageMemoryBarrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
        vulkanImageMemoryBarrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
        vulkanImageMemoryBarrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        vulkanImageMemoryBarrier.subresourceRange = subresourceRange;
        vulkanImageMemoryBarrier.image = vulkanImage;

        vkCmdPipelineBarrier(GetVulkanCommandBuffer(), VK_PIPELINE_STAGE_TRANSFER_BIT,
                             VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0, 0, nullptr, 0, nullptr, 1,
                             &vulkanImageMemoryBarrier);
    }

    VulkanGraphicsContext::VulkanGraphicsContext(std::shared_ptr<VulkanGraphicsDevice> device, size_t index) noexcept
        : GraphicsContext(std::move(device), index),
          _fence(std::make_shared<VulkanGraphicsFence>(GetDevice(), /* isSignaled*/ true)),
          _waitForExecuteCompletionFence(std::make_shared<VulkanGraphicsFence>(GetDevice(), /* isSignaled*/ false)),
          _vulkanCommandBuffer([&]() { return CreateVulkanCommandBuffer(); }),
          _vulkanCommandPool([&]() { return CreateVulkanCommandPool(); }),
          _vulkanFramebuffer([&]() { return CreateVulkanFramebuffer(); }),
          _vulkanSwapChainImageView([&]() { return CreateVulkanSwapChainImageView(); })
    {
        static_cast<void>(_state.Transition(Threading::VolatileState::Initialised));
    }

    void VulkanGraphicsContext::BeginDrawing(NovelRT::Graphics::RGBAColour backgroundColour)
    {
        DestroyDescriptorSets();
        VkClearValue clearValue{};
        clearValue.color.float32[0] = backgroundColour.getRScalar();
        clearValue.color.float32[1] = backgroundColour.getGScalar();
        clearValue.color.float32[2] = backgroundColour.getBScalar();
        clearValue.color.float32[3] = backgroundColour.getAScalar();

        std::shared_ptr<VulkanGraphicsDevice> device = GetDevice();
        std::shared_ptr<IGraphicsSurface> surface = device->GetSurface();

        float surfaceWidth = surface->GetWidth();
        float surfaceHeight = surface->GetHeight();

        VkExtent2D extent2D{};
        extent2D.width = static_cast<uint32_t>(surfaceWidth);
        extent2D.height = static_cast<uint32_t>(surfaceHeight);

        VkRect2D renderArea{};
        renderArea.extent = extent2D;

        VkRenderPassBeginInfo renderPassBeginInfo{};
        renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassBeginInfo.renderPass = device->GetVulkanRenderPass();
        renderPassBeginInfo.framebuffer = GetVulkanFramebuffer();
        renderPassBeginInfo.renderArea = renderArea;
        renderPassBeginInfo.clearValueCount = 1;
        renderPassBeginInfo.pClearValues = &clearValue;

        VkCommandBuffer commandBuffer = GetVulkanCommandBuffer();
        vkCmdBeginRenderPass(commandBuffer, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

        VkViewport viewport{};
        viewport.x = 0;
        viewport.y = surfaceHeight;
        viewport.width = surfaceWidth;
        viewport.height = -surfaceHeight;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;

        vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

        VkRect2D scissorRect{};
        scissorRect.extent = extent2D;

        vkCmdSetScissor(commandBuffer, 0, 1, &scissorRect);
    }

    void VulkanGraphicsContext::BeginFrame()
    {
        std::shared_ptr<VulkanGraphicsFence> fence = GetVulkanFence();
        fence->Wait();
        fence->Reset();

        VkCommandBufferBeginInfo commandBufferBeginInfo{};
        commandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        VkResult result = vkBeginCommandBuffer(GetVulkanCommandBuffer(), &commandBufferBeginInfo);

        if (result != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException(
                "Failed to initialise on the VkCommandBuffer instance correctly.", result);
        }
    }

    void VulkanGraphicsContext::EndDrawing()
    {
        vkCmdEndRenderPass(GetVulkanCommandBuffer());
    }

    void VulkanGraphicsContext::EndFrame()
    {
        VkCommandBuffer commandBuffer = GetVulkanCommandBuffer();

        VkResult endCommandBufferResult = vkEndCommandBuffer(commandBuffer);

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

        std::shared_ptr<VulkanGraphicsFence> executeGraphicsFence = GetWaitForExecuteCompletionFence();

        VkResult queueSubmitResult = vkQueueSubmit(GetDevice()->GetVulkanGraphicsQueue(), 1, &submitInfo,
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
        if (_vulkanFramebuffer.isCreated())
        {
            DisposeVulkanFramebuffer(_vulkanFramebuffer.getActual());
            _vulkanFramebuffer.reset();
        }

        if (_vulkanSwapChainImageView.isCreated())
        {
            DisposeVulkanSwapChainImageView(_vulkanSwapChainImageView.getActual());
            _vulkanSwapChainImageView.reset();
        }
    }

    VulkanGraphicsContext::~VulkanGraphicsContext()
    {
        DestroyDescriptorSets();

        if (_vulkanCommandBuffer.isCreated())
        {
            DisposeVulkanCommandBuffer(_vulkanCommandBuffer.getActual());
            _vulkanCommandBuffer.reset();
        }

        if (_vulkanCommandPool.isCreated())
        {
            DisposeVulkanCommandPool(_vulkanCommandPool.getActual());
            _vulkanCommandPool.reset();
        }

        ResetContext();
    }

    void VulkanGraphicsContext::DestroyDescriptorSets()
    {
        for (auto&& pair : _vulkanDescriptorSets)
        {
            pair.first->DestroyDescriptorSets(pair.second);
        }

        _vulkanDescriptorSets.clear();
    }
} // namespace NovelRT::Graphics::Vulkan
