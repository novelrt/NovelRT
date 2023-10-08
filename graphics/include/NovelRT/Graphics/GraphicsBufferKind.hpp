// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICS_GRAPHICSBUFFERKIND_H
#define NOVELRT_GRAPHICS_GRAPHICSBUFFERKIND_H

#ifndef NOVELRT_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Graphics
{
    enum class GraphicsBufferKind : uint32_t
    {
        Default = 0,
        Vertex = 1,
        Index = 2,
        Constant = 3,
        Uniform = Constant
    };
}

#endif // !NOVELRT_GRAPHICS_GRAPHICSBUFFERKIND_H
