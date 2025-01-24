#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsBackendTraits.hpp>

namespace NovelRT::Graphics::Vulkan
{
    struct VulkanGraphicsBackend;

    class VulkanGraphicsProvider;
    class VulkanGraphicsAdapter;
    class VulkanGraphicsDevice;
    class VulkanGraphicsSurfaceContext;
    class VulkanGraphicsResource;
    template <typename TResource>
    class VulkanGraphicsResourceMemoryRegion;
    class VulkanGraphicsMemoryAllocator;
    class VulkanGraphicsBuffer;
    class VulkanGraphicsTexture;
}

namespace NovelRT::Graphics
{
    template<>
    struct GraphicsBackendTraits<Vulkan::VulkanGraphicsBackend>
    {
        using ProviderType = Vulkan::VulkanGraphicsProvider;
        using AdapterType = Vulkan::VulkanGraphicsAdapter;
        using DeviceType = Vulkan::VulkanGraphicsDevice;
        using SurfaceContextType = Vulkan::VulkanGraphicsSurfaceContext;
        using ContextType = Vulkan::VulkanGraphicsSurfaceContext;
        using ResourceType = Vulkan::VulkanGraphicsResource;

        template<typename TResource>
        using ResourceMemoryRegionType = Vulkan::VulkanGraphicsResourceMemoryRegion<TResource>;

        using MemoryAllocatorType = Vulkan::VulkanGraphicsMemoryAllocator;
        using BufferType = Vulkan::VulkanGraphicsBuffer;
        using TextureType = Vulkan::VulkanGraphicsTexture;
        using DescriptorType = Vulkan::VulkanGraphicsDescriptorSet;
    };
}