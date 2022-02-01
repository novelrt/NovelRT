// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICS_TEXELFORMAT_H
#define NOVELRT_GRAPHICS_TEXELFORMAT_H

#ifndef NOVELRT_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Graphics
{
    enum class TexelFormat : uint32_t
    {
        R8G8B8A8_UNORM,
        R16_SINT,
        R16G16UINT,
    };
}

#endif // NOVELRT_GRAPHICS_TEXELFORMAT_H
