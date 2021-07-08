// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Experimental/Graphics/Graphics.h>

namespace NovelRT::Experimental::Graphics
{
    GraphicsPipelineInputElement::GraphicsPipelineInputElement(std::type_index type,
                                                               GraphicsPipelineInputElementKind kind,
                                                               size_t size) noexcept
        : _type(type), _kind(kind), _size(size)
    {
    }

    std::type_index GraphicsPipelineInputElement::GetType() const noexcept
    {
        return _type;
    }

    GraphicsPipelineInputElementKind GraphicsPipelineInputElement::GetKind() const noexcept
    {
        return _kind;
    }

    size_t GraphicsPipelineInputElement::GetSize() const noexcept
    {
        return _size;
    }
} // namespace NovelRT::Experimental::Graphics
