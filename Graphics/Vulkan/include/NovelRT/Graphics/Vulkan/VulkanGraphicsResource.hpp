#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsResourceAccess.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsResourceMemoryRegion.hpp>
#include <NovelRT/Graphics/Vulkan/Utilities/Vma.hpp>
#include <NovelRT/Utilities/Span.hpp>

#include <tuple>

namespace NovelRT::Graphics::Vulkan
{
    class VulkanGraphicsDevice;
    class VulkanGraphicsMemoryAllocator;

    class VulkanGraphicsResource
    {
    private:
        VulkanGraphicsMemoryAllocator* _allocator;
        VulkanGraphicsDevice* _device;

        VmaAllocation _allocation;
        VmaAllocationInfo _allocationInfo;
        VmaVirtualBlock _virtualBlock;

        [[nodiscard]] std::tuple<VmaVirtualAllocation, VmaVirtualAllocationInfo> GetVirtualAllocation(size_t size, size_t alignment);

    protected:
        [[nodiscard]] virtual std::unique_ptr<VulkanGraphicsResourceMemoryRegion<VulkanGraphicsResource>> AllocateInternal(VmaVirtualAllocation allocation, VmaVirtualAllocationInfo info) = 0;

    public:
        VulkanGraphicsResource(VulkanGraphicsDevice* graphicsDevice,
                               VulkanGraphicsMemoryAllocator* allocator,
                               GraphicsResourceAccess cpuAccess,
                               VmaAllocation allocation,
                               VmaAllocationInfo allocationInfo);

        virtual ~VulkanGraphicsResource() noexcept = default;

        [[nodiscard]] VulkanGraphicsMemoryAllocator* GetAllocator() const noexcept
        {
            return _allocator;
        }

        [[nodiscard]] VulkanGraphicsDevice* GetDevice() const noexcept
        {
            return _device;
        }

        [[nodiscard]] size_t GetDeviceMemoryOffset() const noexcept;

        [[nodiscard]] size_t GetSize() const noexcept;

        [[nodiscard]] std::unique_ptr<VulkanGraphicsResourceMemoryRegion<VulkanGraphicsResource>> Allocate(size_t size, size_t alignment);

        [[nodiscard]] virtual NovelRT::Utilities::Span<uint8_t> MapBytes(size_t rangeOffset, size_t rangeLength) = 0;

        [[nodiscard]] virtual NovelRT::Utilities::Span<const uint8_t> MapBytesForRead(size_t rangeOffset, size_t rangeLength) = 0;

        virtual void UnmapBytes() = 0;

        virtual void UnmapBytesAndWrite(size_t writtenRangeOffset, size_t writtenRangeLength) = 0;

        [[nodiscard]] VmaAllocation GetAllocation() const noexcept;

        [[nodiscard]] const VmaAllocationInfo& GetAllocationInfo() const noexcept;

        [[nodiscard]] VmaVirtualBlock GetVirtualBlock() const noexcept;
    };
}
