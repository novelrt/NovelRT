#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsCmdList.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsResource.hpp>

#include <NovelRT/Utilities/Span.hpp>

namespace NovelRT::Graphics::Vulkan
{
    class VulkanGraphicsRenderPass;
    class VulkanGraphicsContext;
    class VulkanGraphicsDescriptorSet;
    class VulkanGraphicsBuffer;
    class VulkanGraphicsTexture;
    class VulkanGraphicsPipeline;
    class VulkanGraphicsPipelineSignature;

    class VulkanGraphicsCmdList
    {
    private:
        VulkanGraphicsContext* _context;
        VkCommandBuffer _commandBuffer;

    public:
        explicit VulkanGraphicsCmdList(VulkanGraphicsContext* context, VkCommandBuffer commandBuffer) noexcept;

        ~VulkanGraphicsCmdList() = default;

        [[nodiscard]] VulkanGraphicsContext* GetContext() const noexcept
        {
            return _context;
        }

        void CmdBeginRenderPass(const VulkanGraphicsRenderPass* targetPass, Utilities::Span<const ClearValue> clearValues);

        void CmdEndRenderPass();

        void CmdBindDescriptorSets(NovelRT::Utilities::Span<const VulkanGraphicsDescriptorSet*> sets);

        void CmdBindVertexBuffers(uint32_t firstBinding,
                                  uint32_t bindingCount,
                                  NovelRT::Utilities::Span<const VulkanGraphicsBuffer*> buffers,
                                  NovelRT::Utilities::Span<const size_t> offsets);

        void CmdBindIndexBuffer(const VulkanGraphicsResourceMemoryRegion<VulkanGraphicsBuffer>* buffer, IndexType indexType);

        void CmdCopy(const VulkanGraphicsResourceMemoryRegion<VulkanGraphicsBuffer>* destination, const VulkanGraphicsResourceMemoryRegion<VulkanGraphicsBuffer>* source);

        void CmdCopy(const VulkanGraphicsTexture* destination, const VulkanGraphicsResourceMemoryRegion<VulkanGraphicsBuffer>* source);

        void CmdDrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, size_t vertexOffset, uint32_t firstInstance);

        void CmdDraw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance);

        void CmdSetScissor(Maths::GeoVector2F offset, Maths::GeoVector2F extent);

        void CmdSetViewport(ViewportInfo viewportInfo);

        void CmdBeginTexturePipelineBarrierLegacyVersion(const VulkanGraphicsTexture* texture);

        void CmdEndTexturePipelineBarrierLegacyVersion(const VulkanGraphicsTexture* texture);
        void CmdBindPipeline(const VulkanGraphicsPipeline* pipeline);

        void CmdPushConstants(const VulkanGraphicsPipelineSignature* pipelineSignature, ShaderProgramVisibility visibility, size_t offset, NovelRT::Utilities::Span<uint8_t> values);

        void CmdPipelineBufferBarrier(const VulkanGraphicsBuffer* buffer,
            GraphicsMemoryAccessMode sourceAccessFlag,
            GraphicsMemoryAccessMode destinationAccessFlag,
            GraphicsPipelineVisibility sourceStageFlag,
            GraphicsPipelineVisibility destinationStageFlag);
    };
}
