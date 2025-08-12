// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsRenderPass.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsContext.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsRenderPass.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsSwapchain.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsSwapchainImage.hpp>

#include <NovelRT/Exceptions/InitialisationFailureException.hpp>

namespace NovelRT::Graphics
{
    using VulkanGraphicsRenderPass = GraphicsRenderPass<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsSwapchainImage = GraphicsSwapchainImage<Vulkan::VulkanGraphicsBackend>;

    VkFramebuffer CreateVulkanFramebuffer(VkDevice device, VkRenderPass renderPass, VkImageView swapchainImageView, uint32_t width, uint32_t height, uint32_t layers = 1)
    {
        VkFramebufferCreateInfo framebufferCreateInfo{};
        framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferCreateInfo.renderPass = renderPass;
        framebufferCreateInfo.attachmentCount = 1;
        framebufferCreateInfo.pAttachments = &swapchainImageView;
        framebufferCreateInfo.width = width;
        framebufferCreateInfo.height = height;
        framebufferCreateInfo.layers = layers;

        VkFramebuffer vulkanFramebuffer = VK_NULL_HANDLE;
        const VkResult result = vkCreateFramebuffer(device, &framebufferCreateInfo, nullptr, &vulkanFramebuffer);

        if (result != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException(
                "Failed to initialise the VkFramebuffer instance with the given parameters and VkDevice.", result);
        }

        return vulkanFramebuffer;
    }

    VkRenderPass CreateRenderPass(std::shared_ptr<VulkanGraphicsSwapchainImage> image)
    {
        VkAttachmentDescription attachmentDescription{};
        attachmentDescription.format = image->GetSwapchain()->GetVulkanFormat();
        attachmentDescription.samples = VK_SAMPLE_COUNT_1_BIT;
        attachmentDescription.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        attachmentDescription.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        attachmentDescription.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        attachmentDescription.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

        VkAttachmentReference colourAttachmentReference{};
        colourAttachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        VkSubpassDescription subpass{};
        subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpass.colorAttachmentCount = 1;
        subpass.pColorAttachments = &colourAttachmentReference;

        VkSubpassDependency dependency = {};
        dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
        dependency.dstSubpass = 0;
        dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.srcAccessMask = 0;
        dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

        VkRenderPassCreateInfo renderPassCreateInfo{};
        renderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        renderPassCreateInfo.attachmentCount = 1;
        renderPassCreateInfo.pAttachments = &attachmentDescription;
        renderPassCreateInfo.subpassCount = 1;
        renderPassCreateInfo.pSubpasses = &subpass;
        renderPassCreateInfo.pDependencies = &dependency;
        renderPassCreateInfo.dependencyCount = 1;

        VkRenderPass returnRenderPass = VK_NULL_HANDLE;
        VkResult renderPassResult =
            vkCreateRenderPass(image->GetDevice()->GetVulkanDevice(), &renderPassCreateInfo, nullptr, &returnRenderPass);

        if (renderPassResult != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to create the VkRenderPass.", renderPassResult);
        }

        return returnRenderPass;
    }

    VulkanGraphicsRenderPass::GraphicsRenderPass(
        std::shared_ptr<GraphicsContext<Vulkan::VulkanGraphicsBackend>> context,
        std::shared_ptr<GraphicsSwapchainImage<Vulkan::VulkanGraphicsBackend>> target)
        : _context(std::move(context)),
          _vulkanRenderPass(CreateRenderPass(target)),
          _vulkanFrameBuffer(CreateVulkanFramebuffer(target->GetDevice()->GetVulkanDevice(), _vulkanRenderPass, target->GetVulkanImageView(), target->GetWidth(), target->GetHeight()))
    {
    }

    VulkanGraphicsRenderPass::~GraphicsRenderPass() noexcept
    {
        vkDestroyRenderPass(GetDevice()->GetVulkanDevice(), _vulkanRenderPass, nullptr);
        vkDestroyFramebuffer(GetDevice()->GetVulkanDevice(), _vulkanFrameBuffer, nullptr);
    }

    std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> VulkanGraphicsRenderPass::GetDevice() const
    {
        return _context->GetDevice();
    }

    std::shared_ptr<GraphicsContext<Vulkan::VulkanGraphicsBackend>> VulkanGraphicsRenderPass::GetContext() const
    {
        return _context;
    }

    VkRenderPass VulkanGraphicsRenderPass::GetVulkanRenderPass() const noexcept
    {
        return _vulkanRenderPass;
    }

    VkFramebuffer VulkanGraphicsRenderPass::GetVulkanFramebuffer() const noexcept
    {
        return _vulkanFrameBuffer;
    }
}
