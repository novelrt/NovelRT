#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDeviceObject.hpp>
#include <NovelRT/Maths/GeoVector2F.h>
#include <NovelRT/Utilities/Misc.h>
#include <memory>

namespace NovelRT::Graphics
{
    class GraphicsContext;
    class GraphicsBuffer;
    class GraphicsTexture;
    class GraphicsDescriptorSet;
    class GraphicsRenderPass;

    // TODO: MOVE THIS
    struct ViewportInfo
    {
        float x = 0;
        float y = 0;
        float width = 0;
        float height = 0;
        float minDepth = 0;
        float maxDepth = 0;
    };

    class GraphicsCmdList : public GraphicsDeviceObject
    {
    private:
        std::shared_ptr<GraphicsContext> _context;

    public:
        explicit GraphicsCmdList(std::shared_ptr<GraphicsContext> context) noexcept;

        virtual ~GraphicsCmdList() = default;

        [[nodiscard]] std::shared_ptr<GraphicsContext> GetContext() const noexcept;

        virtual void CmdBeginRenderPass(std::shared_ptr<GraphicsRenderPass> targetPass) = 0;

        virtual void CmdBindDescriptorSets(
            NovelRT::Utilities::Misc::Span<const std::shared_ptr<GraphicsDescriptorSet>> sets) = 0;

        virtual void CmdBindVertexBuffers(uint32_t firstBinding,
                                          uint32_t bindingCount,
                                          NovelRT::Utilities::Misc::Span<const std::shared_ptr<GraphicsBuffer>> buffers,
                                          NovelRT::Utilities::Misc::span<const size_t> offsets) = 0;

        virtual void CmdBindVertexBuffers()

        virtual void CmdBindIndexBuffers(
            NovelRT::Utilities::Misc::Span<const std::shared_ptr<GraphicsBuffer>> buffers) = 0;

        virtual void CmdCopy(std::shared_ptr<GraphicsBuffer> destination, std::shared_ptr<GraphicsBuffer> source) = 0;

        virtual void CmdCopy(std::shared_ptr<GraphicsTexture> destination, std::shared_ptr<GraphicsBuffer> source) = 0;

        virtual void CmdDrawIndexed(uint32_t instanceCount) = 0;

        virtual void CmdDraw(uint32_t instanceCount, uint32_t bufferStride) = 0;

        virtual void CmdSetScissor(Maths::GeoVector2F extent) = 0;

        virtual void CmdSetScissor(float xExtent, float yExtent) = 0;

        virtual void CmdSetViewport(uint32_t firstViewport, uint32_t viewportCount, ViewportInfo viewportInfo) = 0;
    };
}