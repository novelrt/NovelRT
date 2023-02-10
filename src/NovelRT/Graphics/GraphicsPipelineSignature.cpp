// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include "NovelRT/Graphics/Graphics.h"

namespace NovelRT::Graphics
{

    GraphicsPipelineSignature::GraphicsPipelineSignature(
        std::shared_ptr<GraphicsDevice> device,
        GraphicsPipelineBlendFactor srcBlendFactor,
        GraphicsPipelineBlendFactor dstBlendFactor,
        NovelRT::Utilities::Misc::Span<const GraphicsPipelineInput> inputs,
        NovelRT::Utilities::Misc::Span<const GraphicsPipelineResource> resources) noexcept
        : GraphicsDeviceObject(std::move(device)),
          _srcBlendFactor(srcBlendFactor),
          _dstBlendFactor(dstBlendFactor),
          _inputs(std::vector<GraphicsPipelineInput>(inputs.begin(), inputs.end())),
          _resources(std::vector<GraphicsPipelineResource>(resources.begin(), resources.end()))
    {
    }

    NovelRT::Utilities::Misc::Span<const GraphicsPipelineInput> GraphicsPipelineSignature::GetInputs() const noexcept
    {
        return NovelRT::Utilities::Misc::Span<const GraphicsPipelineInput>(&(*_inputs.begin()), _inputs.size());
    }
    NovelRT::Utilities::Misc::Span<const GraphicsPipelineResource> GraphicsPipelineSignature::GetResources()
        const noexcept
    {
        return NovelRT::Utilities::Misc::Span<const GraphicsPipelineResource>(&(*_resources.begin()),
                                                                              _resources.size());
    }
} // namespace NovelRT::Graphics
