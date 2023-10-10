// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICS_SHADERPROGRAMVISIBILITY_H
#define NOVELRT_GRAPHICS_SHADERPROGRAMVISIBILITY_H

#ifndef NOVELRT_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Graphics
{
    enum class ShaderProgramVisibility : uint32_t
    {
        NoneOrUnknown = 0,
        Vertex = 1 << 0,
        Pixel = 1 << 1,
        Fragment = Pixel,
        All = Vertex | Pixel
    };
}

#endif // !NOVELRT_GRAPHICS_SHADERPROGRAMVISIBILITY_H
