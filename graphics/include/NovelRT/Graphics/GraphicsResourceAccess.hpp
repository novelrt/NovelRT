// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICS_GRAPHICSRESOURCEACCESS_H
#define NOVELRT_GRAPHICS_GRAPHICSRESOURCEACCESS_H

#ifndef NOVELRT_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Graphics
{
    enum class GraphicsResourceAccess : uint32_t
    {
        None = 1 << 0,
        Read = 1 << 1,
        Write = 1 << 2,
        ReadWrite = Read | Write,
    };
}

#endif // !NOVELRT_GRAPHICS_GRAPHICSRESOURCEACCESS_H
