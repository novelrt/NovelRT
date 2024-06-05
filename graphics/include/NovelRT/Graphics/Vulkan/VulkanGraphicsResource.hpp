#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/Vulkan/VulkanGraphicsResourceMemoryRegion.hpp>
#include <vma/vk_mem_alloc.h>
#include <tuple>

namespace NovelRT::Graphics::Vulkan
{
    class VulkanGraphicsDevice;
    class VulkanGraphicsMemoryAllocator;

    class VulkanGraphicsResource
    {
    private:
        VmaAllocation _allocation;
        VmaAllocationInfo _allocationInfo;
        VmaVirtualBlock _virtualBlock;
        [[nodiscard]] std::tuple<VmaVirtualAllocation, VkDeviceSize> GetVirtualAllocation(size_t size, size_t alignment);

    protected:
        [[nodiscard]] virtual std::shared_ptr<VulkanGraphicsResourceMemoryRegionBase> VulkanAllocateInternal(VmaVirtualAllocation allocation, VkDeviceSize offset) = 0;

    public:
        VulkanGraphicsResource(std::shared_ptr<VulkanGraphicsDevice> graphicsDevice,
                               std::shared_ptr<VulkanGraphicsMemoryAllocator> allocator,
                               GraphicsResourceAccess cpuAccess,
                               VmaAllocation allocation,
                               VmaAllocationInfo allocationInfo);
 
        [[nodiscard]] std::shared_ptr<VulkanGraphicsMemoryAllocator> GetAllocator() const noexcept;

        [[nodiscard]] std::shared_ptr<VulkanGraphicsDevice> GetDevice() const noexcept;

        [[nodiscard]] size_t GetDeviceMemoryOffset() const noexcept;

        [[nodiscard]] size_t GetSize() const noexcept;
        
        [[nodiscard]] std::shared_ptr<GraphicsResourceMemoryRegionBase> Allocate(size_t size, size_t alignment);

        [[nodiscard]] std::shared_ptr<VulkanGraphicsResourceMemoryRegionBase> VulkanAllocate(size_t size, size_t alignment);

        [[nodiscard]] VmaAllocation GetAllocation() const noexcept;

        [[nodiscard]] const VmaAllocationInfo& GetAllocationInfo() const noexcept;

        [[nodiscard]] VmaVirtualBlock GetVirtualBlock() const noexcept;

        [[nodiscard]] virtual std::shared_ptr<VulkanGraphicsResourceMemoryRegionBase> VulkanAllocate(size_t size, size_t alignment);
    };
}