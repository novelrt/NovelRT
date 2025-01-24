#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsCmdList.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsResource.hpp>

namespace NovelRT::Graphics::Vulkan
{
    class VulkanGraphicsRenderPass;
    class VulkanGraphicsContext;
    class VulkanGraphicsDescriptorSet;
    class VulkanGraphicsBuffer;
    class VulkanGraphicsTexture;

    class VulkanGraphicsCmdList final : public VulkanGraphicsResource
    {
    private:
        std::shared_ptr<VulkanGraphicsContext> _context;

    public:
        explicit VulkanGraphicsCmdList(std::shared_ptr<VulkanGraphicsContext> context) noexcept;

        ~VulkanGraphicsCmdList() = default;

        [[nodiscard]] std::shared_ptr<VulkanGraphicsContext> GetContext() const noexcept;

        void CmdBeginRenderPass(std::shared_ptr<VulkanGraphicsRenderPass> targetPass);

        void CmdBindDescriptorSets(
            NovelRT::Utilities::Misc::Span<const std::shared_ptr<VulkanGraphicsDescriptorSet>> sets);

        void CmdBindVertexBuffers(uint32_t firstBinding,
                                  uint32_t bindingCount,
                                  NovelRT::Utilities::Misc::Span<const std::shared_ptr<VulkanGraphicsBuffer>> buffers,
                                  NovelRT::Utilities::Misc::Span<const size_t> offsets);

        void CmdBindIndexBuffers(NovelRT::Utilities::Misc::Span<const std::shared_ptr<VulkanGraphicsBuffer>> buffers);

        void CmdCopy(std::shared_ptr<VulkanGraphicsBuffer> destination, std::shared_ptr<VulkanGraphicsBuffer> source);
        
        void CmdCopy(std::shared_ptr<VulkanGraphicsTexture> destination, std::shared_ptr<VulkanGraphicsBuffer> source);

        void CmdDrawIndexed(uint32_t instanceCount);

        void CmdDraw(uint32_t instanceCount, uint32_t bufferStride);

        void CmdSetScissor(Maths::GeoVector2F extent);
        
        void CmdSetScissor(float xExtent, float yExtent);

        void CmdSetViewport(uint32_t firstViewport, uint32_t viewportCount, ViewportInfo viewportInfo);
    };
}