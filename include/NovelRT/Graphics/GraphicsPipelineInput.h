// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICS_GRAPHICSPIPELINEINPUT_H
#define NOVELRT_GRAPHICS_GRAPHICSPIPELINEINPUT_H

#ifndef NOVELRT_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

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

#endif // !NOVELRT_GRAPHICS_GRAPHICSPIPELINEINPUT_H
