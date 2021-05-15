// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_SHADERPROGRAMVISIBILITY_H
#define NOVELRT_SHADERPROGRAMVISIBILITY_H

namespace NovelRT::Experimental::Graphics
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

#endif // NOVELRT_SHADERPROGRAMVISIBILITY_H
