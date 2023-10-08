// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/Vulkan/VulkanGraphicsBuffer.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsMemoryAllocator.hpp>
#include <NovelRT/Utilities/Misc.h>

namespace NovelRT::Graphics::Vulkan
{
    VulkanGraphicsBuffer::VulkanGraphicsBuffer(std::shared_ptr<VulkanGraphicsDevice> graphicsDevice,
                                               std::shared_ptr<VulkanGraphicsMemoryAllocator> allocator,
                                               GraphicsResourceAccess cpuAccess,
                                               GraphicsBufferKind kind,
                                               VmaAllocation allocation,
                                               VmaAllocationInfo allocationInfo,
                                               size_t subAllocations,
                                               VkBuffer vulkanBuffer)
        : VulkanGraphicsResource(graphicsDevice, allocator, cpuAccess, allocation, allocationInfo),
          GraphicsBuffer(graphicsDevice, allocator, cpuAccess, kind),
          _vulkanBuffer(vulkanBuffer),
          _subAllocations(subAllocations)
    {
    }

    VulkanGraphicsBuffer::~VulkanGraphicsBuffer() noexcept
    {
        auto allocator = VulkanGraphicsResource::GetAllocator()->GetVmaAllocator();
        auto allocation = GetAllocation();

        assert_message("Attempted to destroy a VkBuffer containing mapped regions.", _subAllocations != 0);

        vmaDestroyBuffer(allocator, GetVulkanBuffer(), allocation);
    }

    Utilities::Misc::Span<uint8_t> VulkanGraphicsBuffer::MapBytes(size_t rangeOffset, size_t rangeLength)
    {
        size_t sizeOfBuffer = GetAllocationInfo().size;
        size_t rangeValidationValue = sizeOfBuffer - rangeOffset;

        if (rangeValidationValue < rangeLength)
        {
            throw Exceptions::InvalidOperationException(
                "Attempted to map a subrange of a VkBuffer that exceeded the VkBuffer's size.");
        }

        void* data = nullptr;
        VkResult result =
            vmaMapMemory(VulkanGraphicsResource::GetAllocator()->GetVmaAllocator(), GetAllocation(), &data);

        if (result != VK_SUCCESS)
        {
            // TODO: Make this a real exception
            throw std::runtime_error("Failed to map Vulkan memory to the CPU. Reason: " + std::to_string(result));
        }

        _subAllocations++;

        return Utilities::Misc::Span<uint8_t>(reinterpret_cast<uint8_t*>(data) + rangeOffset, rangeLength);
    }

    Utilities::Misc::Span<const uint8_t> VulkanGraphicsBuffer::MapBytesForRead(size_t rangeOffset, size_t rangeLength)
    {
        size_t sizeOfBuffer = GetAllocationInfo().size;
        size_t rangeValidationValue = sizeOfBuffer - rangeOffset;

        if (rangeValidationValue < rangeLength)
        {
            throw Exceptions::InvalidOperationException(
                "Attempted to map a subrange of a VkBuffer that exceeded the VkBuffer's size.");
        }

        VmaAllocator allocator = VulkanGraphicsResource::GetAllocator()->GetVmaAllocator();
        VmaAllocation allocation = GetAllocation();

        void* data = nullptr;
        VkResult mapResult = vmaMapMemory(allocator, allocation, &data);

        if (mapResult != VK_SUCCESS)
        {
            // TODO: Make this a real exception
            throw std::runtime_error("Failed to map Vulkan memory to the CPU. Reason: " + std::to_string(mapResult));
        }

        VkResult invalidateResult = vmaInvalidateAllocation(allocator, allocation, rangeOffset, rangeLength);

        if (invalidateResult != VK_SUCCESS)
        {
            // TODO: Make this a real exception
            throw std::runtime_error("Failed to invalidate mapped memory. Reason: " + std::to_string(mapResult));
        }

        return Utilities::Misc::Span<const uint8_t>(reinterpret_cast<const uint8_t*>(data), rangeLength);
    }

    void VulkanGraphicsBuffer::UnmapBytes()
    {
        vmaUnmapMemory(VulkanGraphicsResource::GetAllocator()->GetVmaAllocator(), GetAllocation());
    }

    void VulkanGraphicsBuffer::UnmapBytesAndWrite(size_t writtenRangeOffset, size_t writtenRangeLength)
    {
        size_t sizeOfBuffer = GetAllocationInfo().size;
        size_t rangeValidationValue = sizeOfBuffer - writtenRangeOffset;

        if (rangeValidationValue < writtenRangeLength)
        {
            throw Exceptions::InvalidOperationException(
                "Attempted to write a subrange of a VkBuffer that exceeded the VkBuffer's size.");
        }

        auto allocator = VulkanGraphicsResource::GetAllocator()->GetVmaAllocator();
        auto allocation = GetAllocation();

        VkResult result = vmaFlushAllocation(allocator, allocation, writtenRangeOffset, writtenRangeLength);

        if (result != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to write VkBuffer subrange to GPU memory. Reason: " +
                                     std::to_string(result));
        }

        vmaUnmapMemory(allocator, allocation);
    }

    VkBuffer VulkanGraphicsBuffer::GetVulkanBuffer() const noexcept
    {
        return _vulkanBuffer;
    }
}