#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#if NOVELRT_USE_STD_SPAN
#include <span>
#else
#include <gsl/span>
#endif

namespace NovelRT::Utilities
{

#ifdef NOVELRT_USE_STD_SPAN
    const size_t DynamicExtent = std::dynamic_extent;
#else
    const size_t DynamicExtent = gsl::dynamic_extent;
#endif

    template<class T, std::size_t Extent = DynamicExtent>
#ifdef NOVELRT_USE_STD_SPAN
    using Span = std::span<T, Extent>;
#else
    using Span = gsl::span<T, Extent>;
#endif

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
