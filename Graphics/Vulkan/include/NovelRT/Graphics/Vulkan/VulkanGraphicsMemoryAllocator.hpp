#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDeviceObject.hpp>
#include <NovelRT/Graphics/GraphicsMemoryAllocator.hpp>
#include <NovelRT/Graphics/Vulkan/Utilities/Vma.hpp>

#include <memory>

namespace NovelRT::Graphics::Vulkan
{
    struct VulkanGraphicsBackend;
}

namespace NovelRT::Graphics
{
    template<>
    class GraphicsMemoryAllocator<Vulkan::VulkanGraphicsBackend>
        : public GraphicsDeviceObject<Vulkan::VulkanGraphicsBackend>
    {
    private:
        std::weak_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> _device;
        std::shared_ptr<GraphicsProvider<Vulkan::VulkanGraphicsBackend>> _provider;

        VmaAllocator _allocator;

    public:
        //NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        std::shared_ptr<GraphicsMemoryAllocator<Vulkan::VulkanGraphicsBackend>> shared_from_this();
        //NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        std::shared_ptr<const GraphicsMemoryAllocator<Vulkan::VulkanGraphicsBackend>> shared_from_this() const;

        GraphicsMemoryAllocator(std::weak_ptr<GraphicsDevice<Vulkan::VulkanGraphicsBackend>> device, std::shared_ptr<GraphicsProvider<Vulkan::VulkanGraphicsBackend>> provider);

        [[nodiscard]] std::weak_ptr<GraphicsProvider<Vulkan::VulkanGraphicsBackend>> GetProvider() const noexcept;

        [[nodiscard]] std::shared_ptr<GraphicsBuffer<Vulkan::VulkanGraphicsBackend>> CreateBuffer(const GraphicsBufferCreateInfo& createInfo);
        [[nodiscard]] std::shared_ptr<GraphicsTexture<Vulkan::VulkanGraphicsBackend>> CreateTexture(const GraphicsTextureCreateInfo& createInfo);

        [[nodiscard]] std::shared_ptr<GraphicsTexture<Vulkan::VulkanGraphicsBackend>> CreateTexture2DRepeatGpuWriteOnly(uint32_t width, uint32_t height = 1);

        [[nodiscard]] VmaAllocator GetVmaAllocator() const noexcept;
    };
}
