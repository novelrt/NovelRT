#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsBufferKind.hpp>
#include <NovelRT/Graphics/GraphicsResource.hpp>

namespace NovelRT::Graphics
{
    template<typename TResource, typename TBackend> class GraphicsResourceMemoryRegion;

    template<typename TBackend> struct GraphicsBackendTraits;

    template<typename TBackend> class GraphicsBuffer : public GraphicsResource<TBackend>
    {
    public:
        using BackendBufferType = typename GraphicsBackendTraits<TBackend>::BufferType;
        using BackendResourceMemoryRegionType = typename GraphicsBackendTraits<TBackend>::ResourceMemoryRegionType;

    private:
        GraphicsBufferKind _kind;

    public:
        GraphicsBuffer(std::shared_ptr<BackendBufferType> implementation,
                       std::shared_ptr<GraphicsMemoryAllocator<TBackend>> allocator,
                       GraphicsResourceAccess cpuAccess,
                       GraphicsBufferKind kind) noexcept
            : GraphicsResource(implementation, allocator, cpuAccess), _kind(kind)
        {
        }
        
        virtual ~GraphicsBuffer() noexcept override = default;

        [[nodiscard]] std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsBuffer<TBackend>, TBackend>> Allocate(size_t size, size_t alignment)
        {
            return GraphicsResource<TBackend>::_implementation->Allocate(size, alignment);
        }

        [[nodiscard]] GraphicsBufferKind GetKind() const noexcept
        {
            return _kind;
        }
    };
}