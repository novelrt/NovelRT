#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsCmdList.hpp>
#include <NovelRT/Graphics/GraphicsContext.hpp>
#include <NovelRT/Graphics/SecondaryCmdListInfo.hpp>
#include <NovelRT/Utilities/Span.hpp>

#include <functional>
#include <memory>
#include <optional>

#include <vulkan/vulkan.h>

namespace NovelRT::Graphics::Vulkan
{
    struct VulkanGraphicsBackend;
}

namespace NovelRT::Graphics
{
    template<>
    class GraphicsCmdList<Vulkan::VulkanGraphicsBackend>
        : public std::enable_shared_from_this<GraphicsCmdList<Vulkan::VulkanGraphicsBackend>>
    {
    private:
        std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> _device;
        VkCommandBuffer _commandBuffer;
        std::shared_ptr<GraphicsContext<Vulkan::VulkanGraphicsBackend>> _owningContext;
        std::optional<SecondaryCmdListInfo<Vulkan::VulkanGraphicsBackend>> _secondaryContextData;

    public:
        GraphicsCmdList(
            std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> device,
            VkCommandBuffer commandBuffer,
            std::shared_ptr<GraphicsContext<Vulkan::VulkanGraphicsBackend>> owningContext,
            std::optional<SecondaryCmdListInfo<Vulkan::VulkanGraphicsBackend>> secondaryContextData) noexcept;

        ~GraphicsCmdList();

        [[nodiscard]] std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> GetDevice() const noexcept;

        [[nodiscard]] VkCommandBuffer GetVkCommandBuffer();

        void Begin();
        void End();

        void CmdBeginRenderPass(
            const std::shared_ptr<GraphicsRenderPass<Vulkan::VulkanGraphicsBackend>>& targetPass,
            const std::shared_ptr<GraphicsRenderTarget<Vulkan::VulkanGraphicsBackend>>& renderTarget,
            Utilities::Span<const ClearValue> clearValues);

        void CmdEndRenderPass();

        
        void CmdBindDescriptorSet(
                const std::shared_ptr<GraphicsDescriptorSet<Vulkan::VulkanGraphicsBackend>>&
                set);

        void CmdBindDescriptorSets(
            NovelRT::Utilities::Span<
                std::reference_wrapper<const std::shared_ptr<GraphicsDescriptorSet<Vulkan::VulkanGraphicsBackend>>>>
                sets);

        void CmdBindVertexBuffers(
            uint32_t firstBinding,
            uint32_t bindingCount,
            NovelRT::Utilities::Span<
                std::reference_wrapper<const std::shared_ptr<GraphicsBuffer<Vulkan::VulkanGraphicsBackend>>>> buffers,
            NovelRT::Utilities::Span<const size_t> offsets);

        void CmdBindIndexBuffer(
            const std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsBuffer, Vulkan::VulkanGraphicsBackend>>& buffer,
            IndexType indexType);

        void CmdCopy(
            const std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsBuffer, Vulkan::VulkanGraphicsBackend>>&
                destination,
            const std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsBuffer, Vulkan::VulkanGraphicsBackend>>& source);

        void CmdCopy(
            const std::shared_ptr<GraphicsTexture<Vulkan::VulkanGraphicsBackend>>& destination,
            const std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsBuffer, Vulkan::VulkanGraphicsBackend>>& source);

        void CmdDrawIndexed(uint32_t indexCount,
                            uint32_t instanceCount,
                            uint32_t firstIndex,
                            size_t vertexOffset,
                            uint32_t firstInstance);

        void CmdDraw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance);

        void CmdSetScissor(Maths::GeoVector2F offset, Maths::GeoVector2F extent);

        void CmdSetViewport(ViewportInfo viewportInfo);

        void CmdBeginTexturePipelineBarrierLegacyVersion(
            const std::shared_ptr<GraphicsTexture<Vulkan::VulkanGraphicsBackend>>& texture);
        void CmdEndTexturePipelineBarrierLegacyVersion(
            const std::shared_ptr<GraphicsTexture<Vulkan::VulkanGraphicsBackend>>& texture);

        void CmdInitialSwapchainImageBarrierLegacyVersion(
            const std::shared_ptr<GraphicsSwapchainImage<Vulkan::VulkanGraphicsBackend>>& swapchainImage);

        void CmdBindPipeline(const std::shared_ptr<GraphicsPipeline<Vulkan::VulkanGraphicsBackend>>& pipeline);

        void CmdPushConstants(
            const std::shared_ptr<GraphicsPipelineSignature<Vulkan::VulkanGraphicsBackend>>& pipelineSignature,
            ShaderProgramVisibility visibility,
            size_t offset,
            NovelRT::Utilities::Span<uint8_t> values);

        void CmdPipelineBufferBarrier(const std::shared_ptr<GraphicsBuffer<Vulkan::VulkanGraphicsBackend>>& buffer,
                                      GraphicsMemoryAccessMode sourceAccessFlag,
                                      GraphicsMemoryAccessMode destinationAccessFlag,
                                      GraphicsPipelineVisibility sourceStageFlag,
                                      GraphicsPipelineVisibility destinationStageFlag);

        void CmdExecuteCommands(const std::shared_ptr<GraphicsCmdList<Vulkan::VulkanGraphicsBackend>>& cmdList);

        void CmdTransitionSwapchainImageTo(
            const std::shared_ptr<GraphicsSwapchainImage<Vulkan::VulkanGraphicsBackend>>& swapchainImage,
            ImageLayout oldLayout,
            ImageLayout newLayout);

        void CmdClearColourSwapchainImage(
            const std::shared_ptr<GraphicsSwapchainImage<Vulkan::VulkanGraphicsBackend>>& swapchainImage,
            ClearValue clearData);
    };
}
