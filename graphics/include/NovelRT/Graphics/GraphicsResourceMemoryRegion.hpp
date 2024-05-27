#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDeviceObject.hpp>
#include <NovelRT/Utilities/Misc.h>
#include <memory>

namespace NovelRT::Graphics
{
    class GraphicsResource;

    class GraphicsResourceMemoryRegionBase : public GraphicsDeviceObject
    {
    private:
        std::shared_ptr<GraphicsResource> _owningResource;

    public:
        GraphicsResourceMemoryRegionBase(std::shared_ptr<GraphicsDevice> graphicsDevice,
                                         std::shared_ptr<GraphicsResource> owningResource);

        virtual ~GraphicsResourceMemoryRegionBase() = default;

        [[nodiscard]] virtual size_t GetRelativeOffset() const noexcept = 0;

        [[nodiscard]] virtual size_t GetSize() const noexcept = 0;

        [[nodiscard]] std::shared_ptr<GraphicsResource> GetOwningResource() const noexcept;

        [[nodiscard]] Utilities::Misc::Span<uint8_t> MapBytes();

        [[nodiscard]] Utilities::Misc::Span<const uint8_t> MapBytesForRead();

        void UnmapBytes();

        void UnmapBytesAndWrite();

        template<typename T> [[nodiscard]] Utilities::Misc::Span<T> Map()
        {
            return Utilities::Misc::SpanCast<T>(MapBytes());
        }

        template<typename T> [[nodiscard]] Utilities::Misc::Span<const T> MapForRead()
        {
            return Utilities::Misc::SpanCast<const T>(MapBytesForRead());
        }
    };

    template<typename TResource> class GraphicsResourceMemoryRegion : public GraphicsResourceMemoryRegionBase
    {
        GraphicsResourceMemoryRegion(std::shared_ptr<GraphicsDevice> graphicsDevice,
                                         std::shared_ptr<GraphicsResource> owningResource)
            : GraphicsResourceMemoryRegionBase(GraphicsDevice, owningResource)
        {
        }

        ~GraphicsResourceMemoryRegion() override = default;

        [[nodiscard]] std::shared_ptr<TResource> GetOwningResource() const noexcept
        {
            return std::reinterpret_pointer_cast<TResource>(GraphicsResourceMemoryRegionBase::GetOwningResource());
        }
    };
}