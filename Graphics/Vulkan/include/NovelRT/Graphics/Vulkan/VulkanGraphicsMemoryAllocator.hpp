#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsBufferCreateInfo.hpp>
#include <NovelRT/Graphics/GraphicsTextureCreateInfo.hpp>

#include <NovelRT/Graphics/Vulkan/Utilities/Vma.hpp>

namespace NovelRT::Graphics::Vulkan
{
    class VulkanGraphicsBuffer;
    class VulkanGraphicsDevice;
    class VulkanGraphicsProvider;
    class VulkanGraphicsTexture;

    class VulkanGraphicsMemoryAllocator : public std::enable_shared_from_this<VulkanGraphicsMemoryAllocator>
    {
    private:
        VmaAllocator _allocator;
        std::shared_ptr<VulkanGraphicsDevice> _device;
        std::shared_ptr<VulkanGraphicsProvider> _provider;

    public:
        VulkanGraphicsMemoryAllocator(std::shared_ptr<VulkanGraphicsDevice> device,
                                      std::shared_ptr<VulkanGraphicsProvider> provider);

        [[nodiscard]] std::shared_ptr<VulkanGraphicsDevice> GetDevice() const noexcept;

        [[nodiscard]] std::shared_ptr<VulkanGraphicsProvider> GetProvider() const noexcept;

        [[nodiscard]] std::shared_ptr<VulkanGraphicsBuffer> CreateBuffer(const GraphicsBufferCreateInfo& createInfo);

        [[nodiscard]] std::shared_ptr<VulkanGraphicsTexture> CreateTexture(const GraphicsTextureCreateInfo& createInfo);

        [[nodiscard]] std::shared_ptr<VulkanGraphicsBuffer> CreateVulkanBuffer(
            const GraphicsBufferCreateInfo& createInfo);

        [[nodiscard]] std::shared_ptr<VulkanGraphicsTexture> CreateVulkanTexture(
            const GraphicsTextureCreateInfo& createInfo);

        [[nodiscard]] VmaAllocator GetVmaAllocator() const noexcept;
    };
}
