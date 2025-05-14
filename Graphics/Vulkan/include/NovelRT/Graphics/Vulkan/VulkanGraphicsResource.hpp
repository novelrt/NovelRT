#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsResourceAccess.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsResourceMemoryRegion.hpp>
#include <vk_mem_alloc.h>
#include <tuple>

namespace NovelRT::Graphics::Vulkan
{
    class VulkanGraphicsDevice;
    class VulkanGraphicsMemoryAllocator;

    class VulkanGraphicsResource : public std::enable_shared_from_this<VulkanGraphicsResource>
    {
    private:
        std::shared_ptr<VulkanGraphicsMemoryAllocator> _allocator;
        std::shared_ptr<VulkanGraphicsDevice> _graphicsDevice;
        VmaAllocation _allocation;
        VmaAllocationInfo _allocationInfo;
        VmaVirtualBlock _virtualBlock;
        [[nodiscard]] std::tuple<VmaVirtualAllocation, VkDeviceSize> GetVirtualAllocation(size_t size, size_t alignment);

    protected:
        [[nodiscard]] virtual std::shared_ptr<VulkanGraphicsResourceMemoryRegion<VulkanGraphicsResource>> AllocateInternal(VmaVirtualAllocation allocation, VkDeviceSize offset) = 0;

    public:
        VulkanGraphicsResource(std::shared_ptr<VulkanGraphicsDevice> graphicsDevice,
                               std::shared_ptr<VulkanGraphicsMemoryAllocator> allocator,
                               GraphicsResourceAccess cpuAccess,
                               VmaAllocation allocation,
                               VmaAllocationInfo allocationInfo);

        virtual ~VulkanGraphicsResource() noexcept = default;

        [[nodiscard]] std::shared_ptr<VulkanGraphicsMemoryAllocator> GetAllocator() const noexcept;

        [[nodiscard]] std::shared_ptr<VulkanGraphicsDevice> GetDevice() const noexcept;

        [[nodiscard]] size_t GetDeviceMemoryOffset() const noexcept;

        [[nodiscard]] size_t GetSize() const noexcept;

        [[nodiscard]] std::shared_ptr<VulkanGraphicsResourceMemoryRegion<VulkanGraphicsResource>> Allocate(size_t size, size_t alignment);

        [[nodiscard]] virtual NovelRT::Utilities::Misc::Span<uint8_t> MapBytes(size_t rangeOffset, size_t rangeLength) = 0;

        [[nodiscard]] virtual NovelRT::Utilities::Misc::Span<const uint8_t> MapBytesForRead(size_t rangeOffset, size_t rangeLength) = 0;

        virtual void UnmapBytes() = 0;

        virtual void UnmapBytesAndWrite(size_t writtenRangeOffset, size_t writtenRangeLength) = 0;

        [[nodiscard]] VmaAllocation GetAllocation() const noexcept;

        [[nodiscard]] const VmaAllocationInfo& GetAllocationInfo() const noexcept;

        [[nodiscard]] VmaVirtualBlock GetVirtualBlock() const noexcept;
    };
}
