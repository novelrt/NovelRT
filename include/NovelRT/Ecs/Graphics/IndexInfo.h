// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_GRAPHICS_INDEXINFO_H
#define NOVELRT_ECS_GRAPHICS_INDEXINFO_H

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

namespace NovelRT::Ecs::Graphics
{
    struct IndexInfo
    {
        NovelRT::Graphics::GraphicsMemoryRegion<NovelRT::Graphics::GraphicsResource> gpuIndexRegion = {};
        std::string indexInfoName;
        Atom ecsId = 0;
        void* stagingPtr = nullptr;
        IndexIntegerKind indexKind = IndexIntegerKind::UInt16;
        size_t sizeofIndexStructData = 0;
        size_t stagingPtrLength = 0;

        bool operator==(const IndexInfo& other) const noexcept
        {
            return (gpuIndexRegion == other.gpuIndexRegion) && (indexInfoName == other.indexInfoName) &&
                   (ecsId == other.ecsId);
        }
    };
}

#endif // NOVELRT_ECS_GRAPHICS_INDEXINFO_H
