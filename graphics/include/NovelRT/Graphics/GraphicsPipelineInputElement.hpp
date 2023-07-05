#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <typeindex>
#include <NovelRT/Graphics/GraphicsPipelineInputElementKind.hpp>

namespace NovelRT::Graphics
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
