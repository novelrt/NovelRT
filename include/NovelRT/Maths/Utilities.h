// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_MATHS_UTILITIES_H
#define NOVELRT_MATHS_UTILITIES_H

#include <NovelRT/Exceptions/InvalidOperationException.h>

namespace NovelRT::Maths
{
    class Utilities
    {
    public:
        [[nodiscard]] inline static bool IsPow2(size_t value) noexcept
        {
            return ((value & (value - 1ULL)) == 0ULL) && (value != 0ULL);
        }

        [[nodiscard]] inline static size_t AlignUp(size_t address, size_t alignment)
        {
            if (!IsPow2(alignment))
            {
                throw Exceptions::InvalidOperationException("Alignment must be to a power of two.");
            }

            return (address + (alignment - 1ULL)) & ~(alignment - 1ULL);
        }

        [[nodiscard]] [[deprecated("This implementation of PopCount is superseeded by std::popcount in C++20. This "
                                   "will be removed when the language version is updated.")]] inline static int32_t
        PopCount(uint32_t value) noexcept
        {
            const uint32_t c1 = 0x55555555u;
            const uint32_t c2 = 0x33333333u;
            const uint32_t c3 = 0x0F0F0F0Fu;
            const uint32_t c4 = 0x01010101u;

            value -= (value >> 1) & c1;
            value = (value & c2) + ((value >> 2) & c2);
            value = (((value + (value >> 4)) & c3) * c4) >> 24;

            return static_cast<int32_t>(value);
        }
    };
} // namespace NovelRT::Maths

#endif // NOVELRT_UTILITIES_H
