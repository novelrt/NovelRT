#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsMemoryAccessMode.hpp>
#include <NovelRT/Graphics/GraphicsPipelineVisibility.hpp>
#include <NovelRT/Graphics/RGBAColour.hpp>
#include <NovelRT/Graphics/ShaderProgramVisibility.hpp>
#include <NovelRT/Maths/GeoVector2F.hpp>
#include <NovelRT/Utilities/Span.hpp>

#include <cstdint>
#include <functional>
#include <memory>

namespace NovelRT::Graphics
{
    template<typename TBackend>
    class GraphicsContext;
    template<typename TBackend>
    class GraphicsBuffer;
    template<typename TBackend>
    class GraphicsPipeline;
    template<typename TBackend>
    class GraphicsTexture;
    template<typename TBackend>
    class GraphicsDescriptorSet;
    template<typename TBackend>
    class GraphicsRenderPass;
    template<typename TBackend>
    class GraphicsPipelineSignature;
    template<template<typename> typename TResource, typename TBackend>
    class GraphicsResourceMemoryRegion;

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

    template<typename TBackend>
    struct GraphicsBackendTraits;

    enum class IndexType
    {
        None = 0,
        UInt16 = 1,
        UInt32 = 2
    };

    struct ClearValue
    {
        RGBAColour colour = RGBAColour(0, 0, 0, 0);
        float depth;
        uint32_t stencil;
    };

    template<typename TBackend>
    class GraphicsCmdList : std::enable_shared_from_this<GraphicsCmdList<TBackend>>
    {
    public:
        GraphicsCmdList() = delete;
        ~GraphicsCmdList() = default;

        [[nodiscard]] std::shared_ptr<GraphicsContext<TBackend>> GetContext() const noexcept;

        void CmdBeginRenderPass(const std::shared_ptr<GraphicsRenderPass<TBackend>>& targetPass,
                                Utilities::Span<const ClearValue> clearValues);

        void CmdEndRenderPass();

        void CmdBindDescriptorSets(NovelRT::Utilities::Span<std::reference_wrapper<const std::shared_ptr<GraphicsDescriptorSet<TBackend>>>> sets);

        void CmdBindVertexBuffers(uint32_t firstBinding,
                                  uint32_t bindingCount,
                                  NovelRT::Utilities::Span<std::reference_wrapper<const std::shared_ptr<GraphicsBuffer<TBackend>>>> buffers,
                                  NovelRT::Utilities::Span<const size_t> offsets);

        void CmdBindIndexBuffer(const std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsBuffer, TBackend>>& buffer,
                                IndexType indexType);

        void CmdCopy(const std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsBuffer, TBackend>>& destination,
                     const std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsBuffer, TBackend>>& source);

        void CmdCopy(const std::shared_ptr<GraphicsTexture<TBackend>>& destination,
                     const std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsBuffer, TBackend>>& source);

        void CmdDrawIndexed(uint32_t indexCount,
                            uint32_t instanceCount,
                            uint32_t firstIndex,
                            size_t vertexOffset,
                            uint32_t firstInstance);

        void CmdDraw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance);

        void CmdSetScissor(Maths::GeoVector2F offset, Maths::GeoVector2F extent);

        void CmdSetViewport(ViewportInfo viewportInfo);

        void CmdBeginTexturePipelineBarrierLegacyVersion(const std::shared_ptr<GraphicsTexture<TBackend>>& texture);
        void CmdEndTexturePipelineBarrierLegacyVersion(const std::shared_ptr<GraphicsTexture<TBackend>>& texture);

        void CmdBindPipeline(const std::shared_ptr<GraphicsPipeline<TBackend>>& pipeline);

        void CmdPushConstants(const std::shared_ptr<GraphicsPipelineSignature<TBackend>>& pipelineSignature,
                              ShaderProgramVisibility visibility,
                              size_t offset,
                              Utilities::Span<uint8_t> values);

        void CmdPipelineBufferBarrier(const std::shared_ptr<GraphicsBuffer<TBackend>>& buffer,
                                      GraphicsMemoryAccessMode sourceAccessFlag,
                                      GraphicsMemoryAccessMode destinationAccessFlag,
                                      GraphicsPipelineVisibility sourceStageFlag,
                                      GraphicsPipelineVisibility destinationStageFlag);
    };
}
