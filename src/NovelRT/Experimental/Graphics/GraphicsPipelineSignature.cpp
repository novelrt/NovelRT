// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Experimental/Graphics/Graphics.h>

namespace NovelRT::Experimental::Graphics
{

    GraphicsPipelineSignature::GraphicsPipelineSignature(std::shared_ptr<GraphicsDevice> device,
                                                         gsl::span<const GraphicsPipelineInput> inputs,
                                                         gsl::span<const GraphicsPipelineResource> resources) noexcept
        : GraphicsDeviceObject(std::move(device)),
          _inputs(std::vector<GraphicsPipelineInput>(inputs.begin(), inputs.end())),
          _resources(std::vector<GraphicsPipelineResource>(resources.begin(), resources.end()))
    {
    }

    gsl::span<const GraphicsPipelineInput> GraphicsPipelineSignature::GetInputs() const noexcept
    {
        return gsl::span<const GraphicsPipelineInput>(&(*_inputs.begin()), _inputs.size());
    }
    gsl::span<const GraphicsPipelineResource> GraphicsPipelineSignature::GetResources() const noexcept
    {
        return gsl::span<const GraphicsPipelineResource>(&(*_resources.begin()), _resources.size());
    }
} // namespace NovelRT::Experimental::Graphics
