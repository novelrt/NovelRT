// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsResource.hpp>
#include <NovelRT/Graphics/GraphicsResourceMemoryRegion.hpp>

namespace NovelRT::Graphics
{
    GraphicsResourceMemoryRegion::GraphicsResourceMemoryRegion(std::shared_ptr<GraphicsDevice> graphicsDevice,
                                                               std::shared_ptr<GraphicsResource> owningResource)
        : GraphicsDeviceObject(graphicsDevice), _owningResource(owningResource)
    {
    }

    std::shared_ptr<GraphicsResource> GraphicsResourceMemoryRegion::GetOwningResource() const noexcept
    {
        return _owningResource;
    }

    Utilities::Misc::Span<uint8_t> GraphicsResourceMemoryRegion::MapBytes()
    {
        return _owningResource->MapBytes(GetRelativeOffset(), GetSize());
    }

    Utilities::Misc::Span<const uint8_t> GraphicsResourceMemoryRegion::MapBytesForRead()
    {
        return _owningResource->MapBytesForRead(GetRelativeOffset(), GetSize());
    }

    void GraphicsResourceMemoryRegion::UnmapBytes()
    {
        _owningResource->UnmapBytes();
    }

    void GraphicsResourceMemoryRegion::UnmapBytesAndWrite()
    {
        _owningResource->UnmapBytesAndWrite(GetRelativeOffset(), GetSize());
    }
}