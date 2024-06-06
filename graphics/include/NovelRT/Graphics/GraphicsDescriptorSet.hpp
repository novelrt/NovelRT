#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Utilities/Misc.h>
#include <memory>
#include <vector>

namespace NovelRT::Graphics
{
    template<typename TBackend> class GraphicsBuffer;
    template<typename TBackend> class GraphicsPipeline;
    template<typename TBackend> class GraphicsTexture;

    template<typename TBackend> class GraphicsDescriptorSet
    {
    public:
        using BackendDescriptorSetType = TBackend::BackendDescriptorSetType;

    private:
        std::shared_ptr<BackendDescriptorSetType> _implementation;
        std::shared_ptr<GraphicsPipeline<TBackend>> _pipeline;

    public:
        explicit GraphicsDescriptorSet(std::shared_ptr<BackendDescriptorSetType> implementation,
                                       std::shared_ptr<GraphicsPipeline<TBackend>> targetPipeline) noexcept
            : _implementation(implementation), _pipeline(targetPipeline)
        {
        }

        std::shared_ptr<GraphicsPipeline<TBackend>> GraphicsDescriptorSet::GetPipeline() const noexcept
        {
            return _pipeline;
        }

        void GraphicsDescriptorSet::AddBuffers(
            NovelRT::Utilities::Misc::Span<const std::shared_ptr<GraphicsBuffer<TBackend>>> buffers)
        {
            _implementation->AddBuffers(buffers);
        }

        void AddTextures(NovelRT::Utilities::Misc::Span<const std::shared_ptr<GraphicsTexture<TBackend>>> textures)
        {
            _implementation->AddTextures(textures);
        }
    };
}