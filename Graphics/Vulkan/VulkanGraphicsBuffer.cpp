// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InvalidOperationException.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsBuffer.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsMemoryAllocator.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsResource.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsResourceMemoryRegion.hpp>
#include <NovelRT/Utilities/Macros.hpp>

namespace NovelRT::Graphics
{
    using VulkanGraphicsBuffer = GraphicsBuffer<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsDevice = GraphicsDevice<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsDeviceObject = GraphicsDeviceObject<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsMemoryAllocator = GraphicsMemoryAllocator<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsResource = GraphicsResource<Vulkan::VulkanGraphicsBackend>;
    template <template <typename> typename TResource>
    using VulkanGraphicsResourceMemoryRegion = GraphicsResourceMemoryRegion<TResource, Vulkan::VulkanGraphicsBackend>;

    //NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
    std::shared_ptr<VulkanGraphicsBuffer> VulkanGraphicsBuffer::shared_from_this()
    {
        return std::static_pointer_cast<VulkanGraphicsBuffer>(GraphicsResource::shared_from_this());
    }

    //NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
    std::shared_ptr<const VulkanGraphicsBuffer> VulkanGraphicsBuffer::shared_from_this() const
    {
        return std::static_pointer_cast<const VulkanGraphicsBuffer>(GraphicsResource::shared_from_this());
    }

    VulkanGraphicsBuffer::GraphicsBuffer(std::weak_ptr<VulkanGraphicsDevice> graphicsDevice,
        std::shared_ptr<VulkanGraphicsMemoryAllocator> allocator,
        const GraphicsBufferCreateInfo& createInfo,
        VmaAllocation allocation,
        VmaAllocationInfo allocationInfo,
        VkBuffer vulkanBuffer)
        : VulkanGraphicsResource(graphicsDevice, allocator, createInfo.cpuAccessKind, allocation, allocationInfo)
        , _vulkanBuffer(vulkanBuffer)
        , _mappedMemoryRegions(0)
        , _cpuAccess(createInfo.cpuAccessKind)
        , _kind(createInfo.bufferKind)
    {}

    VulkanGraphicsBuffer::~GraphicsBuffer() noexcept
    {
        assert_message(_mappedMemoryRegions == 0, "Attempted to destroy a VkBuffer containing mapped regions.");

        auto allocator = GetAllocator().lock();
        auto vmaAllocator = allocator->GetVmaAllocator();
        auto allocation = GetAllocation();
        vmaDestroyBuffer(vmaAllocator, _vulkanBuffer, allocation);
    }

    GraphicsResourceAccess VulkanGraphicsBuffer::GetAccess() const noexcept
    {
        return _cpuAccess;
    }

    GraphicsBufferKind VulkanGraphicsBuffer::GetKind() const noexcept
    {
        return _kind;
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
        const VkResult result = vmaMapMemory(GetAllocator().lock()->GetVmaAllocator(), GetAllocation(), &data);

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

        VmaAllocator allocator = GetAllocator().lock()->GetVmaAllocator();
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

        auto allocator = GetAllocator().lock();
        vmaUnmapMemory(allocator->GetVmaAllocator(), GetAllocation());
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

        auto allocator = GetAllocator().lock();
        auto vmaAllcoator = allocator->GetVmaAllocator();
        auto allocation = GetAllocation();

        const VkResult result = vmaFlushAllocation(vmaAllcoator, allocation, writtenRangeOffset, writtenRangeLength);

        if (result != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to write VkBuffer subrange to GPU memory. Reason: " +
                                     std::to_string(result));
        }

        _mappedMemoryRegions--;

        vmaUnmapMemory(vmaAllcoator, allocation);
    }

    VkBuffer VulkanGraphicsBuffer::GetVulkanBuffer() const noexcept
    {
        return _vulkanBuffer;
    }
}
