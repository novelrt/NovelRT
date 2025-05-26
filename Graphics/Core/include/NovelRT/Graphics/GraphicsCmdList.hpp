#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsMemoryAccessMode.hpp>
#include <NovelRT/Graphics/GraphicsPipelineVisibility.hpp>
#include <NovelRT/Graphics/RGBAColour.hpp>
#include <NovelRT/Maths/GeoVector2F.hpp>
#include <NovelRT/Utilities/Span.hpp>

#include <memory>
#include <cstdint>

namespace NovelRT::Graphics
{
    template<typename TBackend> class GraphicsContext;
    template<typename TBackend> class GraphicsBuffer;
    template<typename TBackend> class GraphicsTexture;
    template<typename TBackend> class GraphicsDescriptorSet;
    template<typename TBackend> class GraphicsRenderPass;
    template<template<typename TBackend> typename TResource, typename TBackend> class GraphicsResourceMemoryRegion;

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

    template<typename TBackend> class GraphicsCmdList
    {
    public:
        using BackendCmdListType = typename GraphicsBackendTraits<TBackend>::CmdListType;
        using BackendDescriptorType = typename GraphicsBackendTraits<TBackend>::DescriptorSetType;
        using BackendBufferType = typename GraphicsBackendTraits<TBackend>::BufferType;
        template<typename TResource>
        using BackendResourceMemoryRegionType =
            typename GraphicsBackendTraits<TBackend>::template ResourceMemoryRegionType<TResource>;

    public:
        std::shared_ptr<BackendCmdListType> _implementation;
        std::shared_ptr<GraphicsContext<TBackend>> _context;

    public:
        GraphicsCmdList(std::shared_ptr<BackendCmdListType> implementation,
                        std::shared_ptr<GraphicsContext<TBackend>> context) noexcept
            : _implementation(implementation), _context(context)
        {
        }

        ~GraphicsCmdList() = default;

        [[nodiscard]] std::shared_ptr<GraphicsContext<TBackend>> GetContext() const noexcept
        {
            return _context;
        }

        void CmdBeginRenderPass(std::shared_ptr<GraphicsRenderPass<TBackend>> targetPass,
                                Utilities::Span<const ClearValue> clearValues)
        {
            _implementation->CmdBeginRenderPass(targetPass->GetImplementation(), clearValues);
        }

        void CmdEndRenderPass()
        {
            _implementation->CmdEndRenderPass();
        }

        void CmdBindDescriptorSets(
            NovelRT::Utilities::Span<const std::shared_ptr<GraphicsDescriptorSet<TBackend>>> sets)
        {
            std::vector<std::shared_ptr<BackendDescriptorType>> transformedArgs{};
            transformedArgs.resize(sets.size());
            std::transform(sets.begin(), sets.end(), transformedArgs.begin(),
                           [&](auto x) { return x->GetImplementation(); });
            _implementation->CmdBindDescriptorSets(transformedArgs);
        }

        void CmdBindVertexBuffers(
            uint32_t firstBinding,
            uint32_t bindingCount,
            NovelRT::Utilities::Span<const std::shared_ptr<GraphicsBuffer<TBackend>>> buffers,
            NovelRT::Utilities::Span<const size_t> offsets)
        {
            std::vector<std::shared_ptr<BackendBufferType>> transformedArgs{};
            transformedArgs.resize(buffers.size());
            std::transform(buffers.begin(), buffers.end(), transformedArgs.begin(),
                           [&](auto x) { return x->GetImplementation(); });
            _implementation->CmdBindVertexBuffers(firstBinding, bindingCount, transformedArgs, offsets);
        }

        void CmdBindIndexBuffer(std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsBuffer, TBackend>> buffer,
                                IndexType indexType)
        {
            _implementation->CmdBindIndexBuffer(buffer->GetImplementation(), indexType);
        }

        void CmdCopy(std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsBuffer, TBackend>> destination,
                     std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsBuffer, TBackend>> source)
        {
            _implementation->CmdCopy(destination->GetImplementation(), source->GetImplementation());
        }

        void CmdCopy(std::shared_ptr<GraphicsTexture<TBackend>> destination,
                     std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsBuffer, TBackend>> source)
        {
            _implementation->CmdCopy(destination->GetImplementation(), source->GetImplementation());
        }

        void CmdDrawIndexed(uint32_t indexCount,
                            uint32_t instanceCount,
                            uint32_t firstIndex,
                            size_t vertexOffset,
                            uint32_t firstInstance)
        {
            _implementation->CmdDrawIndexed(indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
        }

        void CmdDraw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance)
        {
            _implementation->CmdDraw(vertexCount, instanceCount, firstVertex, firstInstance);
        }

        void CmdSetScissor(Maths::GeoVector2F offset, Maths::GeoVector2F extent)
        {
            _implementation->CmdSetScissor(offset, extent);
        }

        void CmdSetViewport(ViewportInfo viewportInfo)
        {
            _implementation->CmdSetViewport(viewportInfo);
        }

        void CmdBeginTexturePipelineBarrierLegacyVersion(std::shared_ptr<GraphicsTexture<TBackend>> texture)
        {
            _implementation->CmdBeginTexturePipelineBarrierLegacyVersion(texture->GetImplementation());
        }

        void CmdEndTexturePipelineBarrierLegacyVersion(std::shared_ptr<GraphicsTexture<TBackend>> texture)
        {
            _implementation->CmdEndTexturePipelineBarrierLegacyVersion(texture->GetImplementation());
        }

        void CmdBindPipeline(std::shared_ptr<GraphicsPipeline<TBackend>> pipeline)
        {
            _implementation->CmdBindPipeline(pipeline->GetImplementation());
        }

        void CmdPushConstants(std::shared_ptr<GraphicsPipelineSignature<TBackend>> pipelineSignature, ShaderProgramVisibility visibility, size_t offset, Utilities::Misc::Span<uint8_t> values)
        {
            _implementation->CmdPushConstants(pipelineSignature->GetImplementation(), visibility, offset, values);
        }

        void CmdPipelineBufferBarrier(std::shared_ptr<GraphicsBuffer<TBackend>> buffer, 
            GraphicsMemoryAccessMode sourceAccessFlag, 
            GraphicsMemoryAccessMode destinationAccessFlag, 
            GraphicsPipelineVisibility sourceStageFlag, 
            GraphicsPipelineVisibility destinationStageFlag)
        {
            _implementation->CmdPipelineBufferBarrier(buffer->GetImplementation(), sourceAccessFlag, destinationAccessFlag, sourceStageFlag, destinationStageFlag);
        }
    };
}
