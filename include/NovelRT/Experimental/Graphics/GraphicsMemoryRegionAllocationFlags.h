// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICSMEMORYREGIONALLOCATIONFLAGS_H
#define NOVELRT_EXPERIMENTAL_GRAPHICSMEMORYREGIONALLOCATIONFLAGS_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Experimental::Graphics
{
    enum class GraphicsMemoryRegionAllocationFlags : uint32_t
    {
        None = 0,
        DedicatedCollection = 1 << 0,
        ExistingCollection = 1 << 1,
        WithinBudget = 1 << 2
    };
}

#endif // !NOVELRT_EXPERIMENTAL_GRAPHICSMEMORYREGIONALLOCATIONFLAGS_H
