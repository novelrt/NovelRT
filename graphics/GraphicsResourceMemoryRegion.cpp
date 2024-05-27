// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsResource.hpp>
#include <NovelRT/Graphics/GraphicsResourceMemoryRegion.hpp>

namespace NovelRT::Graphics
{
    GraphicsResourceMemoryRegionBase::GraphicsResourceMemoryRegionBase(std::shared_ptr<GraphicsDevice> graphicsDevice,
                                                               std::shared_ptr<GraphicsResource> owningResource)
        : GraphicsDeviceObject(graphicsDevice), _owningResource(owningResource)
    {
    }

    std::shared_ptr<GraphicsResource> GraphicsResourceMemoryRegionBase::GetOwningResource() const noexcept
    {
        return _owningResource;
    }

    Utilities::Misc::Span<uint8_t> GraphicsResourceMemoryRegionBase::MapBytes()
    {
        return _owningResource->MapBytes(GetRelativeOffset(), GetSize());
    }

    Utilities::Misc::Span<const uint8_t> GraphicsResourceMemoryRegionBase::MapBytesForRead()
    {
        return _owningResource->MapBytesForRead(GetRelativeOffset(), GetSize());
    }

    void GraphicsResourceMemoryRegionBase::UnmapBytes()
    {
        _owningResource->UnmapBytes();
    }

    void GraphicsResourceMemoryRegionBase::UnmapBytesAndWrite()
    {
        _owningResource->UnmapBytesAndWrite(GetRelativeOffset(), GetSize());
    }
}