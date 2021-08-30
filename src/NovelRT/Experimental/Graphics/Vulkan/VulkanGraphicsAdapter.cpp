// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Experimental/Graphics/Vulkan/Graphics.Vulkan.h>

namespace NovelRT::Experimental::Graphics::Vulkan
{
    std::string VulkanGraphicsAdapter::GetNameInternal()
    {
        return std::string(GetVulkanPhysicalDeviceProperties().deviceName);
    }

    VkPhysicalDeviceProperties VulkanGraphicsAdapter::GetVulkanPhysicalDevicePropertiesInternal()
    {
        VkPhysicalDeviceProperties physicalDeviceProperties{};
        vkGetPhysicalDeviceProperties(GetVulkanPhysicalDevice(), &physicalDeviceProperties);
        return physicalDeviceProperties;
    }

    VkPhysicalDeviceMemoryProperties VulkanGraphicsAdapter::GetVulkanPhysicalDeviceMemoryPropertiesInternal()
    {
        VkPhysicalDeviceMemoryProperties physicalDeviceMemoryProperties{};
        vkGetPhysicalDeviceMemoryProperties(GetVulkanPhysicalDevice(), &physicalDeviceMemoryProperties);
        return physicalDeviceMemoryProperties;
    }

    VulkanGraphicsAdapter::VulkanGraphicsAdapter(const std::shared_ptr<VulkanGraphicsProvider>& provider,
                                                 VkPhysicalDevice physicalDevice)
        : GraphicsAdapter(provider->weak_from_this()),
          _vulkanPhysicalDevice(physicalDevice),
          _vulkanPhysicalDeviceProperties([&]() { return GetVulkanPhysicalDevicePropertiesInternal(); }),
          _vulkanPhysicalDeviceMemoryProperties([&]() { return GetVulkanPhysicalDeviceMemoryPropertiesInternal(); }),
          _name([&]() { return GetNameInternal(); }),
          _state()
    {
        static_cast<void>(_state.Transition(Threading::VolatileState::Initialised));
    }
} // namespace NovelRT::Experimental::Graphics::Vulkan