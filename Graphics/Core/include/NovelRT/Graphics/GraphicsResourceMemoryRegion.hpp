#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDeviceObject.hpp>
#include <NovelRT/Utilities/Misc.h>
#include <memory>
#include <type_traits>

namespace NovelRT::Graphics
{
    template<typename TBackend> class GraphicsResource;

    template<typename TBackend> struct GraphicsBackendTraits;

    template<template <typename TBackend> typename TResource, typename TBackend>
    class GraphicsResourceMemoryRegion
        : public std::conditional_t<
            std::is_same_v<TResource<TBackend>, GraphicsResource<TBackend>>,
            GraphicsDeviceObject<TBackend>,
            GraphicsResourceMemoryRegion<GraphicsResource, TBackend>>
    {
        static_assert(std::is_base_of_v<GraphicsResource<TBackend>, TResource<TBackend>>,
                      "Incompatible type specified as the resource type.");
    public:
        using BackendResourceType = typename TResource<TBackend>::BackendResourceType;
        using BackendResourceMemoryRegionType = typename GraphicsBackendTraits<TBackend>::template ResourceMemoryRegionType<BackendResourceType>;

        using Super = std::conditional_t<std::is_same_v<TResource<TBackend>, GraphicsResource<TBackend>>, GraphicsDeviceObject<TBackend>, GraphicsResourceMemoryRegion<GraphicsResource, TBackend>>;

    private:
        std::shared_ptr<BackendResourceMemoryRegionType> _implementation;
        std::shared_ptr<TResource<TBackend>> _owningResource;

    public:
        template <typename S = Super, std::enable_if_t<std::is_same_v<S, GraphicsDeviceObject<TBackend>>, bool> = true>
        GraphicsResourceMemoryRegion(std::shared_ptr<BackendResourceMemoryRegionType> implementation,
                                     std::shared_ptr<TResource<TBackend>> owningResource)
            : Super(owningResource->GetDevice()),
                _implementation(implementation),
                _owningResource(owningResource)
            {
            }

        template <typename S = Super, std::enable_if_t<std::is_same_v<S, GraphicsResourceMemoryRegion<GraphicsResource, TBackend>>, bool> = true>
        GraphicsResourceMemoryRegion(std::shared_ptr<BackendResourceMemoryRegionType> implementation,
                                     std::shared_ptr<TResource<TBackend>> owningResource)
            : Super(implementation, owningResource),
                _implementation(implementation),
                _owningResource(owningResource)
            {
            }

        virtual ~GraphicsResourceMemoryRegion() noexcept override = default;

        [[nodiscard]] std::shared_ptr<BackendResourceMemoryRegionType> GetImplementation() const noexcept
        {
            return _implementation;
        }

        [[nodiscard]] std::shared_ptr<TResource<TBackend>> GetOwningResource() const noexcept
        {
            return _owningResource;
        }

        [[nodiscard]] size_t GetOffset() const noexcept
        {
            return _implementation->GetOffset();
        }

        [[nodiscard]] size_t GetSize() const noexcept
        {
            return _implementation->GetSize();
        }

        [[nodiscard]] Utilities::Misc::Span<uint8_t> MapBytes()
        {
            return _implementation->MapBytes(GetOffset(), GetSize());
        }

        [[nodiscard]] Utilities::Misc::Span<const uint8_t> MapBytesForRead()
        {
            return _implementation->MapBytesForRead(GetOffset(), GetSize());
        }

        void UnmapBytes()
        {
            _implementation->UnmapBytes();
        }

        void UnmapBytesAndWrite()
        {
            _implementation->UnmapBytesAndWrite(GetOffset(), GetSize());
        }

        template<typename T> [[nodiscard]] Utilities::Misc::Span<T> Map()
        {
            return Utilities::Misc::SpanCast<T>(MapBytes());
        }

        template<typename T> [[nodiscard]] Utilities::Misc::Span<const T> MapForRead()
        {
            return Utilities::Misc::SpanCast<const T>(MapBytesForRead());
        }
    };
}
