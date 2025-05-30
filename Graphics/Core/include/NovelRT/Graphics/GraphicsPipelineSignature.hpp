#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDeviceObject.hpp>
#include <NovelRT/Graphics/GraphicsPipelineInput.hpp>
#include <NovelRT/Graphics/GraphicsPipelineResource.hpp>
#include <NovelRT/Graphics/GraphicsPushConstantRange.hpp>

namespace NovelRT::Graphics
{
    template<typename TBackend> class GraphicsDescriptorSet;

    template<typename TBackend> struct GraphicsBackendTraits;

    template<typename TBackend> class GraphicsPipelineSignature : public GraphicsDeviceObject<TBackend>
    {
    public:
        using BackendPipelineSignatureType = typename GraphicsBackendTraits<TBackend>::PipelineSignatureType;

    private:
        std::shared_ptr<BackendPipelineSignatureType> _implementation;
        GraphicsPipelineBlendFactor _srcBlendFactor;
        GraphicsPipelineBlendFactor _dstBlendFactor;
        std::vector<GraphicsPipelineInput> _inputs;
        std::vector<GraphicsPipelineResource> _resources;
        std::vector<GraphicsPushConstantRange> _pushConstantRanges;

    public:
        GraphicsPipelineSignature(std::shared_ptr<BackendPipelineSignatureType> implementation,
                                  std::shared_ptr<GraphicsDevice<TBackend>> device,
                                  GraphicsPipelineBlendFactor srcBlendFactor,
                                  GraphicsPipelineBlendFactor dstBlendFactor,
                                  NovelRT::Utilities::Misc::Span<const GraphicsPipelineInput> inputs,
                                  NovelRT::Utilities::Misc::Span<const GraphicsPipelineResource> resources,
                                  NovelRT::Utilities::Misc::Span<const GraphicsPushConstantRange> pushConstantRanges) noexcept
            : GraphicsDeviceObject<TBackend>(device),
              _implementation(implementation),
              _srcBlendFactor(srcBlendFactor),
              _dstBlendFactor(dstBlendFactor),
              _inputs(std::vector<GraphicsPipelineInput>(inputs.begin(), inputs.end())),
              _resources(std::vector<GraphicsPipelineResource>(resources.begin(), resources.end())),
              _pushConstantRanges(std::vector<GraphicsPushConstantRange>(pushConstantRanges.begin(), pushConstantRanges.end()))
        {
        }

        virtual ~GraphicsPipelineSignature() noexcept override = default;

        [[nodiscard]] std::shared_ptr<BackendPipelineSignatureType> GetImplementation() const noexcept
        {
            return _implementation;
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
                pipeline);
        }

        [[nodiscard]] NovelRT::Utilities::Misc::Span<const GraphicsPipelineInput> GetInputs()
            const noexcept
        {
            return NovelRT::Utilities::Misc::Span<const GraphicsPipelineInput>(&(*_inputs.begin()), _inputs.size());
        }

        [[nodiscard]] NovelRT::Utilities::Misc::Span<const GraphicsPipelineResource> GetResources()
            const noexcept
        {
            return NovelRT::Utilities::Misc::Span<const GraphicsPipelineResource>(&(*_resources.begin()),
                                                                                  _resources.size());
        }
    };
}
