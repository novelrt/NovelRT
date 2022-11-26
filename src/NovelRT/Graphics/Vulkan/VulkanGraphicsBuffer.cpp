// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include "NovelRT/Graphics/Vulkan/Graphics.Vulkan.h"

namespace NovelRT::Graphics::Vulkan
{
    VulkanGraphicsDevice* VulkanGraphicsBuffer::GetDeviceInternal() const noexcept
    {
        // TODO: This feels like it might be a perf issue later.
        return dynamic_cast<VulkanGraphicsDevice*>(GraphicsDeviceObject::GetDevice().get());
    }

    VulkanGraphicsBuffer::VulkanGraphicsBuffer(std::shared_ptr<VulkanGraphicsDevice> device,
                                               GraphicsBufferKind kind,
                                               GraphicsMemoryRegion<GraphicsMemoryBlock> blockRegion,
                                               GraphicsResourceAccess cpuAccess,
                                               VkBuffer buffer)
        : GraphicsBuffer(std::move(device), kind, std::move(blockRegion), cpuAccess), _vulkanBuffer(buffer)
    {
        VkResult bindResult = vkBindBufferMemory(GetAllocator()->GetDevice()->GetVulkanDevice(), _vulkanBuffer,
                                                 GetBlock()->GetVulkanDeviceMemory(), GetBlockRegion().GetOffset());

        if (bindResult != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to bind the VkBuffer!", bindResult);
        }
    }

    void* VulkanGraphicsBuffer::MapUntyped()
    {
        std::shared_ptr<VulkanGraphicsDevice> device = GetDevice();

        VkDevice vulkanDevice = device->GetVulkanDevice();
        VkDeviceMemory vulkanDeviceMemory = GetBlock()->GetVulkanDeviceMemory();

        void* pDestination = nullptr;

        VkResult mapMemoryResult =
            vkMapMemory(vulkanDevice, vulkanDeviceMemory, GetOffset(), GetSize(), 0, &pDestination);

        if (mapMemoryResult != VK_SUCCESS)
        {
            // TODO: Make a real exception.
            throw std::runtime_error("Failed to map Vulkan memory to the CPU!");
        }

        return pDestination;
    }

    void* VulkanGraphicsBuffer::MapUntyped(size_t rangeOffset, size_t rangeLength)
    {
        std::shared_ptr<VulkanGraphicsDevice> device = GetDevice();

        VkDevice vulkanDevice = device->GetVulkanDevice();
        VkDeviceMemory vulkanDeviceMemory = GetBlock()->GetVulkanDeviceMemory();

        void* pDestination = nullptr;
        
        uint64_t nonCoherentAtomSize =
            device->GetAdapter()->GetVulkanPhysicalDeviceProperties().limits.nonCoherentAtomSize;

        VkResult mapMemoryResult =
            vkMapMemory(vulkanDevice, vulkanDeviceMemory, Maths::Utilities::AlignDown(GetOffset() + rangeOffset, nonCoherentAtomSize), Maths::Utilities::AlignUp(rangeLength + nonCoherentAtomSize, nonCoherentAtomSize), 0, &pDestination);

        if (mapMemoryResult != VK_SUCCESS)
        {
            // TODO: Make a real exception.
            throw std::runtime_error("Failed to map Vulkan memory to the CPU! Reason: " +
                                     std::to_string(mapMemoryResult));
        }

        return reinterpret_cast<uint8_t*>(pDestination);
    }

    const void* VulkanGraphicsBuffer::MapForReadUntyped()
    {
        std::shared_ptr<VulkanGraphicsDevice> device = GetDevice();

        VkDevice vulkanDevice = device->GetVulkanDevice();
        VkDeviceMemory vulkanDeviceMemory = GetBlock()->GetVulkanDeviceMemory();

        void* pDestination = nullptr;

        VkResult mapMemoryResult =
            vkMapMemory(vulkanDevice, vulkanDeviceMemory, GetOffset(), GetSize(), 0, &pDestination);

        if (mapMemoryResult != VK_SUCCESS)
        {
            // TODO: Make a real exception.
            throw std::runtime_error("Failed to map Vulkan memory to the CPU! Reason: " +
                                     std::to_string(mapMemoryResult));
        }

        uint64_t nonCoherentAtomSize =
            device->GetAdapter()->GetVulkanPhysicalDeviceProperties().limits.nonCoherentAtomSize;

        size_t offset = GetOffset();
        size_t size = (GetSize() + nonCoherentAtomSize - 1) & ~(nonCoherentAtomSize - 1);

        VkMappedMemoryRange mappedMemoryRange{};
        mappedMemoryRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
        mappedMemoryRange.memory = vulkanDeviceMemory;
        mappedMemoryRange.offset = offset;
        mappedMemoryRange.size = size;

        VkResult invalidateMappedMemoryRangesResult =
            vkInvalidateMappedMemoryRanges(device->GetVulkanDevice(), 1, &mappedMemoryRange);

        if (invalidateMappedMemoryRangesResult != VK_SUCCESS)
        {
            // TODO: Make a real exception.
            throw std::runtime_error("Failed to map the Vulkan memory for read only!");
        }

        return pDestination;
    }

    const void* VulkanGraphicsBuffer::MapForReadUntyped(size_t readRangeOffset, size_t readRangeLength)
    {
        std::shared_ptr<VulkanGraphicsDevice> device = GetDevice();

        VkDevice vulkanDevice = device->GetVulkanDevice();
        VkDeviceMemory vulkanDeviceMemory = GetBlock()->GetVulkanDeviceMemory();

        void* pDestination = nullptr;

        VkResult mapMemoryResult =
            vkMapMemory(vulkanDevice, vulkanDeviceMemory, GetOffset(), GetSize(), 0, &pDestination);

        if (mapMemoryResult != VK_SUCCESS)
        {
            // TODO: Make a real exception.
            throw std::runtime_error("Failed to map Vulkan memory to the CPU!");
        }

        uint64_t nonCoherentAtomSize =
            device->GetAdapter()->GetVulkanPhysicalDeviceProperties().limits.nonCoherentAtomSize;

        size_t offset = Maths::Utilities::AlignDown(GetOffset() + readRangeOffset, nonCoherentAtomSize);
        size_t size = Maths::Utilities::AlignUp(readRangeLength, nonCoherentAtomSize);

        VkMappedMemoryRange mappedMemoryRange{};
        mappedMemoryRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
        mappedMemoryRange.memory = vulkanDeviceMemory;
        mappedMemoryRange.offset = offset;
        mappedMemoryRange.size = size;

        VkResult invalidateMappedMemoryRangesResult =
            vkInvalidateMappedMemoryRanges(device->GetVulkanDevice(), 1, &mappedMemoryRange);

        if (invalidateMappedMemoryRangesResult != VK_SUCCESS)
        {
            // TODO: Make a real exception.
            throw std::runtime_error("Failed to map the Vulkan memory for read only!");
        }

        return (reinterpret_cast<uint8_t*>(pDestination) + readRangeOffset);
    }

    void VulkanGraphicsBuffer::Unmap()
    {
        std::shared_ptr<VulkanGraphicsDevice> device = GetDevice();

        VkDevice vulkanDevice = device->GetVulkanDevice();
        VkDeviceMemory vulkanDeviceMemory = GetBlock()->GetVulkanDeviceMemory();

        vkUnmapMemory(vulkanDevice, vulkanDeviceMemory);
    }

    void VulkanGraphicsBuffer::UnmapAndWrite()
    {
        std::shared_ptr<VulkanGraphicsDevice> device = GetDevice();

        VkDevice vulkanDevice = device->GetVulkanDevice();
        VkDeviceMemory vulkanDeviceMemory = GetBlock()->GetVulkanDeviceMemory();

        uint64_t nonCoherentAtomSize =
            device->GetAdapter()->GetVulkanPhysicalDeviceProperties().limits.nonCoherentAtomSize;

        size_t offset = Maths::Utilities::AlignDown(GetOffset(), nonCoherentAtomSize);
        size_t size = Maths::Utilities::AlignUp(GetSize(), nonCoherentAtomSize);

        VkMappedMemoryRange mappedMemoryRange{};
        mappedMemoryRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
        mappedMemoryRange.memory = vulkanDeviceMemory;
        mappedMemoryRange.offset = offset;
        mappedMemoryRange.size = size;

        VkResult flushMappedMemoryRangesResult = vkFlushMappedMemoryRanges(vulkanDevice, 1, &mappedMemoryRange);

        if (flushMappedMemoryRangesResult != VK_SUCCESS)
        {
            // TODO: Make a real exception.
            throw std::runtime_error("Failed to flush the written changes to the Vulkan memory!");
        }

        vkUnmapMemory(vulkanDevice, vulkanDeviceMemory);
    }

    void VulkanGraphicsBuffer::UnmapAndWrite(size_t writtenRangeOffset, size_t writtenRangeLength)
    {
        std::shared_ptr<VulkanGraphicsDevice> device = GetDevice();

        VkDevice vulkanDevice = device->GetVulkanDevice();
        VkDeviceMemory vulkanDeviceMemory = GetBlock()->GetVulkanDeviceMemory();

        uint64_t nonCoherentAtomSize =
            device->GetAdapter()->GetVulkanPhysicalDeviceProperties().limits.nonCoherentAtomSize;

        size_t offset = Maths::Utilities::AlignDown(GetOffset() + writtenRangeOffset, nonCoherentAtomSize);
        size_t size = Maths::Utilities::AlignUp(writtenRangeLength + nonCoherentAtomSize, nonCoherentAtomSize);

        VkMappedMemoryRange mappedMemoryRange{};
        mappedMemoryRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
        mappedMemoryRange.memory = vulkanDeviceMemory;
        mappedMemoryRange.offset = offset;
        mappedMemoryRange.size = size;

        VkResult flushMappedMemoryRangesResult = vkFlushMappedMemoryRanges(vulkanDevice, 1, &mappedMemoryRange);

        if (flushMappedMemoryRangesResult != VK_SUCCESS)
        {
            // TODO: Make a real exception.
            throw std::runtime_error("Failed to flush the written changes to the Vulkan memory!");
        }

        vkUnmapMemory(vulkanDevice, vulkanDeviceMemory);
    }

    VulkanGraphicsBuffer::~VulkanGraphicsBuffer()
    {
        if (_vulkanBuffer != VK_NULL_HANDLE)
        {
            vkDestroyBuffer(GetDevice()->GetVulkanDevice(), GetVulkanBuffer(), nullptr);
        }
        GetBlockRegion().GetCollection()->Free(GetBlockRegion());
    }
} // namespace NovelRT::Graphics::Vulkan
