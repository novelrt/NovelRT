#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDeviceObject.hpp>
#include <NovelRT/Utilities/Span.hpp>
#include <NovelRT/Utilities/Pointers.hpp>

#include <memory>
#include <type_traits>

namespace NovelRT::Graphics
{
    template<typename TBackend>
    class GraphicsResource;

    template<typename TBackend> struct GraphicsBackendTraits;

    template<template <typename> typename TResource, typename TBackend>
    class GraphicsResourceMemoryRegion;

    template <typename TBackend>
    class GraphicsResourceMemoryRegion<GraphicsResource, TBackend> : public GraphicsDeviceObject<TBackend>
    {
    public:
        using BackendResourceMemoryRegionType = typename GraphicsBackendTraits<TBackend>::template ResourceMemoryRegionType<typename GraphicsResource<TBackend>::BackendResourceType>;

    private:
        std::unique_ptr<BackendResourceMemoryRegionType> _implementation;
        std::shared_ptr<GraphicsResource<TBackend>> _owningResource;

    public:
        std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsResource, TBackend>> shared_from_this()
        {
            return std::static_pointer_cast<GraphicsResourceMemoryRegion<GraphicsResource, TBackend>>(GraphicsDeviceObject<TBackend>::shared_from_this());
        }

        GraphicsResourceMemoryRegion(std::unique_ptr<BackendResourceMemoryRegionType> implementation,
                                     std::shared_ptr<GraphicsResource<TBackend>> owningResource)
            : GraphicsDeviceObject<TBackend>(owningResource->GetDevice())
            , _implementation(std::move(implementation))
            , _owningResource(std::move(owningResource))
        { }

        virtual ~GraphicsResourceMemoryRegion() noexcept override = default;

        [[nodiscard]] BackendResourceMemoryRegionType* GetImplementation() const noexcept
        {
            return _implementation.get();
        }

        [[nodiscard]] GraphicsResource<TBackend>* GetOwningResource() const noexcept
        {
            return _owningResource.get();
        }

        [[nodiscard]] size_t GetOffset() const noexcept
        {
            return _implementation->GetOffset();
        }

        [[nodiscard]] size_t GetSize() const noexcept
        {
            return _implementation->GetSize();
        }

        [[nodiscard]] Utilities::Span<uint8_t> MapBytes()
        {
            return _owningResource->MapBytes(GetOffset(), GetSize());
        }

        [[nodiscard]] Utilities::Span<const uint8_t> MapBytesForRead()
        {
            return _owningResource->MapBytesForRead(GetOffset(), GetSize());
        }

        void UnmapBytes()
        {
            _owningResource->UnmapBytes();
        }

        void UnmapBytesAndWrite()
        {
            _owningResource->UnmapBytesAndWrite(GetOffset(), GetSize());
        }

        template<typename T> [[nodiscard]] Utilities::Span<T> Map()
        {
            return Utilities::SpanCast<T>(MapBytes());
        }

        template<typename T> [[nodiscard]] Utilities::Span<const T> MapForRead()
        {
            return Utilities::SpanCast<const T>(MapBytesForRead());
        }
    };

    template<template <typename> typename TResource, typename TBackend>
    class GraphicsResourceMemoryRegion : public GraphicsResourceMemoryRegion<GraphicsResource, TBackend>
    {
        static_assert(std::is_base_of_v<GraphicsResource<TBackend>, TResource<TBackend>>, "TResource must inherit GraphicsResource");

    private:
        using SuperBackendResourceMemoryRegionType = typename GraphicsResourceMemoryRegion<GraphicsResource, TBackend>::BackendResourceMemoryRegionType;

    public:
        using BackendResourceMemoryRegionType = typename TResource<TBackend>::BackendResourceMemoryRegionType;

        std::shared_ptr<GraphicsResourceMemoryRegion<TResource, TBackend>> shared_from_this()
        {
            return std::static_pointer_cast<GraphicsResourceMemoryRegion<TResource, TBackend>>(
                GraphicsResourceMemoryRegion<GraphicsResource, TBackend>::shared_from_this());
        }

        GraphicsResourceMemoryRegion(
            std::unique_ptr<BackendResourceMemoryRegionType> implementation,
            std::shared_ptr<GraphicsResource<TBackend>> owningResource)
            : GraphicsResourceMemoryRegion<GraphicsResource, TBackend>(
                NovelRT::Utilities::StaticPointerCast<SuperBackendResourceMemoryRegionType>(std::move(implementation)),
                owningResource)
        { }

        [[nodiscard]] BackendResourceMemoryRegionType* GetImplementation() const noexcept
        {
            return static_cast<BackendResourceMemoryRegionType*>(
                GraphicsResourceMemoryRegion<GraphicsResource, TBackend>::GetImplementation());
        }

        [[nodiscard]] TResource<TBackend>* GetOwningResource() const noexcept
        {
            return static_cast<BackendResourceMemoryRegionType*>(
                GraphicsResourceMemoryRegion<GraphicsResource, TBackend>::GetOwningResource());
        }
    };
}
