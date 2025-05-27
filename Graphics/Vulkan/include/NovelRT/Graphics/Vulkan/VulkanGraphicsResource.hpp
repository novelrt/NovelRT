#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsAdapter.hpp>
#include <NovelRT/Graphics/GraphicsDeviceObject.hpp>
#include <NovelRT/Graphics/GraphicsMemoryAllocator.hpp>
#include <NovelRT/Graphics/GraphicsResourceMemoryRegion.hpp>

#include <NovelRT/Graphics/GraphicsResourceAccess.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsResourceMemoryRegion.hpp>
#include <NovelRT/Graphics/Vulkan/Utilities/Vma.hpp>
#include <NovelRT/Utilities/Span.hpp>

#include <memory>
#include <tuple>

namespace NovelRT::Graphics::Vulkan
{
    struct VulkanGraphicsBackend;
}

namespace NovelRT::Graphics
{
    template <>
    class GraphicsResource<Vulkan::VulkanGraphicsBackend>
        : public GraphicsDeviceObject<Vulkan::VulkanGraphicsBackend>
    {
    private:
        std::weak_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> _device;
        std::shared_ptr<GraphicsMemoryAllocator<Vulkan::VulkanGraphicsBackend>> _allocator;

        VmaAllocation _allocation;
        VmaAllocationInfo _allocationInfo;
        VmaVirtualBlock _virtualBlock;

        GraphicsResourceAccess _cpuAccess;

    protected:
        std::tuple<VmaVirtualAllocation, VmaVirtualAllocationInfo> GetVirtualAllocation(size_t size, size_t alignment);

    public:
        //NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        std::shared_ptr<GraphicsResource<Vulkan::VulkanGraphicsBackend>> shared_from_this();
        //NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        std::shared_ptr<const GraphicsResource<Vulkan::VulkanGraphicsBackend>> shared_from_this() const;

        GraphicsResource(std::weak_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> graphicsDevice,
                         std::shared_ptr<GraphicsMemoryAllocator<Vulkan::VulkanGraphicsBackend>> allocator,
                         GraphicsResourceAccess cpuAccess,
                         VmaAllocation allocation,
                         VmaAllocationInfo allocationInfo);
        virtual ~GraphicsResource() noexcept = default;

        [[nodiscard]] std::weak_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> GetDevice() const noexcept;
        [[nodiscard]] std::shared_ptr<GraphicsMemoryAllocator<Vulkan::VulkanGraphicsBackend>> GetAllocator() const noexcept;

        [[nodiscard]] GraphicsResourceAccess GetCpuAccess() const noexcept;
        [[nodiscard]] size_t GetDeviceMemoryOffset() const noexcept;
        [[nodiscard]] size_t GetSize() const noexcept;

        [[nodiscard]] std::shared_ptr<GraphicsResourceMemoryRegion<GraphicsResource, Vulkan::VulkanGraphicsBackend>> Allocate(size_t size, size_t alignment);

        void Free(GraphicsResourceMemoryRegion<GraphicsResource, Vulkan::VulkanGraphicsBackend>& region);

        [[nodiscard]] virtual NovelRT::Utilities::Span<uint8_t> MapBytes(size_t rangeOffset, size_t rangeLength) = 0;
        [[nodiscard]] virtual NovelRT::Utilities::Span<const uint8_t> MapBytesForRead(size_t rangeOffset, size_t rangeLength) = 0;

        virtual void UnmapBytes() = 0;

        virtual void UnmapBytesAndWrite() = 0;
        virtual void UnmapBytesAndWrite(size_t writtenRangeOffset, size_t writtenRangeLength) = 0;

        void UnmapAndWrite(const GraphicsResourceMemoryRegion<GraphicsResource, Vulkan::VulkanGraphicsBackend>* memoryRegion);

        [[nodiscard]] VmaAllocation GetAllocation() const noexcept;
        [[nodiscard]] const VmaAllocationInfo& GetAllocationInfo() const noexcept;
        [[nodiscard]] VmaVirtualBlock GetVirtualBlock() const noexcept;
    };
}
