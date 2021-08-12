// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICSMEMORYALLOCATORSETTINGS_H
#define NOVELRT_EXPERIMENTAL_GRAPHICSMEMORYALLOCATORSETTINGS_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Experimental::Graphics
{
    struct GraphicsMemoryAllocatorSettings
    {
        int32_t MaximumBlockCountPerCollection = 0;
        int32_t MinimumBlockCountPerCollection = 0;
        size_t MinimumBlockSize = 0;
        size_t MinimumFreeRegionSizeToRegister = 0;
        std::optional<std::function<GraphicsMemoryBlock*(std::shared_ptr<GraphicsDevice>,
                                                         std::shared_ptr<GraphicsMemoryBlockCollection>, size_t)>>
            BlockCreationLogicDelegate;
        std::optional<bool> IsExternallySynchronised;
        std::optional<size_t> MaximumSharedBlockSize;
        std::optional<size_t> MinimumAllocatedRegionMarginSize;
    };
} // namespace NovelRT::Experimental::Graphics

#endif // !NOVELRT_EXPERIMENTAL_GRAPHICSMEMORYALLOCATORSETTINGS_H
