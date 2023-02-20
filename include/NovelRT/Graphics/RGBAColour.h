// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICS_RGBACOLOUR_H
#define NOVELRT_GRAPHICS_RGBACOLOUR_H

#include <cstdint>

namespace NovelRT::Graphics
{
    class RGBAColour
    {
    public:
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;

        RGBAColour() noexcept :
            r(0), g(0), b(0), a(0)
        {
        }

        RGBAColour(uint8_t initialR, uint8_t initialG, uint8_t initialB, uint8_t initialA) noexcept
            : r(initialR), g(initialG), b(initialB), a(initialA)
        {
        }

        [[nodiscard]] inline float getRScalar() const noexcept
        {
            return r / 255.0f;
        }

        [[nodiscard]] inline float getGScalar() const noexcept
        {
            return g / 255.0f;
        }

        [[nodiscard]] inline float getBScalar() const noexcept
        {
            return b / 255.0f;
        }

        [[nodiscard]] inline float getAScalar() const noexcept
        {
            return a / 255.0f;
        }

        [[nodiscard]] inline uint32_t Get32BitColour() const noexcept
        {
            return (r | g << 8 | b << 16 | a << 24);
        }
    };
}

#endif // NOVELRT_GRAPHICS_RGBACOLOUR_H
