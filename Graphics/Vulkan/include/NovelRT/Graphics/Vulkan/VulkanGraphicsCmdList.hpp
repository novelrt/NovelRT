#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsCmdList.hpp>

#include <NovelRT/Utilities/Span.hpp>

namespace NovelRT::Graphics::Vulkan
{
    struct VulkanGraphicsBackend;
}

namespace NovelRT::Graphics
{
    template <>
    class GraphicsCmdList<Vulkan::VulkanGraphicsBackend> : std::enable_shared_from_this<GraphicsCmdList<Vulkan::VulkanGraphicsBackend>>
    {
    private:
        std::shared_ptr<GraphicsContext<Vulkan::VulkanGraphicsBackend>> _context;
        VkCommandBuffer _commandBuffer;

    public:
        GraphicsCmdList(
            std::shared_ptr<GraphicsContext<Vulkan::VulkanGraphicsBackend>> context,
            VkCommandBuffer commandBuffer) noexcept;

        ~GraphicsCmdList() = default;

        [[nodiscard]] std::shared_ptr<GraphicsContext<Vulkan::VulkanGraphicsBackend>> GetContext() const noexcept;

        void CmdBeginRenderPass(const GraphicsRenderPass<Vulkan::VulkanGraphicsBackend>* targetPass,
            Utilities::Span<const ClearValue> clearValues);

        void CmdEndRenderPass();

        void CmdBindDescriptorSets(
        NovelRT::Utilities::Span<const GraphicsDescriptorSet<Vulkan::VulkanGraphicsBackend>*> sets);

        void CmdBindVertexBuffers(
        uint32_t firstBinding,
        uint32_t bindingCount,
        NovelRT::Utilities::Span<const GraphicsBuffer<Vulkan::VulkanGraphicsBackend>*> buffers,
        NovelRT::Utilities::Span<const size_t> offsets);

        void CmdBindIndexBuffer(const GraphicsResourceMemoryRegion<GraphicsBuffer, Vulkan::VulkanGraphicsBackend>* buffer,
                    IndexType indexType);

        void CmdCopy(const GraphicsResourceMemoryRegion<GraphicsBuffer, Vulkan::VulkanGraphicsBackend>* destination,
        const GraphicsResourceMemoryRegion<GraphicsBuffer, Vulkan::VulkanGraphicsBackend>* source);

        void CmdCopy(const GraphicsTexture<Vulkan::VulkanGraphicsBackend>* destination,
        const GraphicsResourceMemoryRegion<GraphicsBuffer, Vulkan::VulkanGraphicsBackend>* source);

        void CmdDrawIndexed(uint32_t indexCount,
                uint32_t instanceCount,
                uint32_t firstIndex,
                size_t vertexOffset,
                uint32_t firstInstance);

        void CmdDraw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance);

        void CmdSetScissor(Maths::GeoVector2F offset, Maths::GeoVector2F extent);

        void CmdSetViewport(ViewportInfo viewportInfo);

        void CmdBeginTexturePipelineBarrierLegacyVersion(const GraphicsTexture<Vulkan::VulkanGraphicsBackend>* texture);
        void CmdEndTexturePipelineBarrierLegacyVersion(const GraphicsTexture<Vulkan::VulkanGraphicsBackend>* texture);

        void CmdBindPipeline(const GraphicsPipeline<Vulkan::VulkanGraphicsBackend>* pipeline);

        void CmdPushConstants(const GraphicsPipelineSignature<Vulkan::VulkanGraphicsBackend>* pipelineSignature, ShaderProgramVisibility visibility, size_t offset, NovelRT::Utilities::Span<uint8_t> values);

        void CmdPipelineBufferBarrier(const GraphicsBuffer<Vulkan::VulkanGraphicsBackend>* buffer,
            GraphicsMemoryAccessMode sourceAccessFlag,
            GraphicsMemoryAccessMode destinationAccessFlag,
            GraphicsPipelineVisibility sourceStageFlag,
            GraphicsPipelineVisibility destinationStageFlag);
    };
}
