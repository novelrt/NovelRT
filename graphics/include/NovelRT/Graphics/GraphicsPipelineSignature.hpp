#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDeviceObject.hpp>
#include <NovelRT/Graphics/GraphicsPipelineInput.hpp>
#include <NovelRT/Graphics/GraphicsPipelineResource.hpp>

namespace NovelRT::Graphics
{
    template<typename TBackend> class GraphicsDescriptorSet;

    template<typename TBackend> class GraphicsPipelineSignature : public GraphicsDeviceObject<TBackend>
    {
    public:
        using BackendPipelineSignatureType = TBackend::PipelineSignatureType;

    private:
        std::shared_ptr<BackendPipelineSignatureType> _implementation;
        GraphicsPipelineBlendFactor _srcBlendFactor;
        GraphicsPipelineBlendFactor _dstBlendFactor;
        std::vector<GraphicsPipelineInput> _inputs;
        std::vector<GraphicsPipelineResource> _resources;

    public:
        GraphicsPipelineSignature(std::shared_ptr<BackendPipelineSignatureType> implementation,
                                  std::shared_ptr<GraphicsDevice<TBackend>> device,
                                  GraphicsPipelineBlendFactor srcBlendFactor,
                                  GraphicsPipelineBlendFactor dstBlendFactor,
                                  NovelRT::Utilities::Misc::Span<const GraphicsPipelineInput> inputs,
                                  NovelRT::Utilities::Misc::Span<const GraphicsPipelineResource> resources) noexcept
            : GraphicsDeviceObject(device),
              _implementation(implementation),
              _srcBlendFactor(srcBlendFactor),
              _dstBlendFactor(dstBlendFactor),
              _inputs(std::vector<GraphicsPipelineInput>(inputs.begin(), inputs.end())),
              _resources(std::vector<GraphicsPipelineResource>(resources.begin(), resources.end()))
        {
        }

        virtual ~GraphicsPipelineSignature() = default;
        
        NovelRT::Utilities::Misc::Span<const GraphicsPipelineInput> GraphicsPipelineSignature::GetInputs()
            const noexcept
        {
            return NovelRT::Utilities::Misc::Span<const GraphicsPipelineInput>(&(*_inputs.begin()), _inputs.size());
        }

        NovelRT::Utilities::Misc::Span<const GraphicsPipelineResource> GraphicsPipelineSignature::GetResources()
            const noexcept
        {
            return NovelRT::Utilities::Misc::Span<const GraphicsPipelineResource>(&(*_resources.begin()),
                                                                                  _resources.size());
        }

        [[nodiscard]] inline GraphicsPipelineBlendFactor GraphicsPipelineSignature::GetSrcBlendFactor() const noexcept
        {
            return _srcBlendFactor;
        }

        [[nodiscard]] inline GraphicsPipelineBlendFactor GraphicsPipelineSignature::GetDstBlendFactor() const noexcept
        {
            return _dstBlendFactor;
        }

        [[nodiscard]] std::shared_ptr<GraphicsDescriptorSet> CreateDescriptorSet()
        {
            return _implementation->CreateDescriptorSet();
        }
    };
}
