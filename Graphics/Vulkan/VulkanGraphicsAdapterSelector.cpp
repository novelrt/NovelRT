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
#include <cmath>
#include <functional>
#include <string>
#include <vector>

namespace NovelRT::Graphics::Vulkan
{
    using VulkanGraphicsAdapter = GraphicsAdapter<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsDevice = GraphicsDevice<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsSurfaceContext = GraphicsSurfaceContext<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsProvider = GraphicsProvider<Vulkan::VulkanGraphicsBackend>;

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

        auto isRequiredExtension = [begin = requiredDeviceExtensions.begin(), end = requiredDeviceExtensions.end()](
                                       const auto& it) { return std::find(begin, end, it) != end; };
        auto firstNonRequiredExtension =
            std::partition(extensionNames.begin(), extensionNames.end(), isRequiredExtension);
        auto numberOfRequiredExtensions = static_cast<std::vector<std::string>::size_type>(
            std::abs(std::distance(extensionNames.begin(), firstNonRequiredExtension)));

        // If we don't have all the required extensions, the adapter is useless
        if (numberOfRequiredExtensions < requiredDeviceExtensions.size())
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

        auto isOptionalExtension = [begin = optionalDeviceExtensions.begin(), end = optionalDeviceExtensions.end()](
                                       const auto& it) { return std::find(begin, end, it) != end; };
        auto firstNonNecessaryExtension =
            std::partition(firstNonRequiredExtension, extensionNames.end(), isOptionalExtension);
        auto numberOfOptionalExtensions = static_cast<std::vector<std::string>::size_type>(
            std::abs(std::distance(firstNonRequiredExtension, firstNonNecessaryExtension)));

        // Our score starts at how many optional extensions we have,
        int32_t score = numberOfOptionalExtensions;

        VkPhysicalDeviceProperties deviceProperties;
        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceProperties(adapter.GetPhysicalDevice(), &deviceProperties);
        vkGetPhysicalDeviceFeatures(adapter.GetPhysicalDevice(), &deviceFeatures);

        // The bit position of the largest power-of-two sized texture that can be created on this device
        // That is, 1 << maxPo2TextureSizeBitOffset will return the actual texture size.
        int32_t maxPo2TextureSizeBitOffset =
            std::log2(static_cast<int32_t>(deviceProperties.limits.maxImageDimension2D));

        // If the device can create larger textures, it's usually more powerful.
        score += maxPo2TextureSizeBitOffset * std::max(optionalDeviceExtensions.size(), 1ul);

        // However, we want to prefer dedicated hardware even if software emulation an create something even larger.
        if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
        {
            // N.B. There's a bunch of conflicting information, but it's rather unlikely that a device can create a
            // texture that is 2^32 pixels large.
            score += 32 * std::max(optionalDeviceExtensions.size(), 1ul);
        }

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
