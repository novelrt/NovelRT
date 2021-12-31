// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_GRAPHICSTEXTUREADDRESSMODE_H
#define NOVELRT_EXPERIMENTAL_GRAPHICS_GRAPHICSTEXTUREADDRESSMODE_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Experimental::Graphics
{
    enum class GraphicsTextureAddressMode : uint32_t
    {
        Wrap = 0,
        Repeat = Wrap,
        MirroredRepeat = 1,
        ClampToEdge = 2,
        ClampToBorder = 3,
        MirrorClampToEdge = 4
    };
}

#endif // NOVELRT_EXPERIMENTAL_GRAPHICS_GRAPHICSTEXTUREADDRESSMODE_H
