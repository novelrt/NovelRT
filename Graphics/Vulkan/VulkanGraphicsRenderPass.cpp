// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsRenderPass.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsContext.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsRenderPass.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsSwapchain.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsSwapchainImage.hpp>

#include <NovelRT/Exceptions/InitialisationFailureException.hpp>
#include <NovelRT/Graphics/GraphicsRenderPassDescription.hpp>
#include <NovelRT/Graphics/Vulkan/Utilities/Texel.hpp>
#include <algorithm>
#include <vulkan/vulkan_core.h>

namespace NovelRT::Graphics
{
    using VulkanGraphicsRenderPass = GraphicsRenderPass<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsSwapchainImage = GraphicsSwapchainImage<Vulkan::VulkanGraphicsBackend>;

    VkRenderPass CreateRenderPass(const GraphicsRenderPassDescription& description, VkDevice device)
    {
        std::vector<VkAttachmentDescription> attachmentDescriptions(description.attachmentDescriptions.size());

        std::transform(description.attachmentDescriptions.begin(), description.attachmentDescriptions.end(),
                       attachmentDescriptions.begin(),
                       [](const GraphicsAttachmentDescription& x)
                       {
                           VkAttachmentLoadOp loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;

                           switch (x.loadOp)
                           {
                               case LoadOp::Load:
                                   loadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
                                   break;
                               case LoadOp::Clear:
                                   loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
                                   break;
                               case LoadOp::DontCare:
                                   loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
                                   break;
                           }

                           VkAttachmentLoadOp stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;

                           switch (x.stencilLoadOp)
                           {
                               case LoadOp::Load:
                                   stencilLoadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
                                   break;
                               case LoadOp::Clear:
                                   stencilLoadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
                                   break;
                               case LoadOp::DontCare:
                                   stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
                                   break;
                           }

                           VkAttachmentStoreOp storeOp = VK_ATTACHMENT_STORE_OP_STORE;

                           if (x.storeOp != StoreOp::Store)
                           {
                               storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
                           }

                           VkAttachmentStoreOp stencilStoreOp = VK_ATTACHMENT_STORE_OP_STORE;

                           if (x.stencilStoreOp != StoreOp::Store)
                           {
                               stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
                           }

                           VkImageLayout initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

                           switch (x.initialLayout)
                           {
                               case ImageLayout::Undefined:
                                   initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
                                   break;
                               case ImageLayout::Optimal:
                                   initialLayout = VK_IMAGE_LAYOUT_GENERAL;
                                   break;
                               case ImageLayout::Present:
                                   initialLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
                                   break;
                           }

                           VkImageLayout finalLayout = VK_IMAGE_LAYOUT_UNDEFINED;

                           switch (x.finalLayout)
                           {
                               case ImageLayout::Undefined:
                                   finalLayout = VK_IMAGE_LAYOUT_UNDEFINED;
                                   break;
                               case ImageLayout::Optimal:
                                   finalLayout = VK_IMAGE_LAYOUT_GENERAL;
                                   break;
                               case ImageLayout::Present:
                                   finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
                                   break;
                           }

                           VkAttachmentDescription attachmentDescription{};
                           attachmentDescription.format = Vulkan::Utilities::Map(x.texelFormat);
                           attachmentDescription.samples = VK_SAMPLE_COUNT_1_BIT;
                           attachmentDescription.loadOp = loadOp;
                           attachmentDescription.storeOp = storeOp;
                           attachmentDescription.stencilLoadOp = stencilLoadOp;
                           attachmentDescription.stencilStoreOp = stencilStoreOp;
                           attachmentDescription.initialLayout = initialLayout;
                           attachmentDescription.finalLayout = finalLayout;

                           return attachmentDescription;
                       });

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
        dependency.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
        dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_COLOR_ATTACHMENT_READ_BIT;

        VkRenderPassCreateInfo renderPassCreateInfo{};
        renderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        renderPassCreateInfo.attachmentCount = static_cast<uint32_t>(attachmentDescriptions.size());
        renderPassCreateInfo.pAttachments = attachmentDescriptions.data();
        renderPassCreateInfo.subpassCount = 1;
        renderPassCreateInfo.pSubpasses = &subpass;
        renderPassCreateInfo.pDependencies = &dependency;
        renderPassCreateInfo.dependencyCount = 1;

        VkRenderPass returnRenderPass = VK_NULL_HANDLE;
        VkResult renderPassResult = vkCreateRenderPass(device, &renderPassCreateInfo, nullptr, &returnRenderPass);

        if (renderPassResult != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to create the VkRenderPass.", renderPassResult);
        }

        return returnRenderPass;
    }

    VulkanGraphicsRenderPass::GraphicsRenderPass(std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> device,
                                                 const GraphicsRenderPassDescription& description)
        : _device(std::move(device)), _vulkanRenderPass(CreateRenderPass(description, _device->GetVulkanDevice()))
    {
    }

    VulkanGraphicsRenderPass::~GraphicsRenderPass() noexcept
    {
        vkDestroyRenderPass(GetDevice()->GetVulkanDevice(), _vulkanRenderPass, nullptr);
    }

    std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> VulkanGraphicsRenderPass::GetDevice() const
    {
        return _device;
    }

    VkRenderPass VulkanGraphicsRenderPass::GetVulkanRenderPass() const noexcept
    {
        return _vulkanRenderPass;
    }
}
