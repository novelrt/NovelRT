// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsPipelineInput.hpp>
#include <NovelRT/Graphics/GraphicsPipelineInputElement.hpp>

namespace NovelRT::Graphics
{
    GraphicsPipelineInput::GraphicsPipelineInput(
        NovelRT::Utilities::Misc::Span<const GraphicsPipelineInputElement> elements) noexcept
        : _elements(std::vector<GraphicsPipelineInputElement>(elements.begin(), elements.end()))
    {
    }

    NovelRT::Utilities::Misc::Span<const GraphicsPipelineInputElement> GraphicsPipelineInput::GetElements()
        const noexcept
    {
        return NovelRT::Utilities::Misc::Span<const GraphicsPipelineInputElement>(&(*_elements.begin()),
                                                                                  _elements.size());
    }
} // namespace NovelRT::Graphics
