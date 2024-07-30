#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsResourceAccess.hpp>
#include <NovelRT/Graphics/GraphicsTexture.hpp>
#include <NovelRT/Graphics/GraphicsTextureKind.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsResource.hpp>
#include <NovelRT/Utilities/Lazy.h>
#include <vk_mem_alloc.h>

namespace NovelRT::Graphics::Vulkan
{
    class VulkanGraphicsTexture final : public VulkanGraphicsResource
    {
    private:
        VkImage _vulkanImage;
        size_t _subAllocations;

        NovelRT::Utilities::Lazy<VkImageView> _vulkanImageView;
        NovelRT::Utilities::Lazy<VkSampler> _vulkanSampler;

        [[nodiscard]] VkImageView CreateVulkanImageView();
        [[nodiscard]] VkSampler CreateVulkanSampler();

    public:
        VulkanGraphicsTexture(std::shared_ptr<VulkanGraphicsDevice> device,
                              std::shared_ptr<VulkanGraphicsMemoryAllocator> allocator,
                              GraphicsResourceAccess cpuAccess,
                              GraphicsTextureAddressMode addressMode,
                              GraphicsTextureKind kind,
                              uint32_t width,
                              uint32_t height,
                              uint16_t depth,
                              VmaAllocation allocation,
                              VmaAllocationInfo allocationInfo,
                              size_t subAllocations,
                              VkImage vulkanImage);

        ~VulkanGraphicsTexture() noexcept final;

        [[nodiscard]] NovelRT::Utilities::Misc::Span<uint8_t> MapBytes(size_t rangeOffset, size_t rangeLength);

        [[nodiscard]] NovelRT::Utilities::Misc::Span<const uint8_t> MapBytesForRead(size_t rangeOffset,
                                                                           size_t rangeLength);

        void UnmapBytes();

        void UnmapBytesAndWrite(size_t writtenRangeOffset, size_t writtenRangeLength);
        
        [[nodiscard]] VkImage GetVulkanImage() const noexcept;

        [[nodiscard]] VkImageView GetOrCreateVulkanImageView();

        [[nodiscard]] VkSampler GetOrCreateVulkanSampler();
    };
}