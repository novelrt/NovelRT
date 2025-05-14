#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsBackendTraits.hpp>

namespace NovelRT::Graphics::Vulkan
{
    struct VulkanGraphicsBackend;

    class VulkanGraphicsAdapter;
    class VulkanGraphicsBuffer;
    class VulkanGraphicsCmdList;
    class VulkanGraphicsContext;
    class VulkanGraphicsDescriptorSet;
    class VulkanGraphicsDevice;
    class VulkanGraphicsFence;
    class VulkanGraphicsMemoryAllocator;
    class VulkanGraphicsPipeline;
    class VulkanGraphicsPipelineSignature;
    class VulkanGraphicsProvider;
    class VulkanGraphicsRenderPass;
    class VulkanGraphicsResource;
    class VulkanGraphicsResourceMemoryRegionBase;
    template <typename TResource>
    class VulkanGraphicsResourceMemoryRegion;
    class VulkanGraphicsSurfaceContext;
    class VulkanGraphicsTexture;
    class VulkanShaderProgram;
}

namespace NovelRT::Graphics
{
    template<>
    struct GraphicsBackendTraits<Vulkan::VulkanGraphicsBackend>
    {
        using AdapterType = Vulkan::VulkanGraphicsAdapter;
        using BufferType = Vulkan::VulkanGraphicsBuffer;
        using CmdListType = Vulkan::VulkanGraphicsCmdList;
        using ContextType = Vulkan::VulkanGraphicsContext;
        using DescriptorSetType = Vulkan::VulkanGraphicsDescriptorSet;
        using DeviceType = Vulkan::VulkanGraphicsDevice;
        using FenceType = Vulkan::VulkanGraphicsFence;
        using MemoryAllocatorType = Vulkan::VulkanGraphicsMemoryAllocator;
        using PipelineType = Vulkan::VulkanGraphicsPipeline;
        using PipelineSignatureType = Vulkan::VulkanGraphicsPipelineSignature;
        using ProviderType = Vulkan::VulkanGraphicsProvider;
        using RenderPassType = Vulkan::VulkanGraphicsRenderPass;
        using ResourceType = Vulkan::VulkanGraphicsResource;
        using ResourceMemoryRegionBaseType = Vulkan::VulkanGraphicsResourceMemoryRegionBase;
        template<typename TResource>
        using ResourceMemoryRegionType = Vulkan::VulkanGraphicsResourceMemoryRegion<TResource>;
        using ShaderProgramType = Vulkan::VulkanShaderProgram;
        using SurfaceContextType = Vulkan::VulkanGraphicsSurfaceContext;
        using TextureType = Vulkan::VulkanGraphicsTexture;
    };
}
