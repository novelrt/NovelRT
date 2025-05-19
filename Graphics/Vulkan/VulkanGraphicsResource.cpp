// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InitialisationFailureException.hpp>
#include <NovelRT/Exceptions/OutOfMemoryException.hpp>
#include <NovelRT/Graphics/GraphicsMemoryAllocator.hpp>
#include <NovelRT/Graphics/GraphicsResource.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsBackendTraits.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsMemoryAllocator.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsResource.hpp>
#include <NovelRT/Utilities/Macros.hpp>

#include <string>

namespace NovelRT::Graphics::Vulkan
{
    std::tuple<VmaVirtualAllocation, VmaVirtualAllocationInfo> VulkanGraphicsResource::GetVirtualAllocation(size_t size, size_t alignment)
    {
        VmaVirtualAllocationCreateInfo allocInfo{};
        allocInfo.size = size;
        allocInfo.alignment = alignment;

        VmaVirtualAllocation allocHandle = VK_NULL_HANDLE;
        VkDeviceSize offset{};

        const VkResult allocResult = vmaVirtualAllocate(_virtualBlock, &allocInfo, &allocHandle, &offset);

        if (allocResult != VK_SUCCESS)
        {
            throw Exceptions::OutOfMemoryException("Unable to allocate additional memory in the Vulkan graphics resource.");
        }

        VmaVirtualAllocationInfo allocResultInfo{};
        vmaGetVirtualAllocationInfo(GetVirtualBlock(), allocHandle, &allocResultInfo);

        return std::make_tuple(allocHandle, allocResultInfo);
    }

    VulkanGraphicsResource::VulkanGraphicsResource(VulkanGraphicsDevice* graphicsDevice,
                                                   VulkanGraphicsMemoryAllocator* allocator,
                                                   GraphicsResourceAccess cpuAccess,
                                                   VmaAllocation allocation,
                                                   VmaAllocationInfo allocationInfo)
        : _allocator(allocator),
          _device(graphicsDevice),
          _allocation(allocation),
          _allocationInfo(allocationInfo),
          _virtualBlock(VK_NULL_HANDLE)
    {
        unused(cpuAccess);

        VmaVirtualBlockCreateInfo createInfo{};
        createInfo.size = GetSize();

        const VkResult result = vmaCreateVirtualBlock(&createInfo, &_virtualBlock);

        if (result != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to create virtual memory block for VkBuffer",
                                                             std::to_string(result));
        }
    }

    size_t VulkanGraphicsResource::GetDeviceMemoryOffset() const noexcept
    {
        return _allocationInfo.offset;
    }

    size_t VulkanGraphicsResource::GetSize() const noexcept
    {
        return _allocationInfo.size;
    }

    std::unique_ptr<VulkanGraphicsResourceMemoryRegion<VulkanGraphicsResource>> VulkanGraphicsResource::Allocate(size_t size, size_t alignment)
    {
        auto [allocation, info] = GetVirtualAllocation(size, alignment);
        return AllocateInternal(allocation, info);
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

template class NovelRT::Graphics::GraphicsResource<NovelRT::Graphics::Vulkan::VulkanGraphicsBackend>;
