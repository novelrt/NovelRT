#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDeviceObject.hpp>
#include <NovelRT/Graphics/GraphicsResourceAccess.hpp>
#include <NovelRT/Utilities/Misc.h>
#include <cstdint>
#include <memory>

namespace NovelRT::Graphics
{
    class GraphicsMemoryAllocator;
    class GraphicsResourceMemoryRegionBase;

    template<typename TResource>
    class GraphicsResourceMemoryRegion;

    class GraphicsResource : public GraphicsDeviceObject
    {
    private:
        std::shared_ptr<GraphicsMemoryAllocator> _allocator;
        GraphicsResourceAccess _cpuAccess;

    public:
        GraphicsResource(std::shared_ptr<GraphicsDevice> graphicsDevice,
                         std::shared_ptr<GraphicsMemoryAllocator> allocator,
                         GraphicsResourceAccess cpuAccess) noexcept;

        ~GraphicsResource() noexcept override = default;

        //[[nodiscard]] virtual size_t GetAlignment() const noexcept = 0; //TODO: Do we still need this?
        [[nodiscard]] std::shared_ptr<GraphicsMemoryAllocator> GetAllocator() const noexcept;

        [[nodiscard]] GraphicsResourceAccess GetCpuAccess() const noexcept;

        [[nodiscard]] virtual size_t GetDeviceMemoryOffset() const noexcept = 0;

        [[nodiscard]] virtual size_t GetSize() const noexcept = 0;

        [[nodiscard]] virtual std::shared_ptr<GraphicsResourceMemoryRegionBase> Allocate(size_t size, size_t alignment) = 0;

        [[nodiscard]] Utilities::Misc::Span<uint8_t> MapBytes();

        [[nodiscard]] virtual Utilities::Misc::Span<uint8_t> MapBytes(size_t rangeOffset, size_t rangeLength) = 0;

        [[nodiscard]] Utilities::Misc::Span<const uint8_t> MapBytesForRead();

        [[nodiscard]] virtual Utilities::Misc::Span<const uint8_t> MapBytesForRead(size_t rangeOffset,
                                                                                   size_t rangeLength) = 0;
        virtual void UnmapBytes() = 0;

        void UnmapBytesAndWrite();

        virtual void UnmapBytesAndWrite(size_t writtenRangeOffset, size_t writtenRangeLength) = 0;

        template<typename T> [[nodiscard]] Utilities::Misc::Span<T> Map()
        {
            return Utilities::Misc::SpanCast<T>(MapBytes());
        }

        template<typename T> [[nodiscard]] Utilities::Misc::Span<T> Map(size_t rangeOffset, size_t rangeLength)
        {
            return Utilities::Misc::SpanCast<T>(MapBytes(rangeOffset, rangeLength));
        }

        template<typename T> [[nodiscard]] Utilities::Misc::Span<const T> MapForRead()
        {
            return Utilities::Misc::SpanCast<const T>(MapBytesForRead());
        }

        template<typename T>
        [[nodiscard]] Utilities::Misc::Span<const T> MapForRead(size_t rangeOffset, size_t rangeLength)
        {
            return Utilities::Misc::SpanCast<const T>(MapBytesForRead(rangeOffset, rangeLength));
        }
    };
}