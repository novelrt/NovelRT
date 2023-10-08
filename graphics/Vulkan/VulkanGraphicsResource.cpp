// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsMemoryAllocator.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsResource.hpp>

namespace NovelRT::Graphics::Vulkan
{
    VulkanGraphicsResource::VulkanGraphicsResource(std::shared_ptr<VulkanGraphicsDevice> graphicsDevice,
                                                   std::shared_ptr<VulkanGraphicsMemoryAllocator> allocator,
                                                   GraphicsResourceAccess cpuAccess,
                                                   VmaAllocation allocation,
                                                   VmaAllocationInfo allocationInfo) noexcept
        : GraphicsResource(graphicsDevice, allocator, cpuAccess),
          _allocation(allocation),
          _allocationInfo(allocationInfo)
    {
    }

    std::shared_ptr<VulkanGraphicsMemoryAllocator> VulkanGraphicsResource::GetAllocator() const noexcept
    {
        return std::reinterpret_pointer_cast<VulkanGraphicsMemoryAllocator>(GraphicsResource::GetAllocator());
    }

    std::shared_ptr<VulkanGraphicsDevice> VulkanGraphicsResource::GetDevice() const noexcept
    {
        return std::reinterpret_pointer_cast<VulkanGraphicsDevice>(GraphicsResource::GetDevice());
    }

    size_t VulkanGraphicsResource::GetDeviceMemoryOffset() const noexcept
    {
        return _allocationInfo.offset;
    }

    size_t VulkanGraphicsResource::GetSize() const noexcept
    {
        return _allocationInfo.size;
    }

    const VmaAllocationInfo& VulkanGraphicsResource::GetAllocationInfo() const noexcept
    {
        return _allocationInfo;
    }

    VmaAllocation VulkanGraphicsResource::GetAllocation() const noexcept
    {
        return _allocation;
    }
}