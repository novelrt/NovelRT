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
        : GraphicsBuffer(std::move(device), kind, std::move(blockRegion), cpuAccess), _vulkanBuffer(buffer), _mappingCount(0)
    {
        VkResult bindResult = vkBindBufferMemory(GetAllocator()->GetDevice()->GetVulkanDevice(), _vulkanBuffer,
                                                 GetBlock()->GetVulkanDeviceMemory(), GetBlockRegion().GetOffset());

        if (bindResult != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to bind the VkBuffer!", bindResult);
        }
    }

    gsl::span<uint8_t> VulkanGraphicsBuffer::MapUntyped(size_t rangeOffset, size_t rangeLength)
    {
        std::shared_ptr<VulkanGraphicsDevice> device = GetDevice();

        VkDevice vulkanDevice = device->GetVulkanDevice();
        VkDeviceMemory vulkanDeviceMemory = GetBlock()->GetVulkanDeviceMemory();

        void* pDestination = nullptr;
        
        /*
        uint64_t nonCoherentAtomSize =
            device->GetAdapter()->GetVulkanPhysicalDeviceProperties().limits.nonCoherentAtomSize;
        */

        VkResult mapMemoryResult =
            vkMapMemory(vulkanDevice, vulkanDeviceMemory, 0, VK_WHOLE_SIZE, 0, &pDestination);

        if (mapMemoryResult != VK_SUCCESS)
        {
            // TODO: Make a real exception.
            throw std::runtime_error("Failed to map Vulkan memory to the CPU! Reason: " +
                                     std::to_string(mapMemoryResult));
        }

/*
        auto returnPtr = reinterpret_cast<uint8_t*>(pDestination);
        returnPtr = reinterpret_cast<uint8_t*>(Maths::Utilities::AlignDown(reinterpret_cast<uintptr_t>(returnPtr) + rangeOffset, nonCoherentAtomSize));
        return gsl::span<uint8_t>(returnPtr, Maths::Utilities::AlignUp(rangeLength, nonCoherentAtomSize));
        */ //TODO: DO WE WANT THIS???

        auto returnPtr = reinterpret_cast<uint8_t*>(pDestination);
        returnPtr += rangeOffset;
        return gsl::span<uint8_t>(returnPtr, rangeLength);
    }

    gsl::span<const uint8_t> VulkanGraphicsBuffer::MapForReadUntyped(size_t readRangeOffset, size_t readRangeLength)
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

        auto returnPtr = reinterpret_cast<uint8_t*>(pDestination);
        returnPtr += readRangeOffset;
        return gsl::span<const uint8_t>(returnPtr, readRangeLength);
    }

    void VulkanGraphicsBuffer::Unmap(size_t writtenRangeOffset, size_t writtenRangeLength)
    {
        unused(writtenRangeLength);
        unused(writtenRangeOffset); //TODO: Implement this
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
