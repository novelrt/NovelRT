// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Experimental/Graphics/Graphics.h>

namespace NovelRT::Experimental::Graphics
{
    GraphicsPipelineInput::GraphicsPipelineInput(gsl::span<const GraphicsPipelineInputElement> elements) noexcept :
    _elements(std::vector<GraphicsPipelineInputElement>(elements.begin(), elements.end()))
    {
    }

    gsl::span<const GraphicsPipelineInputElement> GraphicsPipelineInput::GetElements() const noexcept
    {
        return gsl::span<const GraphicsPipelineInputElement>(&(*_elements.begin()), _elements.size());
    }
}
