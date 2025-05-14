// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/Vulkan/VulkanGraphicsBuffer.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsCmdList.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsContext.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDescriptorSet.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsPipeline.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsRenderPass.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsTexture.hpp>

namespace NovelRT::Graphics::Vulkan
{
    VulkanGraphicsCmdList::VulkanGraphicsCmdList(std::shared_ptr<VulkanGraphicsContext> context) noexcept
        : _context(context)
    {
    }

    std::shared_ptr<VulkanGraphicsContext> VulkanGraphicsCmdList::GetContext() const noexcept
    {
        return _context;
    }

    void VulkanGraphicsCmdList::CmdBeginRenderPass(std::shared_ptr<VulkanGraphicsRenderPass> targetPass,
                                                   Utilities::Misc::Span<const ClearValue> clearValues)
    {
        auto device = _context->GetDevice();
        auto surface = device->GetSurface();

        VkExtent2D extent2D{};
        extent2D.width = static_cast<uint32_t>(surface->GetWidth());
        extent2D.height = static_cast<uint32_t>(surface->GetHeight());

        VkRect2D renderArea{};
        renderArea.extent = extent2D;

        std::vector<VkClearValue> clearValuesActual(clearValues.size());

        std::transform(clearValues.begin(), clearValues.end(), clearValuesActual.begin(),
                       [](const ClearValue& data) {
                        VkClearValue returnStruct{};
                        auto colour = data.colour;

                        returnStruct.color.float32[0] = colour.getRScalar();
                        returnStruct.color.float32[1] = colour.getGScalar();
                        returnStruct.color.float32[2] = colour.getBScalar();
                        returnStruct.color.float32[3] = colour.getAScalar();

                        returnStruct.depthStencil.depth = data.depth;
                        returnStruct.depthStencil.stencil = data.stencil;

                        return returnStruct;
                       });

        // TODO: clean this up
        VkRenderPassBeginInfo renderPassBeginInfo{};
        renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassBeginInfo.renderPass = targetPass->GetVulkanRenderPass();
        renderPassBeginInfo.framebuffer = _context->GetVulkanFramebuffer();
        renderPassBeginInfo.renderArea = renderArea;
        renderPassBeginInfo.clearValueCount = static_cast<uint32_t>(clearValuesActual.size());
        renderPassBeginInfo.pClearValues = clearValuesActual.data();

        vkCmdBeginRenderPass(_commandBuffer, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
    }

    void VulkanGraphicsCmdList::CmdEndRenderPass()
    {
        vkCmdEndRenderPass(_commandBuffer);
    }

    void VulkanGraphicsCmdList::CmdBindDescriptorSets(
        NovelRT::Utilities::Misc::Span<const std::shared_ptr<VulkanGraphicsDescriptorSet>> sets)
    {
        for (auto&& set : sets)
        {
            vkCmdBindDescriptorSets(_commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
                                    set->GetPipeline()->GetSignature()->GetVulkanPipelineLayout(), 0, 1,
                                    set->GetVulkanDescriptorSet(), 0, nullptr);
        }
    }

    void VulkanGraphicsCmdList::CmdBindVertexBuffers(
        uint32_t firstBinding,
        uint32_t bindingCount,
        NovelRT::Utilities::Misc::Span<const std::shared_ptr<VulkanGraphicsBuffer>> buffers,
        NovelRT::Utilities::Misc::Span<const size_t> offsets)
    {
        std::vector<VkBuffer> bufferArgs(buffers.size());
        std::vector<VkDeviceSize> offsetArgs(offsets.size());

        std::transform(buffers.begin(), buffers.end(), bufferArgs.begin(), [](auto x) { return x->GetVulkanBuffer(); });
        std::transform(offsets.begin(), offsets.end(), offsetArgs.begin(),
                       [](auto x) { return static_cast<VkDeviceSize>(x); });

        vkCmdBindVertexBuffers(_commandBuffer, firstBinding, bindingCount, bufferArgs.data(), offsetArgs.data());
    }

    void VulkanGraphicsCmdList::CmdBindIndexBuffer(
        std::shared_ptr<VulkanGraphicsResourceMemoryRegion<VulkanGraphicsBuffer>> buffer,
        IndexType indexType)
    {
        VkIndexType type = VK_INDEX_TYPE_NONE_KHR;

        switch (indexType)
        {
            case IndexType::UInt16:
                type = VK_INDEX_TYPE_UINT16;
                break;
            case IndexType::UInt32:
                type = VK_INDEX_TYPE_UINT32;
                break;
            case IndexType::None:
            default:
                throw Exceptions::InvalidOperationException(
                    "Attempted to bind an index buffer with index type of none. This is not allowed.");
                break;
        }

        vkCmdBindIndexBuffer(_commandBuffer, buffer->GetOwningResource()->GetVulkanBuffer(),
                             buffer->GetOffset(), type);
    }

    void VulkanGraphicsCmdList::CmdCopy(std::shared_ptr<VulkanGraphicsResourceMemoryRegion<VulkanGraphicsBuffer>> destination, std::shared_ptr<VulkanGraphicsResourceMemoryRegion<VulkanGraphicsBuffer>> source)
    {
        VkBufferCopy vulkanBufferCopy{};
        vulkanBufferCopy.srcOffset = source->GetOffset();
        vulkanBufferCopy.dstOffset = destination->GetOffset();
        vulkanBufferCopy.size = std::min(destination->GetSize(), source->GetSize());

        vkCmdCopyBuffer(_commandBuffer, source->GetOwningResource()->GetVulkanBuffer(), destination->GetOwningResource()->GetVulkanBuffer(), 1, &vulkanBufferCopy);
    }

    void VulkanGraphicsCmdList::CmdCopy(std::shared_ptr<VulkanGraphicsTexture> destination, std::shared_ptr<VulkanGraphicsResourceMemoryRegion<VulkanGraphicsBuffer>> source)
    {
        if (destination->GetSize() > source->GetSize())
        {
            throw Exceptions::InvalidOperationException("The destination texture is larger than the provided source data. This is not allowed.");
        }

        VkImage vulkanImage = destination->GetVulkanImage();

        VkImageSubresourceLayers imageSubresourceLayers{};
        imageSubresourceLayers.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        imageSubresourceLayers.layerCount = 1;

        VkExtent3D imageExtent{};
        imageExtent.width = destination->GetWidth();
        imageExtent.height = destination->GetHeight();
        imageExtent.depth = destination->GetDepth();

        VkBufferImageCopy vulkanBufferImageCopy{};
        vulkanBufferImageCopy.imageSubresource = imageSubresourceLayers;
        vulkanBufferImageCopy.imageExtent = imageExtent;
        vulkanBufferImageCopy.bufferOffset = source->GetOffset();

        vkCmdCopyBufferToImage(_commandBuffer, source->GetOwningResource()->GetVulkanBuffer(), vulkanImage,
                               VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &vulkanBufferImageCopy);
    }

    void VulkanGraphicsCmdList::CmdDrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, size_t vertexOffset, uint32_t firstInstance)
    {
        vkCmdDrawIndexed(_commandBuffer, indexCount, instanceCount, firstIndex, static_cast<int32_t>(vertexOffset), firstInstance);
    }

    void VulkanGraphicsCmdList::CmdDraw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance)
    {
        vkCmdDraw(_commandBuffer, vertexCount, instanceCount, firstVertex, firstInstance);
    }

    void VulkanGraphicsCmdList::CmdSetScissor(Maths::GeoVector2F offset, Maths::GeoVector2F extent)
    {
        VkOffset2D offset2D{};
        offset2D.x = static_cast<int32_t>(offset.x);
        offset2D.y = static_cast<int32_t>(offset.y);

        VkExtent2D extent2D{};
        extent2D.width = static_cast<uint32_t>(extent.x);
        extent2D.height = static_cast<uint32_t>(extent.y);

        VkRect2D newScissor{};
        newScissor.extent = extent2D;
        newScissor.offset = offset2D;

        vkCmdSetScissor(_commandBuffer, 0, 1, &newScissor);
    }

    void VulkanGraphicsCmdList::CmdSetViewport(ViewportInfo viewportInfo)
    {
        VkViewport viewport{};
        viewport.x = viewportInfo.x;
        viewport.y = viewportInfo.y;
        viewport.width = viewportInfo.width;
        viewport.height = viewportInfo.height;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;

        vkCmdSetViewport(_commandBuffer, 0, 1, &viewport);
    }

    void VulkanGraphicsCmdList::CmdBeginTexturePipelineBarrierLegacyVersion(std::shared_ptr<VulkanGraphicsTexture> texture)
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
        vulkanImageMemoryBarrier.image = texture->GetVulkanImage();

        vkCmdPipelineBarrier(_commandBuffer, VK_PIPELINE_STAGE_HOST_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0,
                             nullptr, 0, nullptr, 1, &vulkanImageMemoryBarrier);
    }

    void VulkanGraphicsCmdList::CmdEndTexturePipelineBarrierLegacyVersion(std::shared_ptr<VulkanGraphicsTexture> texture)
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
        vulkanImageMemoryBarrier.image = texture->GetVulkanImage();

        vkCmdPipelineBarrier(_commandBuffer, VK_PIPELINE_STAGE_TRANSFER_BIT,
                             VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0, 0, nullptr, 0, nullptr, 1,
                             &vulkanImageMemoryBarrier);
    }
}
