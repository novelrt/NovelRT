// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_GRAPHICSPIPELINEINPUTELEMENT_H
#define NOVELRT_EXPERIMENTAL_GRAPHICS_GRAPHICSPIPELINEINPUTELEMENT_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Experimental::Graphics
{
    class GraphicsPipelineInputElement
    {
    private:
        std::type_index _type;
        GraphicsPipelineInputElementKind _kind;
        size_t _size;

    public:
        GraphicsPipelineInputElement(std::type_index type, GraphicsPipelineInputElementKind kind, size_t size) noexcept;
        [[nodiscard]] std::type_index GetType() const noexcept;
        [[nodiscard]] GraphicsPipelineInputElementKind GetKind() const noexcept;
        [[nodiscard]] size_t GetSize() const noexcept;
    };
}

#endif // !NOVELRT_EXPERIMENTAL_GRAPHICS_GRAPHICSPIPELINEINPUTELEMENT_H
