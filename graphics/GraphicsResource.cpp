// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsResource.hpp>

namespace NovelRT::Graphics
{
    GraphicsResource::GraphicsResource(std::shared_ptr<GraphicsDevice> graphicsDevice, std::shared_ptr<GraphicsMemoryAllocator> allocator, GraphicsResourceAccess cpuAccess) noexcept
        : GraphicsDeviceObject(graphicsDevice), _allocator(allocator), _cpuAccess(cpuAccess)
    {
    }

    std::shared_ptr<GraphicsMemoryAllocator> GraphicsResource::GetAllocator() const noexcept
    {
        return _allocator;
    }    

    GraphicsResourceAccess GraphicsResource::GetCpuAccess() const noexcept
    {
        return _cpuAccess;
    }

    Utilities::Misc::Span<uint8_t> GraphicsResource::MapBytes()
    {
        return MapBytes(0, GetSize());
    }

    Utilities::Misc::Span<const uint8_t> GraphicsResource::MapBytesForRead()
    {
        return MapBytesForRead(0, GetSize());
    }

    void GraphicsResource::UnmapBytesAndWrite()
    {
        UnmapBytesAndWrite(0, GetSize());
    }
}