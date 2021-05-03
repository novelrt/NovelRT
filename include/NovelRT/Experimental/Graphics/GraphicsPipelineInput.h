// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICSPIPELINEINPUT_H
#define NOVELRT_GRAPHICSPIPELINEINPUT_H

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
        GraphicsPipelineInput(gsl::span<GraphicsPipelineInputElement> elements) noexcept :
        _elements(std::vector<GraphicsPipelineInputElement>(elements.begin(), elements.end()))
        {
        }

        [[nodiscard]] inline gsl::span<GraphicsPipelineInputElement> GetElements() const noexcept
        {
            return gsl::span<GraphicsPipelineInputElement>(&(*_elements.begin()), _elements.size());
        }
    };
}

#endif // NOVELRT_GRAPHICSPIPELINEINPUT_H
