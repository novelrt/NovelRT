#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsBufferKind.hpp>
#include <NovelRT/Graphics/GraphicsResource.hpp>

namespace NovelRT::Graphics
{
    template<typename TResource>
    class GraphicsResourceMemoryRegion;

    class GraphicsBuffer : public GraphicsResource
    {
    private:
        GraphicsBufferKind _kind;

    public:
        GraphicsBuffer(std::shared_ptr<GraphicsDevice> graphicsDevice, std::shared_ptr<GraphicsMemoryAllocator> allocator, GraphicsResourceAccess cpuAccess, GraphicsBufferKind kind);
        
        ~GraphicsBuffer() noexcept override = default;

        [[nodiscard]] std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsBuffer>>  Allocate(size_t size, size_t alignment);

        [[nodiscard]] GraphicsBufferKind GetKind() const noexcept;
    };
}