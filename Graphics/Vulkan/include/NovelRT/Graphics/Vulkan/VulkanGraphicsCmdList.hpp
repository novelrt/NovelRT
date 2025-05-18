#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsCmdList.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsResource.hpp>
#include<NovelRT/Utilities/Misc.h>

namespace NovelRT::Graphics::Vulkan
{
    class VulkanGraphicsRenderPass;
    class VulkanGraphicsContext;
    class VulkanGraphicsDescriptorSet;
    class VulkanGraphicsBuffer;
    class VulkanGraphicsTexture;
    class VulkanGraphicsPipeline;
    class VulkanGraphicsPipelineSignature;

    class VulkanGraphicsCmdList final
    {
    private:
        std::shared_ptr<VulkanGraphicsContext> _context;
        VkCommandBuffer _commandBuffer;

    public:
        explicit VulkanGraphicsCmdList(std::shared_ptr<VulkanGraphicsContext> context, VkCommandBuffer commandBuffer) noexcept;

        ~VulkanGraphicsCmdList() = default;

        [[nodiscard]] std::shared_ptr<VulkanGraphicsContext> GetContext() const noexcept;

        void CmdBeginRenderPass(std::shared_ptr<VulkanGraphicsRenderPass> targetPass, NovelRT::Utilities::Misc::Span<const ClearValue> clearValues);

        void CmdEndRenderPass();

        void CmdBindDescriptorSets(
            NovelRT::Utilities::Misc::Span<const std::shared_ptr<VulkanGraphicsDescriptorSet>> sets);

        void CmdBindVertexBuffers(uint32_t firstBinding,
                                  uint32_t bindingCount,
                                  NovelRT::Utilities::Misc::Span<const std::shared_ptr<VulkanGraphicsBuffer>> buffers,
                                  NovelRT::Utilities::Misc::Span<const size_t> offsets);

        void CmdBindIndexBuffer(std::shared_ptr<VulkanGraphicsResourceMemoryRegion<VulkanGraphicsBuffer>> buffer, IndexType indexType);

        void CmdCopy(std::shared_ptr<VulkanGraphicsResourceMemoryRegion<VulkanGraphicsBuffer>> destination, std::shared_ptr<VulkanGraphicsResourceMemoryRegion<VulkanGraphicsBuffer>> source);

        void CmdCopy(std::shared_ptr<VulkanGraphicsTexture> destination, std::shared_ptr<VulkanGraphicsResourceMemoryRegion<VulkanGraphicsBuffer>> source);

        void CmdDrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, size_t vertexOffset, uint32_t firstInstance);

        void CmdDraw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance);

        void CmdSetScissor(Maths::GeoVector2F offset, Maths::GeoVector2F extent);

        void CmdSetViewport(ViewportInfo viewportInfo);

        void CmdBeginTexturePipelineBarrierLegacyVersion(std::shared_ptr<VulkanGraphicsTexture> texture);

        void CmdEndTexturePipelineBarrierLegacyVersion(std::shared_ptr<VulkanGraphicsTexture> texture);

        void CmdBindPipeline(std::shared_ptr<VulkanGraphicsPipeline> pipeline);
        
        void CmdPushConstants(std::shared_ptr<VulkanGraphicsPipelineSignature> pipelineSignature, ShaderProgramVisibility visibility, size_t offset, NovelRT::Utilities::Misc::Span<uint8_t> values);
    };
}
