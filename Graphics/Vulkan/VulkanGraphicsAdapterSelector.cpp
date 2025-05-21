// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

// TODO: clean this up good grief
#include <NovelRT/Exceptions/NotSupportedException.hpp>

#include <NovelRT/Graphics/Vulkan/QueueFamilyIndices.hpp>
#include <NovelRT/Graphics/Vulkan/SwapChainSupportDetails.hpp>
#include <NovelRT/Graphics/Vulkan/Utilities/Support.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsAdapter.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsAdapterSelector.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsProvider.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsSurfaceContext.hpp>

#include <set>
#include <string>
#include <vector>

namespace NovelRT::Graphics::Vulkan
{
    using VulkanGraphicsAdapter = GraphicsAdapter<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsDevice = GraphicsDevice<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsSurfaceContext = GraphicsSurfaceContext<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsProvider = GraphicsProvider<Vulkan::VulkanGraphicsBackend>;

    int32_t VulkanGraphicsAdapterSelector::GetPhysicalDeviceOptionalExtensionSupportScore(
        VkPhysicalDevice physicalDevice) noexcept
    {
        float currentPercentageValue = 0;

        uint32_t extensionCount = 0;
        vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, availableExtensions.data());

        // TODO: EngineConfig was here
        std::set<std::string> optionalExtensionSet{};//EngineConfig::OptionalVulkanPhysicalDeviceExtensions().begin(),
                                                     //EngineConfig::OptionalVulkanPhysicalDeviceExtensions().end());

        const float percentageStep = (1.0f / static_cast<float>(optionalExtensionSet.size())) * 100;

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
                                                                 VkSurfaceKHR surfaceContext) noexcept
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

        const SwapChainSupportDetails supportDetails = Utilities::QuerySwapChainSupport(physicalDevice, surfaceContext);
        const QueueFamilyIndices indices = Utilities::FindQueueFamilies(physicalDevice, surfaceContext);

        if (!indices.IsComplete() || !CheckPhysicalDeviceRequiredExtensionSupport(physicalDevice) ||
            supportDetails.formats.empty() || supportDetails.presentModes.empty())
        {
            score = -1;
        }

        return score;
    }

    bool VulkanGraphicsAdapterSelector::CheckPhysicalDeviceRequiredExtensionSupport(
        VkPhysicalDevice physicalDevice) noexcept
    {
        uint32_t extensionCount = 0;
        vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, availableExtensions.data());

        // TODO: EngineConfig was here
        std::set<std::string> requiredExtensionSet{};//EngineConfig::RequiredVulkanPhysicalDeviceExtensions().begin(),
                                                     //EngineConfig::RequiredVulkanPhysicalDeviceExtensions().end());

        for (const auto& extension : availableExtensions)
        {
            requiredExtensionSet.erase(std::string(extension.extensionName));
        }

        return requiredExtensionSet.empty();
    }

    std::shared_ptr<VulkanGraphicsAdapter> VulkanGraphicsAdapterSelector::GetDefaultRecommendedAdapter(
        const VulkanGraphicsProvider* provider,
        const VulkanGraphicsSurfaceContext* surfaceContext) const
    {
        std::weak_ptr<VulkanGraphicsAdapter> adapter;
        int32_t highestScore = 0;

        for (auto&& currentAdapter : *provider)
        {
            const int32_t score = RateDeviceSuitability(
                currentAdapter->GetPhysicalDevice(),
                surfaceContext->GetSurfaceContextHandle());

            if (score > highestScore)
            {
                adapter = currentAdapter;
                highestScore = score;
            }
        }

        return adapter.lock();
    }
} // namespace NovelRT::Graphics::Vulkan
