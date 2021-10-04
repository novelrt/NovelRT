// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.h>

namespace NovelRT::Graphics
{
    RGBAColour::RGBAColour(int32_t r, int32_t g, int32_t b, int32_t a) noexcept : _r(r), _g(g), _b(b), _a(a)
    {
    }

    int32_t RGBAColour::getR() const noexcept
    {
        return _r;
    }

    void RGBAColour::setR(int32_t value) noexcept
    {
        if (value < 0)
        {
            _r = 0;
        }
        else if (value > 255)
        {
            _r = 255;
        }
        else
        {
            _r = value;
        }
    }

    int32_t RGBAColour::getG() const noexcept
    {
        return _g;
    }

    void RGBAColour::setG(int32_t value) noexcept
    {
        if (value < 0)
        {
            _g = 0;
        }
        else if (value > 255)
        {
            _g = 255;
        }
        else
        {
            _g = value;
        }
    }

    int32_t RGBAColour::getB() const noexcept
    {
        return _b;
    }

    void RGBAColour::setB(int32_t value) noexcept
    {
        if (value < 0)
        {
            _b = 0;
        }
        else if (value > 255)
        {
            _b = 255;
        }
        else
        {
            _b = value;
        }
    }

    int32_t RGBAColour::getA() const noexcept
    {
        return _a;
    }

    void RGBAColour::setA(int32_t value) noexcept
    {
        if (value < 0)
        {
            _a = 0;
        }
        else if (value > 255)
        {
            _a = 255;
        }
        else
        {
            _a = value;
        }
    }
    float RGBAColour::getRScalar() const noexcept
    {
        return getR() / 255.0f;
    }
    float RGBAColour::getGScalar() const noexcept
    {
        return getG() / 255.0f;
    }
    float RGBAColour::getBScalar() const noexcept
    {
        return getB() / 255.0f;
    }
    float RGBAColour::getAScalar() const noexcept
    {
        return getA() / 255.0f;
    }
} // namespace NovelRT::Graphics
