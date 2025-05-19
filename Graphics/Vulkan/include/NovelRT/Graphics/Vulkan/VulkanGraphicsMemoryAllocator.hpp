#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsBufferCreateInfo.hpp>
#include <NovelRT/Graphics/GraphicsTextureCreateInfo.hpp>
#include <NovelRT/Graphics/Vulkan/Utilities/Vma.hpp>

#include <memory>

namespace NovelRT::Graphics::Vulkan
{
    class VulkanGraphicsBuffer;
    class VulkanGraphicsDevice;
    class VulkanGraphicsProvider;
    class VulkanGraphicsTexture;

    class VulkanGraphicsMemoryAllocator
    {
    private:
        VmaAllocator _allocator;
        VulkanGraphicsDevice* _device;
        VulkanGraphicsProvider* _provider;

    public:
        VulkanGraphicsMemoryAllocator(VulkanGraphicsDevice* device, VulkanGraphicsProvider* provider);

        [[nodiscard]] VulkanGraphicsDevice* GetDevice() const noexcept
        {
            return _device;
        }

        [[nodiscard]] VulkanGraphicsProvider* GetProvider() const noexcept
        {
            return _provider;
        }

        [[nodiscard]] std::unique_ptr<VulkanGraphicsBuffer> CreateBuffer(const GraphicsBufferCreateInfo& createInfo);
        [[nodiscard]] std::unique_ptr<VulkanGraphicsTexture> CreateTexture(const GraphicsTextureCreateInfo& createInfo);

        [[nodiscard]] VmaAllocator GetVmaAllocator() const noexcept;
    };
}
