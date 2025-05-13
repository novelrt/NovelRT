#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDeviceObject.hpp>
#include <NovelRT/Utilities/Misc.h>
#include <memory>

namespace NovelRT::Graphics
{
    template<typename TBackend> class GraphicsResource;

    template<typename TBackend> struct GraphicsBackendTraits;

    template<typename TResource, typename TBackend>
    class GraphicsResourceMemoryRegion : public GraphicsDeviceObject<TBackend>
    {
        static_assert(std::is_base_of_v<GraphicsResource<TBackend>, TResource>,
                      "Incompatible type specified as the resource type.");

    public:
        using BackendResourceMemoryRegionType = typename GraphicsBackendTraits<TBackend>::ResourceMemoryRegionType;

    private:
        std::shared_ptr<BackendResourceMemoryRegionType> _implementation;
        std::shared_ptr<TResource> _owningResource;

    public:
        GraphicsResourceMemoryRegion(std::shared_ptr<BackendResourceMemoryRegionType> implementation,
                                     std::shared_ptr<TResource> owningResource)
            : GraphicsDeviceObject<TBackend>(implementation->GetDevice()),
              _implementation(implementation),
              _owningResource(owningResource)
        {
        }

        [[nodiscard]] std::shared_ptr<TResource> GetOwningResource() const noexcept
        {
            return _owningResource;
        }

        [[nodiscard]] size_t GetOffset() const noexcept
        {
            return _implementation->GetOffset();
        }

        [[nodiscard]] virtual size_t GetSize() const noexcept
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
