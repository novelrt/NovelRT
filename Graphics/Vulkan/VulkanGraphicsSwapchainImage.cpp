// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InitialisationFailureException.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsCmdList.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsContext.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsFence.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsSemaphore.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsSwapchain.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsSwapchainImage.hpp>
#include <mutex>
#include <vulkan/vulkan.h>

namespace NovelRT::Graphics
{
    VkImageView CreateVulkanSwapChainImageView(
        std::shared_ptr<GraphicsSwapchain<Vulkan::VulkanGraphicsBackend>> swapchain,
        VkImage image,
        VkFormat imageFormat)
    {
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
        swapChainImageViewCreateInfo.image = image;
        swapChainImageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        swapChainImageViewCreateInfo.format = imageFormat;
        swapChainImageViewCreateInfo.components = componentMapping;
        swapChainImageViewCreateInfo.subresourceRange = subresourceRange;

        VkImageView swapChainImageView = VK_NULL_HANDLE;
        VkResult result = vkCreateImageView(swapchain->GetDevice()->GetVulkanDevice(), &swapChainImageViewCreateInfo,
                                            nullptr, &swapChainImageView);

        if (result != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException(
                "Failed to initialise VkImageView instance with the given parameters and VkDevice.", result);
        }

        return swapChainImageView;
    }

    // NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
    std::shared_ptr<GraphicsSwapchainImage<Vulkan::VulkanGraphicsBackend>> GraphicsSwapchainImage<
        Vulkan::VulkanGraphicsBackend>::shared_from_this()
    {
        return std::static_pointer_cast<GraphicsSwapchainImage<Vulkan::VulkanGraphicsBackend>>(
            GraphicsDeviceObject::shared_from_this());
    }

    GraphicsSwapchainImage<Vulkan::VulkanGraphicsBackend>::GraphicsSwapchainImage(
        std::shared_ptr<GraphicsSwapchain<Vulkan::VulkanGraphicsBackend>> swapchain,
        VkImage image,
        VkFormat imageFormat,
        uint32_t width,
        uint32_t height)
        : _swapchain(std::move(swapchain)),
          _image(image),
          _imageView(CreateVulkanSwapChainImageView(_swapchain, _image, imageFormat)),
          _width(width),
          _height(height)
    {
    }
    
    GraphicsSwapchainImage<Vulkan::VulkanGraphicsBackend>::~GraphicsSwapchainImage() noexcept
    {
        vkDestroyImageView(GetDevice()->GetVulkanDevice(), _imageView, nullptr);
    }

    std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> GraphicsSwapchainImage<
        Vulkan::VulkanGraphicsBackend>::GetDevice() const
    {
        return _swapchain->GetDevice();
    }

    std::shared_ptr<GraphicsSwapchain<Vulkan::VulkanGraphicsBackend>> GraphicsSwapchainImage<
        Vulkan::VulkanGraphicsBackend>::GetSwapchain() const
    {
        return _swapchain;
    }

    VkImage GraphicsSwapchainImage<Vulkan::VulkanGraphicsBackend>::GetVulkanImage() const noexcept
    {
        return _image;
    }

    VkImageView GraphicsSwapchainImage<Vulkan::VulkanGraphicsBackend>::GetVulkanImageView() const noexcept
    {
        return _imageView;
    }

    uint32_t GraphicsSwapchainImage<Vulkan::VulkanGraphicsBackend>::GetWidth() const noexcept
    {
        return _width;
    }

    uint32_t GraphicsSwapchainImage<Vulkan::VulkanGraphicsBackend>::GetHeight() const noexcept
    {
        return _height;
    }

    void GraphicsSwapchainImage<Vulkan::VulkanGraphicsBackend>::QueueSubmit(
        std::shared_ptr<GraphicsCmdList<Vulkan::VulkanGraphicsBackend>> cmdList)
    {
        std::vector<std::shared_ptr<GraphicsCmdList<Vulkan::VulkanGraphicsBackend>>> cmdLists{cmdList};
        QueueSubmit({}, cmdLists, {});
    }
    void GraphicsSwapchainImage<Vulkan::VulkanGraphicsBackend>::QueueSubmit(
        std::pair<std::shared_ptr<GraphicsSemaphore<Vulkan::VulkanGraphicsBackend>>, uint64_t> semaphoreToWait,
        std::shared_ptr<GraphicsCmdList<Vulkan::VulkanGraphicsBackend>> cmdList)
    {
        std::vector<std::pair<std::shared_ptr<GraphicsSemaphore<Vulkan::VulkanGraphicsBackend>>, uint64_t>>
            semaphoresToWait{semaphoreToWait};
        std::vector<std::shared_ptr<GraphicsCmdList<Vulkan::VulkanGraphicsBackend>>> cmdLists{cmdList};
        QueueSubmit(semaphoresToWait, cmdLists, {});
    }
    void GraphicsSwapchainImage<Vulkan::VulkanGraphicsBackend>::QueueSubmit(
        std::shared_ptr<GraphicsCmdList<Vulkan::VulkanGraphicsBackend>> cmdList,
        std::pair<std::shared_ptr<GraphicsSemaphore<Vulkan::VulkanGraphicsBackend>>, uint64_t> semaphoreToSignal)
    {
        std::vector<std::shared_ptr<GraphicsCmdList<Vulkan::VulkanGraphicsBackend>>> cmdLists{cmdList};
        std::vector<std::pair<std::shared_ptr<GraphicsSemaphore<Vulkan::VulkanGraphicsBackend>>, uint64_t>>
            semaphoresToSignal{semaphoreToSignal};
        QueueSubmit({}, cmdLists, semaphoresToSignal);
    }
    void GraphicsSwapchainImage<Vulkan::VulkanGraphicsBackend>::QueueSubmit(
        std::pair<std::shared_ptr<GraphicsSemaphore<Vulkan::VulkanGraphicsBackend>>, uint64_t> semaphoreToWait,
        std::shared_ptr<GraphicsCmdList<Vulkan::VulkanGraphicsBackend>> cmdList,
        std::pair<std::shared_ptr<GraphicsSemaphore<Vulkan::VulkanGraphicsBackend>>, uint64_t> semaphoreToSignal)
    {
        std::vector<std::pair<std::shared_ptr<GraphicsSemaphore<Vulkan::VulkanGraphicsBackend>>, uint64_t>>
            semaphoresToWait{semaphoreToWait};
        std::vector<std::shared_ptr<GraphicsCmdList<Vulkan::VulkanGraphicsBackend>>> cmdLists{cmdList};
        std::vector<std::pair<std::shared_ptr<GraphicsSemaphore<Vulkan::VulkanGraphicsBackend>>, uint64_t>>
            semaphoresToSignal{semaphoreToSignal};
        QueueSubmit(semaphoresToWait, cmdLists, semaphoresToSignal);
    }

    void GraphicsSwapchainImage<Vulkan::VulkanGraphicsBackend>::QueueSubmit(
        NovelRT::Utilities::Span<std::shared_ptr<GraphicsCmdList<Vulkan::VulkanGraphicsBackend>>> cmdLists)
    {
        QueueSubmit({}, cmdLists, {});
    }
    void GraphicsSwapchainImage<Vulkan::VulkanGraphicsBackend>::QueueSubmit(
        NovelRT::Utilities::Span<std::pair<std::shared_ptr<GraphicsSemaphore<Vulkan::VulkanGraphicsBackend>>, uint64_t>>
            semaphoresToWait,
        NovelRT::Utilities::Span<std::shared_ptr<GraphicsCmdList<Vulkan::VulkanGraphicsBackend>>> cmdLists)
    {
        QueueSubmit(semaphoresToWait, cmdLists, {});
    }
    void GraphicsSwapchainImage<Vulkan::VulkanGraphicsBackend>::QueueSubmit(
        NovelRT::Utilities::Span<std::shared_ptr<GraphicsCmdList<Vulkan::VulkanGraphicsBackend>>> cmdLists,
        NovelRT::Utilities::Span<std::pair<std::shared_ptr<GraphicsSemaphore<Vulkan::VulkanGraphicsBackend>>, uint64_t>>
            semaphoresToSignal)
    {
        QueueSubmit({}, cmdLists, semaphoresToSignal);
    }

    void GraphicsSwapchainImage<Vulkan::VulkanGraphicsBackend>::QueueSubmit(
        NovelRT::Utilities::Span<std::pair<std::shared_ptr<GraphicsSemaphore<Vulkan::VulkanGraphicsBackend>>, uint64_t>>
            semaphoresToWait,
        NovelRT::Utilities::Span<std::shared_ptr<GraphicsCmdList<Vulkan::VulkanGraphicsBackend>>> cmdLists,
        NovelRT::Utilities::Span<std::pair<std::shared_ptr<GraphicsSemaphore<Vulkan::VulkanGraphicsBackend>>, uint64_t>>
            semaphoresToSignal)
    {
        VkSemaphore vulkanSemaphore = _swapchain->GetActiveSemaphore(shared_from_this())->GetVulkanSemaphore();
        VkPipelineStageFlags allCommands = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT;

        std::vector<VkCommandBuffer> buffers(cmdLists.size());
        std::vector<VkSemaphore> waitSemaphores(semaphoresToWait.size());
        std::vector<uint64_t> waitSemaphoreValues(semaphoresToWait.size());
        std::vector<VkSemaphore> signalSemaphores(semaphoresToSignal.size());
        std::vector<uint64_t> signalSemaphoreValues(semaphoresToSignal.size());
        std::transform(cmdLists.begin(), cmdLists.end(), buffers.begin(),
                       [](const auto& cmdList) { return cmdList->GetVkCommandBuffer(); });
        std::transform(semaphoresToWait.begin(), semaphoresToWait.end(), waitSemaphores.begin(),
                       [](const auto& semaphore) { return semaphore.first->GetVulkanSemaphore(); });
        std::transform(semaphoresToWait.begin(), semaphoresToWait.end(), waitSemaphoreValues.begin(),
                       [](const auto& semaphore) { return semaphore.second; });
        std::transform(semaphoresToSignal.begin(), semaphoresToSignal.end(), signalSemaphores.begin(),
                       [](const auto& semaphore) { return semaphore.first->GetVulkanSemaphore(); });
        std::transform(semaphoresToSignal.begin(), semaphoresToSignal.end(), signalSemaphoreValues.begin(),
                       [](const auto& semaphore) { return semaphore.second; });

        waitSemaphores.push_back(vulkanSemaphore);
        waitSemaphoreValues.push_back(0);
        signalSemaphores.push_back(vulkanSemaphore);
        signalSemaphoreValues.push_back(0);

        VkTimelineSemaphoreSubmitInfo semaphoreSubmitInfo{};
        semaphoreSubmitInfo.sType = VK_STRUCTURE_TYPE_TIMELINE_SEMAPHORE_SUBMIT_INFO;
        semaphoreSubmitInfo.waitSemaphoreValueCount = static_cast<uint32_t>(waitSemaphoreValues.size());
        semaphoreSubmitInfo.pWaitSemaphoreValues = waitSemaphoreValues.data();
        semaphoreSubmitInfo.signalSemaphoreValueCount = static_cast<uint32_t>(signalSemaphoreValues.size());
        semaphoreSubmitInfo.pSignalSemaphoreValues = signalSemaphoreValues.data();

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.pNext = &semaphoreSubmitInfo;
        submitInfo.commandBufferCount = static_cast<uint32_t>(buffers.size());
        submitInfo.pCommandBuffers = buffers.data();
        submitInfo.signalSemaphoreCount = static_cast<uint32_t>(signalSemaphores.size());
        submitInfo.pSignalSemaphores = signalSemaphores.data();
        submitInfo.waitSemaphoreCount = static_cast<uint32_t>(waitSemaphores.size());
        submitInfo.pWaitSemaphores = waitSemaphores.data();
        submitInfo.pWaitDstStageMask = &allCommands;

        // TODO: submit to the correct queue if it's just transfers somehow?
        const VkResult queueSubmitResult =
            vkQueueSubmit(GetDevice()->GetVulkanGraphicsQueue(), 1, &submitInfo, VK_NULL_HANDLE);
        if (queueSubmitResult != VK_SUCCESS)
        {
            throw std::runtime_error("vkQueueSubmit failed! Reason: " + std::to_string(queueSubmitResult));
        }
    }
}
