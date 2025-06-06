#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsBufferKind.hpp>
#include <NovelRT/Graphics/GraphicsResourceAccess.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsResource.hpp>
#include <memory>
#include <NovelRT/Graphics/Vulkan/Utilities/Vma.hpp>

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
        [[nodiscard]] std::shared_ptr<VulkanGraphicsResourceMemoryRegion<VulkanGraphicsResource>> AllocateInternal(VmaVirtualAllocation allocation, VmaVirtualAllocationInfo info) final;
        
        virtual void FreeInternal(VulkanGraphicsResourceMemoryRegionBase& region) final;

    public:
        std::shared_ptr<VulkanGraphicsBuffer> shared_from_this()
        {
            return std::static_pointer_cast<VulkanGraphicsBuffer>(VulkanGraphicsResource::shared_from_this());
        }

        VulkanGraphicsBuffer(std::shared_ptr<VulkanGraphicsDevice> graphicsDevice,
                             std::shared_ptr<VulkanGraphicsMemoryAllocator> allocator,
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

        [[nodiscard]] NovelRT::Utilities::Misc::Span<uint8_t> MapBytes(size_t rangeOffset, size_t rangeLength) final;

        [[nodiscard]] NovelRT::Utilities::Misc::Span<const uint8_t> MapBytesForRead(size_t rangeOffset,
                                                                                    size_t rangeLength) final;

        void UnmapBytes() final;

        void UnmapBytesAndWrite(size_t writtenRangeOffset, size_t writtenRangeLength) final;

        [[nodiscard]] VkBuffer GetVulkanBuffer() const noexcept;
    };
}
