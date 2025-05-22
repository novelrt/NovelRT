#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsBufferKind.hpp>
#include <NovelRT/Graphics/GraphicsResourceAccess.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsResource.hpp>
#include <NovelRT/Graphics/Vulkan/Utilities/Vma.hpp>
#include <NovelRT/Utilities/Span.hpp>

#include <memory>

#include <vulkan/vulkan.h>

namespace NovelRT::Graphics::Vulkan
{
    struct VulkanGraphicsBackend;
}

namespace NovelRT::Graphics
{
    template<template <typename> typename TResource, typename TBackend> class GraphicsResourceMemoryRegion;

    template <>
    class GraphicsBuffer<Vulkan::VulkanGraphicsBackend> final
        : public GraphicsResource<Vulkan::VulkanGraphicsBackend>
    {
    private:
        VkBuffer _vulkanBuffer;
        size_t _mappedMemoryRegions;
        GraphicsResourceAccess _cpuAccess;
        GraphicsBufferKind _kind;

    public:
        //NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        std::shared_ptr<GraphicsBuffer<Vulkan::VulkanGraphicsBackend>> shared_from_this();
        //NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        std::shared_ptr<const GraphicsBuffer<Vulkan::VulkanGraphicsBackend>> shared_from_this() const;

        GraphicsBuffer(
            std::weak_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> graphicsDevice,
            std::shared_ptr<GraphicsMemoryAllocator<Vulkan::VulkanGraphicsBackend>> allocator,
            const GraphicsBufferCreateInfo& createInfo,
            VmaAllocation allocation,
            VmaAllocationInfo allocationInfo,
            VkBuffer vulkanBuffer);

        ~GraphicsBuffer() noexcept final;

        [[nodiscard]] GraphicsResourceAccess GetAccess() const noexcept;
        [[nodiscard]] GraphicsBufferKind GetKind() const noexcept;

        [[nodiscard]] NovelRT::Utilities::Span<uint8_t> MapBytes(size_t rangeOffset, size_t rangeLength) final;

        [[nodiscard]] NovelRT::Utilities::Span<const uint8_t> MapBytesForRead(size_t rangeOffset, size_t rangeLength) final;

        void UnmapBytes() final;

        void UnmapBytesAndWrite() final;
        void UnmapBytesAndWrite(size_t writtenRangeOffset, size_t writtenRangeLength) final;

        void UnmapAndWrite(const GraphicsResourceMemoryRegion<GraphicsBuffer, Vulkan::VulkanGraphicsBackend>* memoryRegion);

        [[nodiscard]] VkBuffer GetVulkanBuffer() const noexcept;
    };
}
