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

#ifndef NOVELRT_MATHS_H
#error NovelRT does not support including types explicitly by default. Please include Maths.h instead for the Maths namespace subset.
#endif

#if __has_include(<version>)
#include <version>
#endif

#if __cpp_lib_bitops
#include <bit>
#endif

/**
 * @brief Contains utility functions to assist in mathematical operations.
 */
namespace NovelRT::Maths::Utilities
{
    /**
     * @brief Creates a lookup table for calculating the log base 2 for a 32 bit integer.
     *
     * @details
     * This is a pure method. Calling this without using the result has no effect and can introduce overhead for calling
     * the method.
     *
     * @return A lookup table for calculating the log base 2 for a 32 bit integer.
     */
    [[nodiscard]] inline constexpr std::array<uint8_t, 32> Log2DeBruijn() noexcept
    {
        return std::array<uint8_t, 32>{0, 9,  1,  10, 13, 21, 2,  29, 11, 14, 16, 18, 22, 25, 3, 30,
                                       8, 12, 20, 28, 15, 17, 24, 7,  19, 27, 23, 6,  26, 5,  4, 31};
    }

    /**
     * @brief Evaluates if the provided integer is a power of 2.
     *
     * @details
     * This is a pure method. Calling this without using the result has no effect and can introduce overhead for calling
     * the method.
     *
     * @param value The given integer to be tested.
     * @return true if the given integer is a power of 2, otherwise false.
     */
    [[nodiscard]] inline constexpr bool IsPow2(size_t value) noexcept
    {
        return ((value & (value - 1ULL)) == 0ULL) && (value != 0ULL);
    }

    /**
     * @brief Rounds a given address up to the nearest alignment.
     *
     * @details
     * This is a pure method. Calling this without using the result has no effect and can introduce overhead for calling
     * the method.
     *
     * @param address The address to be aligned.
     * @param alignment The target alignment, which should be a power of two.
     * @return The address rounded up to the nearest alignment.
     */
    [[nodiscard]] inline constexpr size_t AlignUp(size_t address, size_t alignment)
    {
        assert(IsPow2(alignment) && "Alignment must be to a power of two.");

        return (address + (alignment - 1ULL)) & ~(alignment - 1ULL);
    }

    /**
     * @brief Returns the number of set bits in the given value.
     *
     * @details
     * This is a pure method. Calling this without using the result has no effect and can introduce overhead for calling
     * the method.
     *
     * This implementation was previously marked as deprecated, but to prevent unnecessary complications it
     * uses <a href="https://en.cppreference.com/w/cpp/numeric/popcount">std::popcount</a> when available instead of
     * being removed.
     *
     * @param value The number to extract the amount of set bits from
     * @return The number of set bits.
     */
    [[nodiscard]] inline constexpr int32_t PopCount(uint32_t value) noexcept
    {
#if __cpp_lib_bitops
        return std::popcount(value);
#else
        const uint32_t c1 = 0x55555555u;
        const uint32_t c2 = 0x33333333u;
        const uint32_t c3 = 0x0F0F0F0Fu;
        const uint32_t c4 = 0x01010101u;

        value -= (value >> 1) & c1;
        value = (value & c2) + ((value >> 2) & c2);
        value = (((value + (value >> 4)) & c3) * c4) >> 24;

        return static_cast<int32_t>(value);
#endif
    }

    /**
     * @brief Determines the exponent to which 2 should be raised with in order to get to the given value, rounded down.
     *
     * @details
     * When the input value is 0, 0 will be returned.
     *
     * This is a pure method. Calling this without using the result has no effect and can introduce overhead for calling
     * the method.
     *
     * @param value The value to reach with 2 to the power of the resulting exponent.
     * @return The exponent to get to the given number, rounded down
     */
    [[nodiscard]] inline constexpr uint32_t Log2(uint32_t value) noexcept
    {
        value |= value >> 1;
        value |= value >> 2;
        value |= value >> 4;
        value |= value >> 8;
        value |= value >> 16;

        return Log2DeBruijn()[(value * 0x07C4ACDDu) >> 27];
    }

    /**
     * @brief Computes the amount of leading zeros for the given 32-bit integer.
     *
     * @details
     * This is a pure method. Calling this without using the result has no effect and can introduce overhead for calling
     * the method.
     *
     * @param value The number to get the amount of leading zeros from.
     * @return The amount of leading zeros.
     */
    [[nodiscard]] inline constexpr uint32_t LeadingZeroCount32(uint32_t value) noexcept
    {
#if __cpp_lib_bitops
        return std::countl_zero(value);
#else
        if (value == 0)
        {
            return 32;
        }
        else
        {
            return 31 ^ Log2(value);
        }
#endif
    }

    /**
     * @brief Computes the amount of leading zeros for the given 64-bit integer.
     *
     * @details
     * This is a pure method. Calling this without using the result has no effect and can introduce overhead for calling
     * the method.
     *
     * @param value The number to get the amount of leading zeros from.
     * @return The amount of leading zeros.
     */
    [[nodiscard]] inline constexpr uint64_t LeadingZeroCount64(uint64_t value) noexcept
    {
#if __cpp_lib_bitops
        return std::countl_zero(value);
#else
        uint32_t hi = static_cast<uint32_t>(value >> 32);

        if (hi == 0)
        {
            return 32 + LeadingZeroCount32(static_cast<uint32_t>(value));
        }
        else
        {
            return LeadingZeroCount32(hi);
        }
#endif
    }

    /**
     * @brief Converts an angle in degrees to an angle in radians.
     *
     * @details
     * To get the angle in radians you can use this formula: \f[
     *      radians = \frac{\pi \times degrees}{180}
     * \f]
     *
     * This is a pure method. Calling this without using the result has no effect and can introduce overhead for calling
     * the method.
     *
     * @param degrees The angle in degrees to convert.
     * @return The angle in radians.
     */
    [[nodiscard]] inline float DegreesToRadians(float degrees) noexcept
    {
        return glm::radians(degrees);
    }

    /**
     * @brief Converts an angle in degrees to an angle in radians.
     *
     * @details
     * To get the angle in degrees you can use this formula: \f[
     *      degrees = \frac{180 \times radians}{\pi }
     * \f]
     *
     * This is a pure method. Calling this without using the result has no effect and can introduce overhead for calling
     * the method.
     *
     * @param radians The angle in radians to convert.
     * @return The angle in degrees.
     */
    [[nodiscard]] inline float RadiansToDegrees(float radians) noexcept
    {
        return glm::degrees(radians);
    }

    /**
     * @brief Retrieves a constant for a full rotation expressed in radians.
     *
     * @details
     * A full rotation is expressed as: \f[
     *      2\pi = 6.283185307179586476925...
     * \f]
     *
     * This is a pure method. Calling this without using the result has no effect and can introduce overhead for calling
     * the method.
     *
     * @tparam TFloatingPointType A floating point type that is expressed as either float or double.
     * @return A full rotation expressed in radians.
     */
    template<typename TFloatingPointType>[[nodiscard]] inline constexpr TFloatingPointType Tau() noexcept
    {
        _assert(std::is_same_v<TFloatingPointType, float> || std::is_same_v<TFloatingPointType, double>,
                "Type is unsupported for a Tau representation.");
    }

    /**
     * @brief Retrieves a constant for a full rotation expressed in radians.
     *
     * @details
     * A full rotation is expressed as: \f[
     *      2\pi = 6.283185307179586476925...
     * \f]
     * In this implementation it is expressed as \f(6.283185307\f).
     *
     * This is a pure method. Calling this without using the result has no effect and can introduce overhead for calling
     * the method.
     *
     * @return A full rotation expressed in radians.
     */
    template<>[[nodiscard]] inline constexpr float Tau<float>() noexcept
    {
        return 6.283185307f;
    }

    /**
     * @brief Retrieves a constant for a full rotation expressed in radians.
     *
     * @details
     * A full rotation is expressed as: \f[
     *      2\pi = 6.283185307179586476925...
     * \f]
     * In this implementation it is expressed as \f(6.283185307179586476925\f).
     *
     * This is a pure method. Calling this without using the result has no effect and can introduce overhead for calling
     * the method.
     *
     * @return A full rotation expressed in radians.
     */
    template<>[[nodiscard]] inline constexpr double Tau<double>() noexcept
    {
        return 6.283185307179586476925;
    }
}

#endif // NOVELRT_UTILITIES_H
