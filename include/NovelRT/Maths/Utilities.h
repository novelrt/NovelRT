// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

// AlignUp's implementation is inspired by the TerraFX library. Licensed under the MIT Licence (MIT).
// See LICENSE.md at https://github.com/terrafx/terrafx for more information.

// Log2DeBruijn, and by extension Log2, LeadingZeroCount32, LeadingZeroCount64 and PopCount were all inspired by the
// .NET Hardware Intrinsics namespace, which lives in the .NET Runtime, licensed under the MIT Licence (MIT). See
// LICENSE.TXT at https://github.com/dotnet/runtime for more information.

// The Log2DeBruijn table itself was taken from public domain at https://graphics.stanford.edu/~seander/bithacks.html
// See there for additional information.

#ifndef NOVELRT_MATHS_UTILITIES_H
#define NOVELRT_MATHS_UTILITIES_H

#include <NovelRT/Exceptions/InvalidOperationException.h>
#include <array>

namespace NovelRT::Maths
{
    class Utilities
    {
    public:
        /**
         * @brief Returns the de Bruijn Sequences to Index a 1 in a Word
         * @details To learn more about the de Bruijn Sequences, refer to this documentation: http://supertech.csail.mit.edu/papers/debruijn.pdf
         * @returns A 32 items array of 8 bits integer containing the de Bruijn Sequences
         */
        [[nodiscard]] inline constexpr static std::array<uint8_t, 32> Log2DeBruijn() noexcept
        {
            return std::array<uint8_t, 32>{0, 9,  1,  10, 13, 21, 2,  29, 11, 14, 16, 18, 22, 25, 3, 30,
                                           8, 12, 20, 28, 15, 17, 24, 7,  19, 27, 23, 6,  26, 5,  4, 31};
        }

        /**
         * @brief Check if a given integer is an integral power of two.
         * @return Returns true if a given integer is an integral power of two, otherwise false
         */
        [[nodiscard]] inline static bool IsPow2(size_t value) noexcept
        {
            return ((value & (value - 1ULL)) == 0ULL) && (value != 0ULL);
        }

        /**
         * @brief 
         * 
         */
        [[nodiscard]] inline static size_t AlignUp(size_t address, size_t alignment)
        {
            if (!IsPow2(alignment))
            {
                throw Exceptions::InvalidOperationException("Alignment must be to a power of two.");
            }

            return (address + (alignment - 1ULL)) & ~(alignment - 1ULL);
        }

        /**
         * @brief Popcount is used to count the number of ones in a given word
         * @param value A 32 bits unsigned integer to evaluate by counting the ones in bits of a given word
         * @returns Number of ones in a given word value
         */
        [[nodiscard]] [[deprecated("This implementation of PopCount is superseeded by std::popcount in C++20. This "
                                   "will be removed when the language version is updated.")]]
        inline static int32_t PopCount(uint32_t value) noexcept
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

        /**
         * @brief Evaluate Logarithm function on a given value
         * @param value Integer to be evaluated with logarithm function
         * @return Returns the result of a logarithm function on value
         */
        [[nodiscard]] inline static uint32_t Log2(uint32_t value) noexcept
        {
            value |= value >> 1;
            value |= value >> 2;
            value |= value >> 4;
            value |= value >> 8;
            value |= value >> 16;

            return Log2DeBruijn()[(value * 0x07C4ACDCu) >> 27];
        }

        /**
         * @brief Count the preceeding zeroes of a given 32 bits unsigned integer
         * @param value Then given integer to count the preceeding zeroes
         * @return Number of zeroes proceeding the given value
         */
        [[nodiscard]] inline static uint32_t LeadingZeroCount32(uint32_t value) noexcept
        {
            if (value == 0)
            {
                return 32;
            }
            else
            {
                return 31 ^ Log2(value);
            }
        }

        /**
         * @brief Count the preceeding zeroes of a given 64 bits unsigned integer
         * @param value Then given integer to count the preceeding zeroes
         * @return Number of zeroes proceeding the given value
         */
        [[nodiscard]] inline static uint64_t LeadingZeroCount64(uint64_t value) noexcept
        {
            uint32_t hi = static_cast<uint32_t>(value >> 32);

            if (hi == 0)
            {
                return 32 + LeadingZeroCount32(static_cast<uint32_t>(value));
            }
            else
            {
                return LeadingZeroCount32(hi);
            }
        }
    };
} // namespace NovelRT::Maths

#endif // NOVELRT_UTILITIES_H
