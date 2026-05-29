// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsResource.hpp>
#include <NovelRT/Graphics/GraphicsResourceMemoryRegion.hpp>

namespace NovelRT::Graphics
{

    template<typename TBackend>
    Utilities::Span<uint8_t> GraphicsResourceMemoryRegion<GraphicsResource, TBackend>::MapBytes()
    {
        return GetOwningResource()->MapBytes(GetOffset(), GetSize());
    }

    template<typename TBackend>
    Utilities::Span<const uint8_t> GraphicsResourceMemoryRegion<GraphicsResource, TBackend>::MapBytesForRead()
    {
        return GetOwningResource()->MapBytesForRead(GetOffset(), GetSize());
    }

    template<typename TBackend>
    void GraphicsResourceMemoryRegion<GraphicsResource, TBackend>::UnmapBytes()
    {
        GetOwningResource()->UnmapBytes();
    }

    template<typename TBackend>
    void GraphicsResourceMemoryRegion<GraphicsResource, TBackend>::UnmapBytesAndWrite()
    {
        GetOwningResource()->UnmapBytesAndWrite();
    }

    template<typename TBackend>
    template<typename T>
    Utilities::Span<T> GraphicsResourceMemoryRegion<GraphicsResource, TBackend>::Map()
    {
        return GetOwningResource()->template Map<T>(this);
    }

    template<typename TBackend>
    template<typename T>
    Utilities::Span<const T> GraphicsResourceMemoryRegion<GraphicsResource, TBackend>::MapForRead()
    {
        return GetOwningResource()->template MapForRead<T>(this);
    }

}