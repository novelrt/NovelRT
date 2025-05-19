// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsAdapter.hpp>
#include <NovelRT/Graphics/GraphicsDevice.hpp>
#include <NovelRT/Graphics/GraphicsRenderPass.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsAdapter.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsBackendTraits.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsDevice.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsProvider.hpp>

#include <string>

namespace NovelRT::Graphics::Vulkan
{
    std::string VulkanGraphicsAdapter::GetNameInternal()
    {
        return { GetVulkanPhysicalDeviceProperties().deviceName };
    }

    VkPhysicalDeviceProperties VulkanGraphicsAdapter::GetVulkanPhysicalDevicePropertiesInternal() const
    {
        VkPhysicalDeviceProperties physicalDeviceProperties{};
        vkGetPhysicalDeviceProperties(GetVulkanPhysicalDevice(), &physicalDeviceProperties);
        return physicalDeviceProperties;
    }

    VkPhysicalDeviceMemoryProperties VulkanGraphicsAdapter::GetVulkanPhysicalDeviceMemoryPropertiesInternal() const
    {
        VkPhysicalDeviceMemoryProperties physicalDeviceMemoryProperties{};
        vkGetPhysicalDeviceMemoryProperties(GetVulkanPhysicalDevice(), &physicalDeviceMemoryProperties);
        return physicalDeviceMemoryProperties;
    }

    VulkanGraphicsAdapter::VulkanGraphicsAdapter(VulkanGraphicsProvider* provider,
                                                 VkPhysicalDevice physicalDevice)
        : _provider(provider)
        , _vulkanPhysicalDevice(physicalDevice)
        , _vulkanPhysicalDeviceProperties([&]() { return GetVulkanPhysicalDevicePropertiesInternal(); })
        , _vulkanPhysicalDeviceMemoryProperties([&]() { return GetVulkanPhysicalDeviceMemoryPropertiesInternal(); })
        , _name([&]() { return GetNameInternal(); })
    {
    }

    std::unique_ptr<VulkanGraphicsDevice> VulkanGraphicsAdapter::CreateDevice(
        VulkanGraphicsSurfaceContext* surfaceContext,
        int32_t contextCount)
    {
        return std::make_unique<VulkanGraphicsDevice>(this, surfaceContext, contextCount);
    }
} // namespace NovelRT::Graphics::Vulkan

template class NovelRT::Graphics::GraphicsAdapter<NovelRT::Graphics::Vulkan::VulkanGraphicsBackend>;
