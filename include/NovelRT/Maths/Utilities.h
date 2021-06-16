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

            return (address +(alignment - 1ULL)) & ~(alignment - 1ULL);
        }
    };
}

#endif // NOVELRT_UTILITIES_H
