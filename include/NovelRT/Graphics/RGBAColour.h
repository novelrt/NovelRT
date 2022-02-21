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
        int32_t r;
        int32_t g;
        int32_t b;
        int32_t a;

        RGBAColour(int32_t initialR, int32_t initialG, int32_t initialB, int32_t initialA) noexcept
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
    };
}

#endif // NOVELRT_GRAPHICS_RGBACOLOUR_H
