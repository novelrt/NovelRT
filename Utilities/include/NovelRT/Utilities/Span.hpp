#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <span>

namespace NovelRT::Utilities
{

    const size_t DynamicExtent = std::dynamic_extent;
    template<class T, std::size_t Extent = DynamicExtent>
    using Span = std::span<T, Extent>;

    template<typename TTo, typename TFrom, std::size_t NFrom>
    auto SpanCast(Span<TFrom, NFrom> s) noexcept -> Span<TTo, (sizeof(TFrom) * NFrom) / sizeof(TTo)>
    {
        return {reinterpret_cast<TTo*>(s.data()), s.size_bytes() / sizeof(TTo)};
    }

    template<typename TTo, typename TFrom>
    auto SpanCast(Span<TFrom, DynamicExtent> s) noexcept -> Span<TTo, DynamicExtent>
    {
        return {reinterpret_cast<TTo*>(s.data()), s.size_bytes() / sizeof(TTo)};
    }
}
