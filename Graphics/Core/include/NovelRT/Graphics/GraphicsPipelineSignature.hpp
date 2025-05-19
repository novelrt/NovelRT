#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDeviceObject.hpp>
#include <NovelRT/Graphics/GraphicsPipelineInput.hpp>
#include <NovelRT/Graphics/GraphicsPipelineResource.hpp>
#include <NovelRT/Graphics/GraphicsPushConstantRange.hpp>

#include <NovelRT/Utilities/Span.hpp>

namespace NovelRT::Graphics
{
    template<typename TBackend> class GraphicsDescriptorSet;

    template<typename TBackend> struct GraphicsBackendTraits;

    template<typename TBackend> class GraphicsPipelineSignature : public GraphicsDeviceObject<TBackend>
    {
    public:
        using BackendPipelineSignatureType = typename GraphicsBackendTraits<TBackend>::PipelineSignatureType;

    private:
        std::unique_ptr<BackendPipelineSignatureType> _implementation;
        GraphicsPipelineBlendFactor _srcBlendFactor;
        GraphicsPipelineBlendFactor _dstBlendFactor;
        std::vector<GraphicsPipelineInput> _inputs;
        std::vector<GraphicsPipelineResource> _resources;
        std::vector<GraphicsPushConstantRange> _pushConstantRanges;

    public:
        //NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        std::shared_ptr<GraphicsPipelineSignature<TBackend>> shared_from_this()
        {
            return std::static_pointer_cast<GraphicsPipelineSignature<TBackend>>(GraphicsDeviceObject<TBackend>::shared_from_this());
        }

        GraphicsPipelineSignature(std::unique_ptr<BackendPipelineSignatureType> implementation,
                                  std::shared_ptr<GraphicsDevice<TBackend>> device,
                                  GraphicsPipelineBlendFactor srcBlendFactor,
                                  GraphicsPipelineBlendFactor dstBlendFactor,
                                  NovelRT::Utilities::Span<const GraphicsPipelineInput> inputs,
                                  NovelRT::Utilities::Span<const GraphicsPipelineResource> resources,
                                  NovelRT::Utilities::Span<const GraphicsPushConstantRange> pushConstantRanges) noexcept
            : GraphicsDeviceObject<TBackend>(std::move(device))
            , _implementation(std::move(implementation))
            , _srcBlendFactor(srcBlendFactor)
            , _dstBlendFactor(dstBlendFactor)
            , _inputs(std::vector<GraphicsPipelineInput>(inputs.begin(), inputs.end()))
            , _resources(std::vector<GraphicsPipelineResource>(resources.begin(), resources.end()))
            , _pushConstantRanges(std::vector<GraphicsPushConstantRange>(pushConstantRanges.begin(), pushConstantRanges.end()))
        {
        }

        virtual ~GraphicsPipelineSignature() noexcept override = default;

        [[nodiscard]] BackendPipelineSignatureType* GetImplementation() const noexcept
        {
            return _implementation.get();
        }

        [[nodiscard]] GraphicsPipelineBlendFactor GetSrcBlendFactor() const noexcept
        {
            return _srcBlendFactor;
        }

        [[nodiscard]] GraphicsPipelineBlendFactor GetDstBlendFactor() const noexcept
        {
            return _dstBlendFactor;
        }

        [[nodiscard]] std::shared_ptr<GraphicsDescriptorSet<TBackend>> CreateDescriptorSet(std::shared_ptr<GraphicsPipeline<TBackend>> pipeline)
        {
            return std::make_shared<GraphicsDescriptorSet<TBackend>>(
                _implementation->CreateDescriptorSet(),
                std::move(pipeline));
        }

        [[nodiscard]] NovelRT::Utilities::Span<const GraphicsPipelineInput> GetInputs()
            const noexcept
        {
            return _inputs;
        }

        [[nodiscard]] NovelRT::Utilities::Span<const GraphicsPipelineResource> GetResources()
            const noexcept
        {
            return _resources;
        }
    };
}
