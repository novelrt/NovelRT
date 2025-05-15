#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsResourceAccess.hpp>
#include <NovelRT/Graphics/GraphicsTexture.hpp>
#include <NovelRT/Graphics/GraphicsTextureKind.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsResource.hpp>
#include <NovelRT/Utilities/Lazy.h>
#include <NovelRT/Graphics/Vulkan/Utilities/Vma.hpp>

namespace NovelRT::Graphics::Vulkan
{
    class VulkanGraphicsTexture : public VulkanGraphicsResource, public std::enable_shared_from_this<VulkanGraphicsTexture>
    {
    private:
        VkImage _vulkanImage;
        size_t _subAllocations;
        GraphicsTextureAddressMode _addressMode;
        GraphicsTextureKind _kind;

        NovelRT::Utilities::Lazy<VkImageView> _vulkanImageView;
        NovelRT::Utilities::Lazy<VkSampler> _vulkanSampler;

        uint32_t _width;
        uint32_t _height;
        uint32_t _depth;

        [[nodiscard]] VkImageView CreateVulkanImageView();
        [[nodiscard]] VkSampler CreateVulkanSampler();

    protected:
        [[nodiscard]] std::shared_ptr<VulkanGraphicsResourceMemoryRegion<VulkanGraphicsResource>> AllocateInternal(
            VmaVirtualAllocation allocation,
            VmaVirtualAllocationInfo info) final;

    public:
        using std::enable_shared_from_this<VulkanGraphicsTexture>::shared_from_this;

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
                              VkImage vulkanImage);

        virtual ~VulkanGraphicsTexture() noexcept;

        [[nodiscard]] GraphicsTextureAddressMode GetAddressMode() const noexcept;
        [[nodiscard]] GraphicsTextureKind GetKind() const noexcept;

        [[nodiscard]] NovelRT::Utilities::Misc::Span<uint8_t> MapBytes(size_t rangeOffset, size_t rangeLength) override;

        [[nodiscard]] NovelRT::Utilities::Misc::Span<const uint8_t> MapBytesForRead(size_t rangeOffset,
                                                                           size_t rangeLength) override;

        void UnmapBytes() final;

        void UnmapBytesAndWrite(size_t writtenRangeOffset, size_t writtenRangeLength) final;

        [[nodiscard]] VkImage GetVulkanImage() const noexcept;

        [[nodiscard]] VkImageView GetOrCreateVulkanImageView();

        [[nodiscard]] VkSampler GetOrCreateVulkanSampler();

        [[nodiscard]] uint32_t GetWidth() const noexcept;

        [[nodiscard]] uint32_t GetHeight() const noexcept;

        [[nodiscard]] uint32_t GetDepth() const noexcept;
    };
}
