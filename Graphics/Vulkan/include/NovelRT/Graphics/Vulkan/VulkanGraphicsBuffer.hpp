#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsBufferKind.hpp>
#include <NovelRT/Graphics/GraphicsResourceAccess.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsResource.hpp>
#include <NovelRT/Graphics/Vulkan/Utilities/Vma.hpp>
#include <NovelRT/Utilities/Span.hpp>

#include <memory>


namespace NovelRT::Graphics::Vulkan
{
    class VulkanGraphicsDevice;
    class VulkanGraphicsMemoryAllocator;
    template<typename TResource> class VulkanGraphicsResourceMemoryRegion;

    class VulkanGraphicsBuffer final : public VulkanGraphicsResource
    {
    private:
        VkBuffer _vulkanBuffer;
        size_t _mappedMemoryRegions;
        GraphicsResourceAccess _cpuAccess;
        GraphicsBufferKind _kind;

    protected:
        [[nodiscard]] std::unique_ptr<VulkanGraphicsResourceMemoryRegion<VulkanGraphicsResource>> AllocateInternal(VmaVirtualAllocation allocation, VmaVirtualAllocationInfo info) final;

        virtual void FreeInternal(VulkanGraphicsResourceMemoryRegion<VulkanGraphicsResource>& region) final;

    public:
        VulkanGraphicsBuffer(VulkanGraphicsDevice* graphicsDevice,
                             VulkanGraphicsMemoryAllocator* allocator,
                             GraphicsResourceAccess cpuAccess,
                             GraphicsBufferKind kind,
                             VmaAllocation allocation,
                             VmaAllocationInfo allocationInfo,
                             VkBuffer vulkanBuffer);

        ~VulkanGraphicsBuffer() noexcept;

        [[nodiscard]] GraphicsResourceAccess GetAccess() const noexcept
        {
            return _cpuAccess;
        }

        [[nodiscard]] GraphicsBufferKind GetKind() const noexcept
        {
            return _kind;
        }

        [[nodiscard]] NovelRT::Utilities::Span<uint8_t> MapBytes(size_t rangeOffset, size_t rangeLength) final;

        [[nodiscard]] NovelRT::Utilities::Span<const uint8_t> MapBytesForRead(size_t rangeOffset,
                                                                                    size_t rangeLength) final;

        void UnmapBytes() final;

        void UnmapBytesAndWrite(size_t writtenRangeOffset, size_t writtenRangeLength) final;

        [[nodiscard]] VkBuffer GetVulkanBuffer() const noexcept;
    };
}
