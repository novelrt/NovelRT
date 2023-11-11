// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <string>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsAdapter.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsProvider.hpp>

namespace NovelRT::Graphics::Vulkan
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

    std::shared_ptr<VulkanGraphicsDevice> VulkanGraphicsAdapter::CreateVulkanGraphicsDevice(
        std::shared_ptr<VulkanGraphicsSurfaceContext> surfaceContext,
        int32_t contextCount)
    {
        return std::make_shared<VulkanGraphicsDevice>(
            std::dynamic_pointer_cast<VulkanGraphicsAdapter>(shared_from_this()), std::move(surfaceContext),
            contextCount);
    }
} // namespace NovelRT::Graphics::Vulkan
