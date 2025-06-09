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

#include <algorithm>
#include <string>
#include <vector>

namespace NovelRT::Graphics::Vulkan
{
    using VulkanGraphicsAdapter = GraphicsAdapter<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsDevice = GraphicsDevice<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsSurfaceContext = GraphicsSurfaceContext<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsProvider = GraphicsProvider<Vulkan::VulkanGraphicsBackend>;

    static int32_t GetOptionalExtensionSupportScore(const std::vector<std::string>& availableDeviceExtensions,
                                                    const std::vector<std::string>& optionalDeviceExtensions)
    {
        // If the user didn't request any optional extensions, don't give them a score.
        if (optionalDeviceExtensions.empty())
        {
            return 0;
        }

        auto isOptionalExtension = [begin = optionalDeviceExtensions.begin(), end = optionalDeviceExtensions.end()](
                                       const auto& it) { return std::find(begin, end, it) != end; };
        auto foundOptionalExtensions =
            std::count_if(availableDeviceExtensions.begin(), availableDeviceExtensions.end(), isOptionalExtension);

        const float percentageStep = (1.0f / static_cast<float>(optionalDeviceExtensions.size())) * 100;
        return static_cast<int32_t>(foundOptionalExtensions * percentageStep);
    }

    static bool CheckRequiredExtensionSupport(const std::vector<std::string>& availableDeviceExtensions,
                                              const std::vector<std::string>& requiredDeviceExtensions)
    {
        // If the user didn't request any required extensions, pass immediately.
        if (requiredDeviceExtensions.empty())
        {
            return true;
        }

        auto isRequiredExtension = [begin = requiredDeviceExtensions.begin(), end = requiredDeviceExtensions.end()](
                                       const auto& it) { return std::find(begin, end, it) != end; };
        auto foundRequiredExtensions =
            std::count_if(availableDeviceExtensions.begin(), availableDeviceExtensions.end(), isRequiredExtension);

        return static_cast<decltype(requiredDeviceExtensions.size())>(foundRequiredExtensions) ==
               requiredDeviceExtensions.size();
    }

    static int32_t RateDeviceSuitability(const VulkanGraphicsAdapter& adapter,
                                         const VulkanGraphicsSurfaceContext& surfaceContext,
                                         const std::vector<std::string>& requiredDeviceExtensions,
                                         const std::vector<std::string>& optionalDeviceExtensions)
    {
        uint32_t extensionCount = 0;
        vkEnumerateDeviceExtensionProperties(adapter.GetPhysicalDevice(), nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        std::vector<std::string> extensionNames(extensionCount);

        vkEnumerateDeviceExtensionProperties(adapter.GetPhysicalDevice(), nullptr, &extensionCount,
                                             availableExtensions.data());
        std::transform(availableExtensions.begin(), availableExtensions.end(), extensionNames.begin(),
                       [](const auto& extension) { return std::string{extension.extensionName}; });

        // If we're missing required extensions, the adapter is useless.
        if (!CheckRequiredExtensionSupport(extensionNames, requiredDeviceExtensions))
        {
            return -1;
        }

        const SwapChainSupportDetails supportDetails =
            Utilities::QuerySwapChainSupport(adapter.GetPhysicalDevice(), surfaceContext.GetSurfaceContextHandle());
        const QueueFamilyIndices indices =
            Utilities::FindQueueFamilies(adapter.GetPhysicalDevice(), surfaceContext.GetSurfaceContextHandle());

        // If we can't render graphics, present or create a swapchain, the adapter is useless.
        if (!indices.IsComplete() || supportDetails.formats.empty() || supportDetails.presentModes.empty())
        {
            return -1;
        }

        VkPhysicalDeviceProperties deviceProperties;
        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceProperties(adapter.GetPhysicalDevice(), &deviceProperties);
        vkGetPhysicalDeviceFeatures(adapter.GetPhysicalDevice(), &deviceFeatures);

        int32_t score = 0;

        // Prefer discrete GPUs where possible
        if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
        {
            score += 1000;
        }

        // Prefer devices with larger texture support
        score += static_cast<int32_t>(deviceProperties.limits.maxImageDimension2D);
        // Prefer devices which support more optional extensions
        score += GetOptionalExtensionSupportScore(extensionNames, optionalDeviceExtensions);

        return score;
    }

    std::shared_ptr<VulkanGraphicsAdapter> VulkanGraphicsAdapterSelector::GetDefaultRecommendedAdapter(
        const std::shared_ptr<VulkanGraphicsProvider>& provider,
        const std::shared_ptr<VulkanGraphicsSurfaceContext>& surfaceContext,
        const std::vector<std::string>& requiredDeviceExtensions,
        const std::vector<std::string>& optionalDeviceExtensions) const
    {
        std::weak_ptr<VulkanGraphicsAdapter> adapter;
        int32_t highestScore = -1;

        for (const auto& currentAdapter : *provider)
        {
            const int32_t score = RateDeviceSuitability(*currentAdapter, *surfaceContext, requiredDeviceExtensions,
                                                        optionalDeviceExtensions);

            if (score > highestScore)
            {
                adapter = currentAdapter;
                highestScore = score;
            }
        }

        return adapter.lock();
    }

    std::shared_ptr<VulkanGraphicsAdapter> VulkanGraphicsAdapterSelector::GetDefaultRecommendedAdapter(
        const std::shared_ptr<VulkanGraphicsProvider>& provider,
        const std::shared_ptr<VulkanGraphicsSurfaceContext>& surfaceContext) const
    {
        return GetDefaultRecommendedAdapter(provider, surfaceContext,
                                            std::vector<std::string>{VK_KHR_SWAPCHAIN_EXTENSION_NAME},
                                            std::vector<std::string>{});
    }
} // namespace NovelRT::Graphics::Vulkan
