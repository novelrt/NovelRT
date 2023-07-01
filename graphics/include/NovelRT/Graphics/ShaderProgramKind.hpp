// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICS_SHADERPROGRAMKIND_H
#define NOVELRT_GRAPHICS_SHADERPROGRAMKIND_H

#ifndef NOVELRT_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Graphics
{
    enum class ShaderProgramKind : uint32_t
    {
        Unknown = 0,
        Vertex = 1,
        Pixel = 2,
        Fragment = Pixel
    };
}

#endif // !NOVELRT_GRAPHICS_SHADERPROGRAMKIND_H
