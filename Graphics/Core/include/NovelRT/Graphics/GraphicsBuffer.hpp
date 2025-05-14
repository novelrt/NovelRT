#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsBufferCreateInfo.hpp>
#include <NovelRT/Graphics/GraphicsBufferKind.hpp>
#include <NovelRT/Graphics/GraphicsResource.hpp>

namespace NovelRT::Graphics
{
    template<template <typename TBackend> typename TResource, typename TBackend> class GraphicsResourceMemoryRegion;

    template<typename TBackend> struct GraphicsBackendTraits;

    template<typename TBackend> class GraphicsBuffer : public GraphicsResource<TBackend>, public std::enable_shared_from_this<GraphicsBuffer<TBackend>>
    {
    public:
        using BackendBufferType = typename GraphicsBackendTraits<TBackend>::BufferType;
        using BackendResourceType = BackendBufferType;
        using BackendResourceMemoryRegionType = typename GraphicsBackendTraits<TBackend>::template ResourceMemoryRegionType<BackendResourceType>;

    private:
        GraphicsBufferKind _kind;

    public:
        using std::enable_shared_from_this<GraphicsBuffer<TBackend>>::shared_from_this;

        GraphicsBuffer(std::shared_ptr<BackendBufferType> implementation,
                       std::shared_ptr<GraphicsMemoryAllocator<TBackend>> allocator,
                       const GraphicsBufferCreateInfo& createInfo) noexcept
            : GraphicsResource<TBackend>(implementation, allocator, createInfo.cpuAccessKind), _kind(createInfo.bufferKind)
        {
        }

        virtual ~GraphicsBuffer() noexcept override = default;

        [[nodiscard]] std::shared_ptr<BackendBufferType> GetImplementation() const noexcept
        {
            return std::static_pointer_cast<BackendBufferType>(GraphicsResource<TBackend>::_implementation);
        }

        [[nodiscard]] std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsBuffer, TBackend>> Allocate(size_t size, size_t alignment)
        {
            return std::make_shared<GraphicsResourceMemoryRegion<GraphicsBuffer, TBackend>>(
                std::static_pointer_cast<BackendResourceMemoryRegionType>(GraphicsResource<TBackend>::_implementation->Allocate(size, alignment)),
                this->shared_from_this());
        }

        [[nodiscard]] GraphicsBufferKind GetKind() const noexcept
        {
            return _kind;
        }
    };
}
