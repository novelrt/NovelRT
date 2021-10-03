// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_GRAPHICSPIPELINEINPUT_H
#define NOVELRT_EXPERIMENTAL_GRAPHICS_GRAPHICSPIPELINEINPUT_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Experimental::Graphics
{
    class GraphicsPipelineInput
    {
    private:
        std::vector<GraphicsPipelineInputElement> _elements;

    public:
        explicit GraphicsPipelineInput(gsl::span<const GraphicsPipelineInputElement> elements) noexcept;

        [[nodiscard]] gsl::span<const GraphicsPipelineInputElement> GetElements() const noexcept;
    };
}

#endif // !NOVELRT_EXPERIMENTAL_GRAPHICS_GRAPHICSPIPELINEINPUT_H
