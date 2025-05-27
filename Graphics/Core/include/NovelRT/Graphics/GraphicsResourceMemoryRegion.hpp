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
        std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsResource, TBackend>> shared_from_this();

        GraphicsResourceMemoryRegion() = delete;
        virtual ~GraphicsResourceMemoryRegion() noexcept override = default;

        [[nodiscard]] std::shared_ptr<GraphicsResource<TBackend>> GetOwningResource() const noexcept;

        [[nodiscard]] size_t GetOffset() const noexcept;
        [[nodiscard]] size_t GetSize() const noexcept;

        [[nodiscard]] Utilities::Span<uint8_t> MapBytes();

        [[nodiscard]] Utilities::Span<const uint8_t> MapBytesForRead();

        void UnmapBytes();

        void UnmapBytesAndWrite();

        template<typename T> [[nodiscard]] Utilities::Span<T> Map();

        template<typename T> [[nodiscard]] Utilities::Span<const T> MapForRead();
    };

    template<template <typename> typename TResource, typename TBackend>
    class GraphicsResourceMemoryRegion : public GraphicsResourceMemoryRegion<GraphicsResource, TBackend>
    {
        static_assert(std::is_base_of_v<GraphicsResource<TBackend>, TResource<TBackend>>, "TResource must inherit GraphicsResource");

    public:
        std::shared_ptr<GraphicsResourceMemoryRegion<TResource, TBackend>> shared_from_this();

        GraphicsResourceMemoryRegion() = delete;

        [[nodiscard]] TResource<TBackend>* GetOwningResource() const noexcept;
    };
}
