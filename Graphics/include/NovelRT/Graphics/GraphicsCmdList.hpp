#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDeviceObject.hpp>
#include <NovelRT/Maths/GeoVector2F.h>
#include <NovelRT/Utilities/Misc.h>
#include <memory>

namespace NovelRT::Graphics
{
    template<typename TBackend> class GraphicsContext;
    template<typename TBackend> class GraphicsBuffer;
    template<typename TBackend> class GraphicsTexture;
    template<typename TBackend> class GraphicsDescriptorSet;
    template<typename TBackend> class GraphicsRenderPass;

    // TODO: MOVE THIS
    struct ViewportInfo
    {
        float x;
        float y;
        float width;
        float height;
        float minDepth;
        float maxDepth;
    };

    template<typename TBackend> struct GraphicsBackendTraits;

    template<typename TBackend> class GraphicsCmdList : public GraphicsDeviceObject<TBackend>
    {
    public:
        using BackendCmdListType = GraphicsBackendTraits<TBackend>::CmdListType;

    private:
        std::shared_ptr<BackendCmdListType> _implementation;
        std::shared_ptr<GraphicsContext<TBackend>> _context;

    public:
        GraphicsCmdList(std::shared_ptr<BackendCmdListType> implementation,
                        std::shared_ptr<GraphicsContext<TBackend>> context) noexcept
            : _implementation(implementation), _context(context)
        {
        }

        virtual ~GraphicsCmdList() override = default;

        [[nodiscard]] std::shared_ptr<GraphicsContext> GetContext() const noexcept
        {
            return _context;
        }

        void CmdBeginRenderPass(std::shared_ptr<GraphicsRenderPass> targetPass)
        {
            _implementation->CmdBeginRenderPass(targetPass);
        }

        void CmdBindDescriptorSets(NovelRT::Utilities::Misc::Span<const std::shared_ptr<GraphicsDescriptorSet>> sets)
        {
            _implementation->CmdBindDescriptorSets(sets);
        }

        void CmdBindVertexBuffers(uint32_t firstBinding,
                                  uint32_t bindingCount,
                                  NovelRT::Utilities::Misc::Span<const std::shared_ptr<GraphicsBuffer>> buffers,
                                  NovelRT::Utilities::Misc::span<const size_t> offsets)
        {
            _implementation->CmdBindVertexBuffers(firstBinding, bindingCount, buffers, offsets);
        }

        void CmdBindIndexBuffers(NovelRT::Utilities::Misc::Span<const std::shared_ptr<GraphicsBuffer>> buffers)
        {
            _implementation->CmdBindIndexbuffers(buffers);
        }

        void CmdCopy(std::shared_ptr<GraphicsBuffer> destination, std::shared_ptr<GraphicsBuffer> source)
        {
            _implementation->CmdCopy(destination, source);
        }

        void CmdCopy(std::shared_ptr<GraphicsTexture> destination, std::shared_ptr<GraphicsBuffer> source)
        {
            _implementation->CmdCopy(destination, source);
        }

        void CmdDrawIndexed(uint32_t instanceCount)
        {
            _implementation->CmdDrawIndexed(instanceCount);
        }

        void CmdDraw(uint32_t instanceCount, uint32_t bufferStride)
        {
            _implementation->CmdDraw(instanceCount, bufferStride);
        }

        void CmdSetScissor(Maths::GeoVector2F extent)
        {
            _implementation->CmdSetScissor(extent);
        }

        void CmdSetScissor(float xExtent, float yExtent)
        {
            _implementation->CmdSetScissor(xExtent, yExtent);
        }

        void CmdSetViewport(uint32_t firstViewport, uint32_t viewportCount, ViewportInfo viewportInfo)
        {
            _implementation->CmdSetViewport(firstViewport, viewportCount, viewportInfo);
        }
    };
}