// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICSMEMORYALLOCATORSETTINGS_H
#define NOVELRT_GRAPHICSMEMORYALLOCATORSETTINGS_H

namespace NovelRT::Experimental::Graphics
{
    struct GraphicsMemoryAllocatorSettings
    {
        int32_t MaximumBlockCountPerCollection = 0;
        int32_t MinimumBlockCountPerCollection = 0;
        uint64_t MinimumBlockSize = 0;
        uint64_t MinimumFreeRegionSizeToRegister = 0;
        std::optional<std::type_index> RegionCollectionMetadataType;
        std::optional<bool> IsExternallySynchronised;
        std::optional<uint64_t> MaximumSharedBlockSize;
        std::optional<uint64_t> MinimumAllocatedRegionMarginSize;

    };
} // namespace NovelRT::Experimental::Graphics

#endif // NOVELRT_GRAPHICSMEMORYALLOCATORSETTINGS_H
