#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsBufferCreateInfo.hpp>
#include <NovelRT/Graphics/GraphicsBufferKind.hpp>
#include <NovelRT/Graphics/GraphicsResource.hpp>

namespace NovelRT::Graphics
{
    template<template <typename> typename TResource, typename TBackend> class GraphicsResourceMemoryRegion;

    template<typename TBackend> struct GraphicsBackendTraits;

    template<typename TBackend>
    class GraphicsBuffer : public GraphicsResource<TBackend>
    {
    private:
        using SuperBackendResourceType = typename GraphicsBackendTraits<TBackend>::ResourceType;
    public:
        using BackendResourceType = typename GraphicsBackendTraits<TBackend>::BufferType;
        using BackendResourceMemoryRegionType = typename GraphicsBackendTraits<TBackend>::template ResourceMemoryRegionType<BackendResourceType>;

    private:
        GraphicsBufferKind _kind;

    public:
        //NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        std::shared_ptr<GraphicsBuffer<TBackend>> shared_from_this()
        {
            return std::static_pointer_cast<GraphicsBuffer<TBackend>>(GraphicsResource<TBackend>::shared_from_this());
        }

        GraphicsBuffer(std::unique_ptr<BackendResourceType> implementation,
                       std::shared_ptr<GraphicsMemoryAllocator<TBackend>> allocator,
                       const GraphicsBufferCreateInfo& createInfo) noexcept
            : GraphicsResource<TBackend>(
                NovelRT::Utilities::StaticPointerCast<SuperBackendResourceType>(std::move(implementation)),
                std::move(allocator),
                createInfo.cpuAccessKind)
            , _kind(createInfo.bufferKind)
        {
        }

        virtual ~GraphicsBuffer() noexcept override = default;

        [[nodiscard]] GraphicsBufferKind GetKind() const noexcept
        {
            return _kind;
        }

        [[nodiscard]] std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsBuffer, TBackend>> Allocate(
            size_t size,
            size_t alignment)
        {
            return std::make_shared<GraphicsResourceMemoryRegion<GraphicsBuffer, TBackend>>(
                NovelRT::Utilities::StaticPointerCast<BackendResourceMemoryRegionType>(
                    std::move(GraphicsResource<TBackend>::AllocateInternal(size, alignment))),
                this->shared_from_this());
        }

        [[nodiscard]] BackendResourceType* GetImplementation() const noexcept
        {
            return static_cast<BackendResourceType*>(GraphicsResource<TBackend>::GetImplementation());
        }

        template <typename T> [[nodiscard]] Utilities::Span<T> Map(const GraphicsResourceMemoryRegion<GraphicsBuffer, TBackend>* memoryRegion)
        {
            return Utilities::SpanCast<T>(MapBytes(memoryRegion->GetOffset(), memoryRegion->GetSize()));
        }

        void UnmapAndWrite(const GraphicsResourceMemoryRegion<GraphicsBuffer, TBackend>* memoryRegion)
        {
            GraphicsResource<TBackend>::UnmapBytesAndWrite(memoryRegion->GetOffset(), memoryRegion->GetSize());
        }
    };
}
