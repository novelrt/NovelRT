// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsBuffer.hpp>
#include <NovelRT/Graphics/GraphicsResource.hpp>

namespace NovelRT::Graphics
{
    GraphicsBuffer::GraphicsBuffer(std::shared_ptr<GraphicsDevice> graphicsDevice,
                                   std::shared_ptr<GraphicsMemoryAllocator> allocator,
                                   GraphicsResourceAccess cpuAccess,
                                   GraphicsBufferKind kind)
        : GraphicsResource(graphicsDevice, allocator, cpuAccess), _kind(kind)
    {
    }
    
    std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsBuffer>> GraphicsBuffer::Allocate(size_t size, size_t alignment)
    {
        return std::reinterpret_pointer_cast<GraphicsResourceMemoryRegion<GraphicsBuffer>>(GraphicsResource::Allocate(size, alignment));
    }

    GraphicsBufferKind GraphicsBuffer::GetKind() const noexcept
    {
        return _kind;
    }
}