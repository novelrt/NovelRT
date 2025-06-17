#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InvalidOperationException.hpp>
#include <NovelRT/Utilities/Span.hpp>

#include <cstring>
#include <type_traits>

namespace NovelRT::Utilities::Memory
{
    template <typename T>
    constexpr std::enable_if_t<std::is_trivially_copyable_v<T>>
    Copy(NovelRT::Utilities::Span<const T> source, NovelRT::Utilities::Span<T> destination)
    {
        if (source.data() < destination.data() && (source.data() + source.size()) >= destination.data())
        {
            // source span overlaps destination:
            // [ s o u r c e   s p a n ]
            //              [ d e s t i n a t i o n   s p a n ]
            //              ^__________^ (overlap)
            // OR
            // [ s o u r c e   s p a n ]
            //              [ d s t ]
            //              ^_______^ (overlap)

            throw Exceptions::InvalidOperationException("The source span overlaps the destination span");
        }

        if (destination.data() < source.data() && (destination.data() + destination.size()) >= source.data())
        {
            // destination span overlaps source:
            //                         [ s o u r c e   s p a n ]
            // [ d e s t i n a t i o n   s p a n ]
            //                         ^_________^ (overlap)
            // OR
            //              [ s r c ]
            // [ d e s t i n a t i o n   s p a n ]
            //              ^_______^ (overlap)

            throw Exceptions::InvalidOperationException("The destination span overlaps the source span");
        }

        if (destination.size() < source.size())
        {
            // Destination is not large enough to contain the span

            throw Exceptions::InvalidOperationException("The destination span is not large enough");
        }

        memcpy(destination.data(), source.data(), source.size());
    }
}
