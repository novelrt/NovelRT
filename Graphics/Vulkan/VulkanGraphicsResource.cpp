// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InitialisationFailureException.h>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsMemoryAllocator.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsResource.hpp>
#include <string>

namespace NovelRT::Graphics::Vulkan
{
    std::tuple<VmaVirtualAllocation, VkDeviceSize> VulkanGraphicsResource::GetVirtualAllocation(size_t size, size_t alignment)
    {
        VmaVirtualAllocationCreateInfo allocInfo{};
        allocInfo.size = size;
        allocInfo.alignment = alignment;

        VmaVirtualAllocation allocHandle = VK_NULL_HANDLE;
        VkDeviceSize offset{};

        VkResult allocResult = vmaVirtualAllocate(_virtualBlock, &allocInfo, &allocHandle, &offset);

        if (allocResult != VK_SUCCESS)
        {
            throw Exceptions::OutOfMemoryException("Unable to allocate additional memory in the Vulkan graphics resource.");
        }

        return std::make_tuple(allocHandle, offset);
    }

    VulkanGraphicsResource::VulkanGraphicsResource(std::shared_ptr<VulkanGraphicsDevice> graphicsDevice,
                                                   std::shared_ptr<VulkanGraphicsMemoryAllocator> allocator,
                                                   GraphicsResourceAccess cpuAccess,
                                                   VmaAllocation allocation,
                                                   VmaAllocationInfo allocationInfo)
        : _allocator(allocator),
          _graphicsDevice(graphicsDevice),
          _allocation(allocation),
          _allocationInfo(allocationInfo),
          _virtualBlock(VK_NULL_HANDLE)
    {
        unused(cpuAccess);

        VmaVirtualBlockCreateInfo createInfo{};
        createInfo.size = GetSize();

        VkResult result = vmaCreateVirtualBlock(&createInfo, &_virtualBlock);

        if (result != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to create virtual memory block for VkBuffer",
                                                             std::to_string(result));
        }
    }

    std::shared_ptr<VulkanGraphicsMemoryAllocator> VulkanGraphicsResource::GetAllocator() const noexcept
    {
        return _allocator;
    }

    std::shared_ptr<VulkanGraphicsDevice> VulkanGraphicsResource::GetDevice() const noexcept
    {
        return _graphicsDevice;
    }

    size_t VulkanGraphicsResource::GetDeviceMemoryOffset() const noexcept
    {
        return _allocationInfo.offset;
    }

    size_t VulkanGraphicsResource::GetSize() const noexcept
    {
        return _allocationInfo.size;
    }

    std::shared_ptr<VulkanGraphicsResourceMemoryRegion<VulkanGraphicsResource>> VulkanGraphicsResource::Allocate(size_t size, size_t alignment)
    {
        auto [allocation, offset] = GetVirtualAllocation(size, alignment);
        return AllocateInternal(allocation, offset);
    }

    VmaAllocation VulkanGraphicsResource::GetAllocation() const noexcept
    {
        return _allocation;
    }

    const VmaAllocationInfo& VulkanGraphicsResource::GetAllocationInfo() const noexcept
    {
        return _allocationInfo;
    }

    VmaVirtualBlock VulkanGraphicsResource::GetVirtualBlock() const noexcept
    {
        return _virtualBlock;
    }
}
