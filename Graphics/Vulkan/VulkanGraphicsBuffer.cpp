// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InvalidOperationException.hpp>
#include <NovelRT/Graphics/GraphicsBuffer.hpp>
#include <NovelRT/Graphics/GraphicsMemoryAllocator.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsBackendTraits.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsBuffer.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsMemoryAllocator.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsResource.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsResourceMemoryRegion.hpp>
#include <NovelRT/Utilities/Macros.hpp>

namespace NovelRT::Graphics::Vulkan
{
    std::unique_ptr<VulkanGraphicsResourceMemoryRegion<VulkanGraphicsResource>> VulkanGraphicsBuffer::AllocateInternal(
        VmaVirtualAllocation allocation,
        VmaVirtualAllocationInfo info)
    {
        return std::make_unique<VulkanGraphicsResourceMemoryRegion<VulkanGraphicsBuffer>>(GetDevice(), this, allocation, info);
    }

    void VulkanGraphicsBuffer::FreeInternal(VulkanGraphicsResourceMemoryRegion<VulkanGraphicsResource>& region)
    {
        unused(region);
        // TODO: Not sure if we need to support this, but since we do so for allocation, at least having this for freeing makes sense.
    }

    VulkanGraphicsBuffer::VulkanGraphicsBuffer(VulkanGraphicsDevice* graphicsDevice,
                                               VulkanGraphicsMemoryAllocator* allocator,
                                               GraphicsResourceAccess cpuAccess,
                                               GraphicsBufferKind kind,
                                               VmaAllocation allocation,
                                               VmaAllocationInfo allocationInfo,
                                               VkBuffer vulkanBuffer)
        : VulkanGraphicsResource(graphicsDevice, allocator, cpuAccess, allocation, allocationInfo)
        , _vulkanBuffer(vulkanBuffer)
        , _mappedMemoryRegions(0)
        , _cpuAccess(cpuAccess)
        , _kind(kind)
    {}

    VulkanGraphicsBuffer::~VulkanGraphicsBuffer() noexcept
    {
        auto* allocator = GetAllocator()->GetVmaAllocator();
        auto* allocation = GetAllocation();

        assert_message(_mappedMemoryRegions == 0, "Attempted to destroy a VkBuffer containing mapped regions.");


        vmaDestroyBuffer(allocator, GetVulkanBuffer(), allocation);
    }

    Utilities::Span<uint8_t> VulkanGraphicsBuffer::MapBytes(size_t rangeOffset, size_t rangeLength)
    {
        const size_t sizeOfBuffer = GetAllocationInfo().size;
        const size_t rangeValidationValue = sizeOfBuffer - rangeOffset;

        if (rangeValidationValue < rangeLength)
        {
            throw Exceptions::InvalidOperationException(
                "Attempted to map a subrange of a VkBuffer that exceeded the VkBuffer's size.");
        }

        void* data = nullptr;
        const VkResult result = vmaMapMemory(GetAllocator()->GetVmaAllocator(), GetAllocation(), &data);

        if (result != VK_SUCCESS)
        {
            // TODO: Make this a real exception
            throw std::runtime_error("Failed to map Vulkan memory to the CPU. Reason: " + std::to_string(result));
        }

        _mappedMemoryRegions++;

        return {static_cast<uint8_t*>(data) + rangeOffset, rangeLength};
    }

    Utilities::Span<const uint8_t> VulkanGraphicsBuffer::MapBytesForRead(size_t rangeOffset, size_t rangeLength)
    {
        const size_t sizeOfBuffer = GetAllocationInfo().size;
        const size_t rangeValidationValue = sizeOfBuffer - rangeOffset;

        if (rangeValidationValue < rangeLength)
        {
            throw Exceptions::InvalidOperationException(
                "Attempted to map a subrange of a VkBuffer that exceeded the VkBuffer's size.");
        }

        VmaAllocator allocator = GetAllocator()->GetVmaAllocator();
        VmaAllocation allocation = GetAllocation();

        void* data = nullptr;
        const VkResult mapResult = vmaMapMemory(allocator, allocation, &data);

        if (mapResult != VK_SUCCESS)
        {
            // TODO: Make this a real exception
            throw std::runtime_error("Failed to map Vulkan memory to the CPU. Reason: " + std::to_string(mapResult));
        }

        const VkResult invalidateResult = vmaInvalidateAllocation(allocator, allocation, rangeOffset, rangeLength);

        if (invalidateResult != VK_SUCCESS)
        {
            // TODO: Make this a real exception
            throw std::runtime_error("Failed to invalidate mapped memory. Reason: " + std::to_string(mapResult));
        }

        _mappedMemoryRegions++;

        return {static_cast<const uint8_t*>(data), rangeLength};
    }

    void VulkanGraphicsBuffer::UnmapBytes()
    {
        if (_mappedMemoryRegions == 0)
        {
            throw Exceptions::InvalidOperationException("Attempted to unmap region of buffer when no memory map was created.");
        }

        _mappedMemoryRegions--;

        vmaUnmapMemory(GetAllocator()->GetVmaAllocator(), GetAllocation());
    }

    void VulkanGraphicsBuffer::UnmapBytesAndWrite(size_t writtenRangeOffset, size_t writtenRangeLength)
    {
        if (_mappedMemoryRegions == 0)
        {
            throw Exceptions::InvalidOperationException("Attempted to unmap region of buffer when no memory map was created.");
        }

        const size_t sizeOfBuffer = GetAllocationInfo().size;
        const size_t rangeValidationValue = sizeOfBuffer - writtenRangeOffset;

        if (rangeValidationValue < writtenRangeLength)
        {
            throw Exceptions::InvalidOperationException(
                "Attempted to write a subrange of a VkBuffer that exceeded the VkBuffer's size.");
        }

        auto* allocator = GetAllocator()->GetVmaAllocator();
        auto* allocation = GetAllocation();

        const VkResult result = vmaFlushAllocation(allocator, allocation, writtenRangeOffset, writtenRangeLength);

        if (result != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to write VkBuffer subrange to GPU memory. Reason: " +
                                     std::to_string(result));
        }

        _mappedMemoryRegions--;

        vmaUnmapMemory(allocator, allocation);
    }

    VkBuffer VulkanGraphicsBuffer::GetVulkanBuffer() const noexcept
    {
        return _vulkanBuffer;
    }
}

template class NovelRT::Graphics::GraphicsBuffer<NovelRT::Graphics::Vulkan::VulkanGraphicsBackend>;
