#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsPipelineInputElement.hpp>
#include <NovelRT/Utilities/Misc.h>
#include <vector>

namespace NovelRT::Graphics
{
    class GraphicsPipelineInput
    {
    private:
        std::vector<GraphicsPipelineInputElement> _elements;

    public:
        explicit GraphicsPipelineInput(
            NovelRT::Utilities::Misc::Span<const GraphicsPipelineInputElement> elements) noexcept;

        [[nodiscard]] NovelRT::Utilities::Misc::Span<const GraphicsPipelineInputElement> GetElements() const noexcept;
    };
}
