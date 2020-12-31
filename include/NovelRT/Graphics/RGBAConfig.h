// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICS_RGBACONFIG_H
#define NOVELRT_GRAPHICS_RGBACONFIG_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Graphics
{
    class RGBAConfig
    {

      private:
        int32_t _r;
        int32_t _g;
        int32_t _b;
        int32_t _a;

      public:
        RGBAConfig(int32_t r, int32_t g, int32_t b, int32_t a) noexcept;

        int32_t getR() const noexcept;
        float getRScalar() const noexcept;
        void setR(int32_t value) noexcept;

        int32_t getG() const noexcept;
        float getGScalar() const noexcept;
        void setG(int32_t value) noexcept;

        int32_t getB() const noexcept;
        float getBScalar() const noexcept;
        void setB(int32_t value) noexcept;

        int32_t getA() const noexcept;
        float getAScalar() const noexcept;
        void setA(int32_t value) noexcept;
    };
} // namespace NovelRT::Graphics

#endif // NOVELRT_GRAPHICS_RGBACONFIG_H
