#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsResourceAccess.hpp>
#include <NovelRT/Graphics/GraphicsTexture.hpp>
#include <NovelRT/Graphics/GraphicsTextureCreateInfo.hpp>
#include <NovelRT/Graphics/GraphicsTextureKind.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsResource.hpp>
#include <NovelRT/Graphics/Vulkan/Utilities/Vma.hpp>
#include <NovelRT/Utilities/Lazy.hpp>
#include <NovelRT/Utilities/Span.hpp>

namespace NovelRT::Graphics::Vulkan
{
    struct VulkanGraphicsBackend;
}

namespace NovelRT::Graphics
{
    template<template <typename> typename TResource, typename TBackend> class GraphicsResourceMemoryRegion;

    template <>
    class GraphicsTexture<Vulkan::VulkanGraphicsBackend> final
        : public GraphicsResource<Vulkan::VulkanGraphicsBackend>
    {
    private:
        VkImage _vulkanImage;
        size_t _mappedMemoryRegions;
        GraphicsTextureAddressMode _addressMode;
        GraphicsTextureKind _kind;

        mutable NovelRT::Utilities::Lazy<VkImageView> _vulkanImageView;
        mutable NovelRT::Utilities::Lazy<VkSampler> _vulkanSampler;

        uint32_t _width;
        uint32_t _height;
        uint32_t _depth;

        [[nodiscard]] VkImageView CreateVulkanImageView();
        [[nodiscard]] VkSampler CreateVulkanSampler();

    public:
        //NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        std::shared_ptr<GraphicsTexture<Vulkan::VulkanGraphicsBackend>> shared_from_this();

        GraphicsTexture(
            std::shared_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> graphicsDevice,
            std::shared_ptr<GraphicsMemoryAllocator<Vulkan::VulkanGraphicsBackend>> allocator,
            const GraphicsTextureCreateInfo& createInfo,
            VmaAllocation allocation,
            VmaAllocationInfo allocationInfo,
            VkImage vulkanImage);

        ~GraphicsTexture() noexcept final;

        [[nodiscard]] GraphicsTextureAddressMode GetAddressMode() const noexcept;
        [[nodiscard]] GraphicsTextureKind GetKind() const noexcept;

        [[nodiscard]] uint32_t GetWidth() const noexcept;
        [[nodiscard]] uint32_t GetHeight() const noexcept;
        [[nodiscard]] uint32_t GetDepth() const noexcept;

        [[nodiscard]] NovelRT::Utilities::Span<uint8_t> MapBytes(size_t rangeOffset, size_t rangeLength) override;

        [[nodiscard]] NovelRT::Utilities::Span<const uint8_t> MapBytesForRead(size_t rangeOffset, size_t rangeLength) override;

        void UnmapBytes() final;
        void UnmapBytesAndWrite() final;
        void UnmapBytesAndWrite(size_t writtenRangeOffset, size_t writtenRangeLength) final;

        void UnmapAndWrite(const GraphicsResourceMemoryRegion<GraphicsTexture, Vulkan::VulkanGraphicsBackend>* memoryRegion);

        [[nodiscard]] VkImage GetVulkanImage() const noexcept;

        [[nodiscard]] VkImageView GetVulkanImageView() const;
        [[nodiscard]] VkSampler GetVulkanSampler() const;


    };
}
