// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include "NovelRT/Graphics/Vulkan/Graphics.Vulkan.h"

namespace NovelRT::Graphics::Vulkan
{
    int32_t VulkanGraphicsAdapterSelector::GetPhysicalDeviceOptionalExtensionSupportScore(
        VkPhysicalDevice physicalDevice) const noexcept
    {
        float currentPercentageValue = 0;

        uint32_t extensionCount = 0;
        vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, availableExtensions.data());

        std::set<std::string> optionalExtensionSet(EngineConfig::OptionalVulkanPhysicalDeviceExtensions().begin(),
                                                   EngineConfig::OptionalVulkanPhysicalDeviceExtensions().end());

        float percentageStep = (1.0f / static_cast<float>(optionalExtensionSet.size())) * 100;

        for (const auto& extension : availableExtensions)
        {

            if (optionalExtensionSet.find(std::string(extension.extensionName)) == optionalExtensionSet.end())
            {
                continue;
            }

            currentPercentageValue += percentageStep;
        }

        return static_cast<int32_t>(currentPercentageValue);
    }

    int32_t VulkanGraphicsAdapterSelector::RateDeviceSuitability(VkPhysicalDevice physicalDevice,
                                                                 VkSurfaceKHR surfaceContext) const noexcept
    {
        VkPhysicalDeviceProperties deviceProperties;
        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);
        vkGetPhysicalDeviceFeatures(physicalDevice, &deviceFeatures);

        int32_t score = 0;

        if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
        {
            score += 1000;
        }

        score += static_cast<int32_t>(deviceProperties.limits.maxImageDimension2D);
        score += GetPhysicalDeviceOptionalExtensionSupportScore(physicalDevice);

        SwapChainSupportDetails supportDetails = Utilities::QuerySwapChainSupport(physicalDevice, surfaceContext);
        QueueFamilyIndices indices = Utilities::FindQueueFamilies(physicalDevice, surfaceContext);

        if (!indices.IsComplete() || !CheckPhysicalDeviceRequiredExtensionSupport(physicalDevice) ||
            supportDetails.formats.empty() || supportDetails.presentModes.empty())
        {
            score = -1;
        }

        return score;
    }

    bool VulkanGraphicsAdapterSelector::CheckPhysicalDeviceRequiredExtensionSupport(
        VkPhysicalDevice physicalDevice) const noexcept
    {
        uint32_t extensionCount = 0;
        vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, availableExtensions.data());

        std::set<std::string> requiredExtensionSet(EngineConfig::RequiredVulkanPhysicalDeviceExtensions().begin(),
                                                   EngineConfig::RequiredVulkanPhysicalDeviceExtensions().end());

        for (const auto& extension : availableExtensions)
        {
            requiredExtensionSet.erase(std::string(extension.extensionName));
        }

        return requiredExtensionSet.empty();
    }

    std::shared_ptr<GraphicsAdapter> VulkanGraphicsAdapterSelector::GetDefaultRecommendedAdapter(
        const std::shared_ptr<GraphicsProvider>& provider,
        const std::shared_ptr<GraphicsSurfaceContext>& surfaceContext) const
    {
        return std::static_pointer_cast<GraphicsAdapter>(GetDefaultRecommendedAdapterVulkan(
            std::dynamic_pointer_cast<VulkanGraphicsProvider>(provider),
            std::dynamic_pointer_cast<VulkanGraphicsSurfaceContext>(surfaceContext)));
    }

    std::shared_ptr<VulkanGraphicsAdapter> VulkanGraphicsAdapterSelector::GetDefaultRecommendedAdapterVulkan(
        const std::shared_ptr<VulkanGraphicsProvider>& provider,
        const std::shared_ptr<VulkanGraphicsSurfaceContext>& surfaceContext) const
    {
        std::shared_ptr<VulkanGraphicsSurfaceContext> surfaceContextVulkan =
            std::dynamic_pointer_cast<VulkanGraphicsSurfaceContext>(surfaceContext);

        if (surfaceContextVulkan == nullptr)
        {
            throw NovelRT::Core::Exceptions::NotSupportedException(
                "The type of surface context that has been provided is not supported by this graphics implementation.");
        }

        std::shared_ptr<VulkanGraphicsAdapter> adapter = nullptr;
        int32_t highestScore = 0;

        for (auto&& currentAdapter : *provider)
        {
            int32_t score = RateDeviceSuitability(
                std::dynamic_pointer_cast<VulkanGraphicsAdapter>(currentAdapter)->GetVulkanPhysicalDevice(),
                surfaceContextVulkan->GetVulkanSurfaceContextHandle());

            if (score > highestScore)
            {
                adapter = std::dynamic_pointer_cast<VulkanGraphicsAdapter>(currentAdapter);
                highestScore = score;
            }
        }

        return adapter;
    }
} // namespace NovelRT::Graphics::Vulkan
