#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsBuffer.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsResource.hpp>
#include <memory>
#include <vk_mem_alloc.h>

namespace NovelRT::Graphics::Vulkan
{
    class VulkanGraphicsDevice;
    class VulkanGraphicsMemoryAllocator;
    template<typename TResource> class VulkanGraphicsResourceMemoryRegion;

    class VulkanGraphicsBuffer final : public VulkanGraphicsResource, public GraphicsBuffer
    {
    private:
        VkBuffer _vulkanBuffer;
        size_t _subAllocations;

    protected:
        [[nodiscard]] std::shared_ptr<VulkanGraphicsResourceMemoryRegionBase> VulkanAllocateInternal(VmaVirtualAllocation allocation, VkDeviceSize offset) final;

    public:
        VulkanGraphicsBuffer(std::shared_ptr<VulkanGraphicsDevice> graphicsDevice,
                             std::shared_ptr<VulkanGraphicsMemoryAllocator> allocator,
                             GraphicsResourceAccess cpuAccess,
                             GraphicsBufferKind kind,
                             VmaAllocation allocation,
                             VmaAllocationInfo allocationInfo,
                             size_t subAllocations,
                             VkBuffer vulkanBuffer);

        ~VulkanGraphicsBuffer() noexcept final;

        [[nodiscard]] NovelRT::Utilities::Misc::Span<uint8_t> MapBytes(size_t rangeOffset, size_t rangeLength) final;

        [[nodiscard]] NovelRT::Utilities::Misc::Span<const uint8_t> MapBytesForRead(size_t rangeOffset,
                                                                                    size_t rangeLength) final;

        void UnmapBytes() final;

        void UnmapBytesAndWrite(size_t writtenRangeOffset, size_t writtenRangeLength) final;

        [[nodiscard]] VkBuffer GetVulkanBuffer() const noexcept;    
    };
}