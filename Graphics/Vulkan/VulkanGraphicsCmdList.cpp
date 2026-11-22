// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include "NovelRT/Exceptions/NotSupportedException.hpp"
#include <NovelRT/Exceptions/InvalidOperationException.hpp>

#include <NovelRT/Graphics/Vulkan/Utilities/ImageLayout.hpp>
#include <NovelRT/Graphics/Vulkan/Utilities/MemoryAccessMode.hpp>
#include <NovelRT/Graphics/Vulkan/Utilities/PipelineVisibility.hpp>
#include <NovelRT/Graphics/Vulkan/Utilities/ShaderProgramVisibility.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsBuffer.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsCmdList.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsContext.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDescriptorSet.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsPipeline.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsPipelineSignature.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsRenderPass.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsTexture.hpp>

#include <NovelRT/Graphics/Vulkan/VulkanGraphicsRenderTarget.hpp>
#include <NovelRT/Utilities/Span.hpp>

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

#include <algorithm>
#include <functional>

namespace NovelRT::Graphics
{
    using VulkanGraphicsAdapter = GraphicsAdapter<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsBuffer = GraphicsBuffer<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsCmdList = GraphicsCmdList<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsContext = GraphicsContext<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsDescriptorSet = GraphicsDescriptorSet<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsPipeline = GraphicsPipeline<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsPipelineSignature = GraphicsPipelineSignature<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsRenderPass = GraphicsRenderPass<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsRenderTarget = GraphicsRenderTarget<Vulkan::VulkanGraphicsBackend>;
    template<template<typename> typename TResource>
    using VulkanGraphicsResourceMemoryRegion = GraphicsResourceMemoryRegion<TResource, Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsTexture = GraphicsTexture<Vulkan::VulkanGraphicsBackend>;

    [[nodiscard]] std::pair<VkAccessFlags, VkPipelineStageFlags> GetAccessAndStageMasksForLayout(VkImageLayout layout,
                                                                                                 bool isSource)
    {
        VkAccessFlags accessMask = 0;
        VkPipelineStageFlags stageMask = 0;

        switch (layout)
        {
            case VK_IMAGE_LAYOUT_UNDEFINED:
                accessMask = 0;
                stageMask = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
                break;
            case VK_IMAGE_LAYOUT_GENERAL:
                accessMask = VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_SHADER_WRITE_BIT;
                stageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT;
                break;
            case VK_IMAGE_LAYOUT_PRESENT_SRC_KHR:
                accessMask = isSource ? VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT : 0;
                stageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
                break;
            case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
                accessMask = VK_ACCESS_TRANSFER_READ_BIT;
                stageMask = VK_PIPELINE_STAGE_TRANSFER_BIT;
                break;
            case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
                accessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
                stageMask = VK_PIPELINE_STAGE_TRANSFER_BIT;
                break;
            default:
                accessMask = 0;
                stageMask = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
                break;
        }

        return {accessMask, stageMask};
    }

    VulkanGraphicsCmdList::GraphicsCmdList(
        std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> device,
        VkCommandBuffer commandBuffer,
        std::shared_ptr<GraphicsContext<Vulkan::VulkanGraphicsBackend>> owningContext,
        std::optional<SecondaryCmdListInfo<Vulkan::VulkanGraphicsBackend>> secondaryContextData) noexcept
        : _device(std::move(device)),
          _commandBuffer(commandBuffer),
          _owningContext(std::move(owningContext)),
          _secondaryContextData(std::move(secondaryContextData))
    {
        std::span<const std::string> extensions = _device->GetEnabledExtensions();

        _supportsMixedRecording =
            std::ranges::any_of(extensions,
                                [](const std::string& extension)
                                {
                                    return extension == VK_EXT_NESTED_COMMAND_BUFFER_EXTENSION_NAME ||
                                           extension == VK_KHR_MAINTENANCE_7_EXTENSION_NAME;
                                });
    }

    VulkanGraphicsCmdList::~GraphicsCmdList()
    {
        if (_commandBuffer == VK_NULL_HANDLE)
        {
            return;
        }

        vkFreeCommandBuffers(_device->GetVulkanDevice(), _owningContext->GetVulkanCommandPool(), 1, &_commandBuffer);
    }

    std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> VulkanGraphicsCmdList::GetDevice() const noexcept
    {
        return _device;
    }

    VkCommandBuffer VulkanGraphicsCmdList::GetVkCommandBuffer()
    {
        return _commandBuffer;
    }

    void VulkanGraphicsCmdList::Begin()
    {
        if (GetVkCommandBuffer() == VK_NULL_HANDLE)
        {
            _replayData.clear();
            return;
        }

        VkCommandBufferBeginInfo commandBufferBeginInfo{};
        commandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        VkCommandBufferInheritanceInfo inheritanceInfo{};

        if (_secondaryContextData.has_value())
        {
            auto& secondaryContext = _secondaryContextData.value();
            inheritanceInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
            inheritanceInfo.framebuffer = VK_NULL_HANDLE;
            inheritanceInfo.occlusionQueryEnable = VK_FALSE; // TODO: Fix this later probably
            inheritanceInfo.pipelineStatistics = 0;
            inheritanceInfo.queryFlags = 0;
            inheritanceInfo.renderPass = secondaryContext.renderPass->GetVulkanRenderPass();
            inheritanceInfo.subpass = static_cast<uint32_t>(secondaryContext.subpassIndex);

            commandBufferBeginInfo.pInheritanceInfo = &inheritanceInfo;
            commandBufferBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT;
        }

        const VkResult result = vkBeginCommandBuffer(_commandBuffer, &commandBufferBeginInfo);

        if (result != VK_SUCCESS)
        {
            throw Exceptions::InvalidOperationException("Failed to begin VkCommandBuffer.");
        }
    }

    void VulkanGraphicsCmdList::End()
    {
        if (GetVkCommandBuffer() == VK_NULL_HANDLE)
        {
            return;
        }

        const VkResult result = vkEndCommandBuffer(_commandBuffer);

        if (result != VK_SUCCESS)
        {
            throw Exceptions::InvalidOperationException("Failed to end VkCommandBuffer.");
        }
    }

    void VulkanGraphicsCmdList::CmdBeginRenderPass(const std::shared_ptr<VulkanGraphicsRenderPass>& targetPass,
                                                   const std::shared_ptr<VulkanGraphicsRenderTarget>& renderTarget,
                                                   Utilities::Span<const ClearValue> clearValues)
    {
        if (_secondaryContextData.has_value())
        {
            throw Exceptions::InvalidOperationException(
                "Unable to begin a render pass in a secondary VkBuffer. This is not allowed.");
        }

        auto surface = _device->GetSurface();

        VkExtent2D extent2D{};
        extent2D.width = static_cast<uint32_t>(surface->GetWidth());
        extent2D.height = static_cast<uint32_t>(surface->GetHeight());

        VkRect2D renderArea{};
        renderArea.extent = extent2D;

        VkRenderPassBeginInfo renderPassBeginInfo{};

        std::vector<VkClearValue> clearValuesActual(clearValues.size());

        std::ranges::transform(clearValues, clearValuesActual.begin(),
                               [](const ClearValue& data)
                               {
                                   VkClearValue returnStruct{};
                                   auto colour = data.colour;

                                   returnStruct.color.float32[0] = colour.getRScalar();
                                   returnStruct.color.float32[1] = colour.getGScalar();
                                   returnStruct.color.float32[2] = colour.getBScalar();
                                   returnStruct.color.float32[3] = colour.getAScalar();

                                   // the color and depthStencil members are actually a C union. Removing these for now,
                                   // but leaving these here so we don't forget. - Matt J.
                                   // returnStruct.depthStencil.depth = data.depth;
                                   // returnStruct.depthStencil.stencil = data.stencil;

                                   return returnStruct;
                               });

        renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassBeginInfo.renderPass = targetPass->GetVulkanRenderPass();
        renderPassBeginInfo.framebuffer = renderTarget->GetVulkanFramebuffer();
        renderPassBeginInfo.renderArea = renderArea;
        renderPassBeginInfo.clearValueCount = static_cast<uint32_t>(clearValuesActual.size());
        renderPassBeginInfo.pClearValues = clearValuesActual.data();

        vkCmdBeginRenderPass(_commandBuffer, &renderPassBeginInfo,
                             _supportsMixedRecording ? VK_SUBPASS_CONTENTS_INLINE_AND_SECONDARY_COMMAND_BUFFERS_KHR
                                                     : VK_SUBPASS_CONTENTS_INLINE);
    }

    void VulkanGraphicsCmdList::CmdEndRenderPass()
    {
        if (_secondaryContextData.has_value())
        {
            throw Exceptions::InvalidOperationException(
                "Unable to end a render pass in a secondary VkBuffer. This is not allowed.");
        }

        vkCmdEndRenderPass(_commandBuffer);
    }

    void VulkanGraphicsCmdList::CmdBindDescriptorSet(const std::shared_ptr<VulkanGraphicsDescriptorSet>& set)
    {
        std::array<std::reference_wrapper<const std::shared_ptr<NovelRT::Graphics::VulkanGraphicsDescriptorSet>>, 1>
            descriptorData{std::cref(set)};

        CmdBindDescriptorSets(descriptorData);
    }

    void VulkanGraphicsCmdList::CmdBindDescriptorSets(
        NovelRT::Utilities::Span<std::reference_wrapper<const std::shared_ptr<VulkanGraphicsDescriptorSet>>> sets)
    {
        for (const auto& wrappedSet : sets)
        {
            auto commandFrame = [set = wrappedSet.get()](VkCommandBuffer cmdBuffer)
            {
                VkDescriptorSet handle = set->GetVulkanDescriptorSet();
                auto pipeline = set->GetPipeline();
                auto signature = pipeline->GetSignature();

                vkCmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
                                        signature->GetVulkanPipelineLayout(), 0, 1, &handle, 0, nullptr);
            };

            if (_commandBuffer == VK_NULL_HANDLE)
            {
                _replayData.emplace_back(std::move(commandFrame));
            }
            else
            {
                commandFrame(_commandBuffer);
            }
        }
    }

    void VulkanGraphicsCmdList::CmdBindVertexBuffers(
        uint32_t firstBinding,
        uint32_t bindingCount,
        NovelRT::Utilities::Span<std::reference_wrapper<const std::shared_ptr<VulkanGraphicsBuffer>>> buffers,
        NovelRT::Utilities::Span<const size_t> offsets)
    {
        std::vector<VkBuffer> bufferArgs(buffers.size());
        std::vector<VkDeviceSize> offsetArgs(offsets.size());

        std::ranges::transform(buffers, bufferArgs.begin(), [](const auto& x) { return x.get()->GetVulkanBuffer(); });
        std::ranges::transform(offsets, offsetArgs.begin(), [](auto x) { return static_cast<VkDeviceSize>(x); });

        if (_commandBuffer == VK_NULL_HANDLE)
        {
            _replayData.emplace_back(
                [bufferArgs, offsetArgs, firstBinding, bindingCount](VkCommandBuffer cmdBuffer)
                {
                    vkCmdBindVertexBuffers(cmdBuffer, firstBinding, bindingCount, bufferArgs.data(), offsetArgs.data());
                });
        }
        else
        {
            vkCmdBindVertexBuffers(_commandBuffer, firstBinding, bindingCount, bufferArgs.data(), offsetArgs.data());
        }
    }

    void VulkanGraphicsCmdList::CmdBindIndexBuffer(
        const std::shared_ptr<VulkanGraphicsResourceMemoryRegion<GraphicsBuffer>>& buffer,
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

        auto bufferResource = buffer->GetOwningResource();

        if (_commandBuffer == VK_NULL_HANDLE)
        {
            _replayData.emplace_back(
                [bufferResource, buffer, type](VkCommandBuffer cmdBuffer)
                { vkCmdBindIndexBuffer(cmdBuffer, bufferResource->GetVulkanBuffer(), buffer->GetOffset(), type); });
        }
        else
        {
            vkCmdBindIndexBuffer(_commandBuffer, bufferResource->GetVulkanBuffer(), buffer->GetOffset(), type);
        }
    }

    void VulkanGraphicsCmdList::CmdCopy(
        const std::shared_ptr<VulkanGraphicsResourceMemoryRegion<GraphicsBuffer>>& destination,
        const std::shared_ptr<VulkanGraphicsResourceMemoryRegion<GraphicsBuffer>>& source)
    {
        VkBufferCopy vulkanBufferCopy{};
        vulkanBufferCopy.srcOffset = source->GetOffset();
        vulkanBufferCopy.dstOffset = destination->GetOffset();
        vulkanBufferCopy.size = std::min(destination->GetSize(), source->GetSize());

        auto sourceResource = source->GetOwningResource();
        auto destinationResource = destination->GetOwningResource();

        if (_commandBuffer == VK_NULL_HANDLE)
        {
            _replayData.emplace_back(
                [sourceResource, destinationResource, vulkanBufferCopy](VkCommandBuffer cmdBuffer)
                {
                    vkCmdCopyBuffer(cmdBuffer, sourceResource->GetVulkanBuffer(),
                                    destinationResource->GetVulkanBuffer(), 1, &vulkanBufferCopy);
                });
        }
        else
        {
            vkCmdCopyBuffer(_commandBuffer, sourceResource->GetVulkanBuffer(), destinationResource->GetVulkanBuffer(),
                            1, &vulkanBufferCopy);
        }
    }

    void VulkanGraphicsCmdList::CmdCopy(
        const std::shared_ptr<VulkanGraphicsTexture>& destination,
        const std::shared_ptr<VulkanGraphicsResourceMemoryRegion<GraphicsBuffer>>& source)
    {
        if (destination->GetSize() < source->GetSize())
        {
            throw Exceptions::InvalidOperationException(
                "The destination texture is smaller than the provided source data. This is not allowed.");
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

        if (_commandBuffer == VK_NULL_HANDLE)
        {
            _replayData.emplace_back(
                [source, vulkanImage, vulkanBufferImageCopy](VkCommandBuffer cmdBuffer)
                {
                    vkCmdCopyBufferToImage(cmdBuffer, source->GetOwningResource()->GetVulkanBuffer(), vulkanImage,
                                           VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &vulkanBufferImageCopy);
                });
        }
        else
        {
            vkCmdCopyBufferToImage(_commandBuffer, source->GetOwningResource()->GetVulkanBuffer(), vulkanImage,
                                   VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &vulkanBufferImageCopy);
        }
    }

    void VulkanGraphicsCmdList::CmdDrawIndexed(uint32_t indexCount,
                                               uint32_t instanceCount,
                                               uint32_t firstIndex,
                                               size_t vertexOffset,
                                               uint32_t firstInstance)
    {
        if (_commandBuffer == VK_NULL_HANDLE)
        {
            _replayData.emplace_back(
                [indexCount, instanceCount, firstIndex, vertexOffset, firstInstance](VkCommandBuffer cmdBuffer)
                {
                    vkCmdDrawIndexed(cmdBuffer, indexCount, instanceCount, firstIndex,
                                     static_cast<int32_t>(vertexOffset), firstInstance);
                });
        }
        else
        {
            vkCmdDrawIndexed(_commandBuffer, indexCount, instanceCount, firstIndex, static_cast<int32_t>(vertexOffset),
                             firstInstance);
        }
    }

    void VulkanGraphicsCmdList::CmdDraw(uint32_t vertexCount,
                                        uint32_t instanceCount,
                                        uint32_t firstVertex,
                                        uint32_t firstInstance)
    {
        if (_commandBuffer == VK_NULL_HANDLE)
        {
            _replayData.emplace_back([vertexCount, instanceCount, firstVertex, firstInstance](VkCommandBuffer cmdBuffer)
                                     { vkCmdDraw(cmdBuffer, vertexCount, instanceCount, firstVertex, firstInstance); });
        }
        else
        {
            vkCmdDraw(_commandBuffer, vertexCount, instanceCount, firstVertex, firstInstance);
        }
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

        if (_commandBuffer == VK_NULL_HANDLE)
        {
            _replayData.emplace_back([newScissor](VkCommandBuffer cmdBuffer)
                                     { vkCmdSetScissor(cmdBuffer, 0, 1, &newScissor); });
        }
        else
        {
            vkCmdSetScissor(_commandBuffer, 0, 1, &newScissor);
        }
    }

    void VulkanGraphicsCmdList::CmdSetViewport(ViewportInfo viewportInfo)
    {
        VkViewport viewport{};
        viewport.x = viewportInfo.x;
        viewport.y = viewportInfo.y;
        viewport.width = viewportInfo.width;
        viewport.height = viewportInfo.height;
        viewport.minDepth = viewport.minDepth;
        viewport.maxDepth = viewport.maxDepth;

        if (_commandBuffer == VK_NULL_HANDLE)
        {
            _replayData.emplace_back([viewport](VkCommandBuffer cmdBuffer)
                                     { vkCmdSetViewport(cmdBuffer, 0, 1, &viewport); });
        }
        else
        {
            vkCmdSetViewport(_commandBuffer, 0, 1, &viewport);
        }
    }

    void VulkanGraphicsCmdList::CmdBeginTexturePipelineBarrierLegacyVersion(
        const std::shared_ptr<VulkanGraphicsTexture>& texture)
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

        if (_commandBuffer == VK_NULL_HANDLE)
        {
            _replayData.emplace_back(
                [vulkanImageMemoryBarrier](VkCommandBuffer cmdBuffer)
                {
                    vkCmdPipelineBarrier(cmdBuffer, VK_PIPELINE_STAGE_HOST_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0,
                                         nullptr, 0, nullptr, 1, &vulkanImageMemoryBarrier);
                });
        }
        else
        {
            vkCmdPipelineBarrier(_commandBuffer, VK_PIPELINE_STAGE_HOST_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0,
                                 nullptr, 0, nullptr, 1, &vulkanImageMemoryBarrier);
        }
    }

    void VulkanGraphicsCmdList::CmdEndTexturePipelineBarrierLegacyVersion(
        const std::shared_ptr<VulkanGraphicsTexture>& texture)
    {
        VkImageSubresourceRange subresourceRange{};
        subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        subresourceRange.levelCount = 1;
        subresourceRange.layerCount = 1;

        VkImageMemoryBarrier vulkanImageMemoryBarrier{};
        vulkanImageMemoryBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        vulkanImageMemoryBarrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        vulkanImageMemoryBarrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
        vulkanImageMemoryBarrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
        vulkanImageMemoryBarrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        vulkanImageMemoryBarrier.subresourceRange = subresourceRange;
        vulkanImageMemoryBarrier.image = texture->GetVulkanImage();

        if (_commandBuffer == VK_NULL_HANDLE)
        {
            _replayData.emplace_back(
                [vulkanImageMemoryBarrier](VkCommandBuffer cmdBuffer)
                {
                    vkCmdPipelineBarrier(cmdBuffer, VK_PIPELINE_STAGE_TRANSFER_BIT,
                                         VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0, 0, nullptr, 0, nullptr, 1,
                                         &vulkanImageMemoryBarrier);
                });
        }
        else
        {
            vkCmdPipelineBarrier(_commandBuffer, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
                                 0, 0, nullptr, 0, nullptr, 1, &vulkanImageMemoryBarrier);
        }
    }

    void VulkanGraphicsCmdList::CmdBindPipeline(const std::shared_ptr<VulkanGraphicsPipeline>& pipeline)
    {
        if (_commandBuffer == VK_NULL_HANDLE)
        {
            _replayData.emplace_back(
                [vulkanPipeline = pipeline->GetVulkanPipeline()](VkCommandBuffer cmdBuffer)
                { vkCmdBindPipeline(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, vulkanPipeline); });
        }
        else
        {
            vkCmdBindPipeline(_commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline->GetVulkanPipeline());
        }
    }

    void VulkanGraphicsCmdList::CmdPushConstants(
        const std::shared_ptr<VulkanGraphicsPipelineSignature>& pipelineSignature,
        ShaderProgramVisibility visibility,
        size_t offset,
        NovelRT::Utilities::Span<uint8_t> values)
    {
        if (_commandBuffer == VK_NULL_HANDLE)
        {
            std::vector<uint8_t> localValuesCopy(values.begin(), values.end());

            _replayData.emplace_back(
                [localValuesCopy, visibility, offset,
                 vulkanPipelineLayout = pipelineSignature->GetVulkanPipelineLayout()](VkCommandBuffer cmdBuffer)
                {
                    vkCmdPushConstants(cmdBuffer, vulkanPipelineLayout,
                                       Vulkan::Utilities::GetVulkanShaderStageFlags(visibility),
                                       static_cast<uint32_t>(offset), static_cast<uint32_t>(localValuesCopy.size()),
                                       localValuesCopy.data());
                });
        }
        else
        {

            vkCmdPushConstants(_commandBuffer, pipelineSignature->GetVulkanPipelineLayout(),
                               Vulkan::Utilities::GetVulkanShaderStageFlags(visibility), static_cast<uint32_t>(offset),
                               static_cast<uint32_t>(values.size()), values.data());
        }
    }

    void VulkanGraphicsCmdList::CmdPipelineBufferBarrier(const std::shared_ptr<VulkanGraphicsBuffer>& buffer,
                                                         GraphicsMemoryAccessMode sourceAccessFlag,
                                                         GraphicsMemoryAccessMode destinationAccessFlag,
                                                         GraphicsPipelineVisibility sourceStageFlag,
                                                         GraphicsPipelineVisibility destinationStageFlag)
    {
        VkBufferMemoryBarrier barrierInfo{.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER,
                                          .pNext = nullptr,
                                          .srcAccessMask = Vulkan::Utilities::GetVulkanAccessFlags(sourceAccessFlag),
                                          .dstAccessMask =
                                              Vulkan::Utilities::GetVulkanAccessFlags(destinationAccessFlag),
                                          .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
                                          .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
                                          .buffer = buffer->GetVulkanBuffer(),
                                          .offset = 0,
                                          .size = VK_WHOLE_SIZE};

        if (_commandBuffer == VK_NULL_HANDLE)
        {
            _replayData.emplace_back(
                [sourceStageFlag, destinationStageFlag, barrierInfo](VkCommandBuffer cmdBuffer)
                {
                    vkCmdPipelineBarrier(cmdBuffer, Vulkan::Utilities::GetVulkanPipelineStageFlags(sourceStageFlag),
                                         Vulkan::Utilities::GetVulkanPipelineStageFlags(destinationStageFlag), 0, 0,
                                         nullptr, 1, &barrierInfo, 0, nullptr);
                });
        }
        else
        {
            vkCmdPipelineBarrier(_commandBuffer, Vulkan::Utilities::GetVulkanPipelineStageFlags(sourceStageFlag),
                                 Vulkan::Utilities::GetVulkanPipelineStageFlags(destinationStageFlag), 0, 0, nullptr, 1,
                                 &barrierInfo, 0, nullptr);
        }
    }

    void VulkanGraphicsCmdList::CmdExecuteCommands(
        const std::shared_ptr<GraphicsCmdList<Vulkan::VulkanGraphicsBackend>>& cmdList)
    {
        if (_secondaryContextData.has_value())
        {
            throw Exceptions::NotSupportedException(
                "Attempted to invoke CmdExecuteCommands on a secondary VkCommandBuffer. This is not allowed by "
                "default, and requires the nestedCommandBufferRendering extension, which NovelRT currently does not "
                "support.");
        }

        VkCommandBuffer childBuffer = cmdList->GetVkCommandBuffer();

        if (childBuffer == VK_NULL_HANDLE)
        {
            // NOTE: Not sure we want to rely on same-time-friend behaviour (I don't know what the official name is) for
            // this. It compiles though. Leaving it for the code review. - Matt J.
            for (const auto& commandFrame : cmdList->_replayData)
            {
                commandFrame(_commandBuffer);
            }

            return;
        }

        vkCmdExecuteCommands(_commandBuffer, 1, &childBuffer);
    }

    void VulkanGraphicsCmdList::CmdTransitionSwapchainImageTo(
        const std::shared_ptr<GraphicsSwapchainImage<Vulkan::VulkanGraphicsBackend>>& swapchainImage,
        ImageLayout oldLayout,
        ImageLayout newLayout)
    {
        VkImageLayout vkOldLayout = Vulkan::GetVulkanImageLayout(oldLayout);
        VkImageLayout vkNewLayout = Vulkan::GetVulkanImageLayout(newLayout);

        VkImageSubresourceRange subresourceRange{};
        subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        subresourceRange.levelCount = 1;
        subresourceRange.layerCount = 1;

        const auto [srcAccessMask, srcStageMask] = GetAccessAndStageMasksForLayout(vkOldLayout, true);
        const auto [dstAccessMask, dstStageMask] = GetAccessAndStageMasksForLayout(vkNewLayout, false);

        VkImageMemoryBarrier barrier{};
        barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        barrier.srcAccessMask = srcAccessMask;
        barrier.dstAccessMask = dstAccessMask;
        barrier.oldLayout = vkOldLayout;
        barrier.newLayout = vkNewLayout;
        barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.image = swapchainImage->GetVulkanImage();
        barrier.subresourceRange = subresourceRange;

        if (_commandBuffer == VK_NULL_HANDLE)
        {
            _replayData.emplace_back(
                [srcStageMask, dstStageMask, barrier](VkCommandBuffer cmdBuffer)
                {
                    vkCmdPipelineBarrier(cmdBuffer, srcStageMask, dstStageMask, 0, 0, nullptr, 0, nullptr, 1, &barrier);
                });
        }
        else
        {
            vkCmdPipelineBarrier(_commandBuffer, srcStageMask, dstStageMask, 0, 0, nullptr, 0, nullptr, 1, &barrier);
        }
    }

    void VulkanGraphicsCmdList::CmdClearColourSwapchainImage(
        const std::shared_ptr<GraphicsSwapchainImage<Vulkan::VulkanGraphicsBackend>>& swapchainImage,
        ClearValue clearData)
    {
        // TODO: This assumes layout is in transfer optimal. Is this correct? - Matt J.
        VkClearColorValue colourValue{};
        colourValue.float32[0] = clearData.colour.getRScalar();
        colourValue.float32[1] = clearData.colour.getGScalar();
        colourValue.float32[2] = clearData.colour.getBScalar();
        colourValue.float32[3] = clearData.colour.getAScalar();

        VkClearDepthStencilValue depthValue{};

        depthValue.depth = clearData.depth;
        depthValue.stencil = clearData.stencil;

        VkImageSubresourceRange subresourceColourRange{};
        subresourceColourRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        subresourceColourRange.levelCount = 1;
        subresourceColourRange.layerCount = 1;

        if (_commandBuffer == VK_NULL_HANDLE)
        {
            _replayData.emplace_back(
                [colourValue, subresourceColourRange,
                 vulkanImage = swapchainImage->GetVulkanImage()](VkCommandBuffer cmdBuffer)
                {
                    vkCmdClearColorImage(cmdBuffer, vulkanImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, &colourValue, 1,
                                         &subresourceColourRange);
                });
        }
        else
        {
            vkCmdClearColorImage(_commandBuffer, swapchainImage->GetVulkanImage(), VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                                 &colourValue, 1, &subresourceColourRange);
        }
    }
}
