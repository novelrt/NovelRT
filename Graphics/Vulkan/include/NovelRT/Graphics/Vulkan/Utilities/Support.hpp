#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <vector>
#include <vulkan/vulkan.h>
#include <NovelRT/Graphics/Vulkan/QueueFamilyIndices.hpp>
#include <NovelRT/Graphics/Vulkan/SwapChainSupportDetails.hpp>

namespace NovelRT::Graphics::Vulkan::Utilities
{
    [[nodiscard]] inline QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice physicalDevice,
                                                              VkSurfaceKHR surface) noexcept
    {
        QueueFamilyIndices returnObject{};

        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

        VkBool32 presentSupport = false;

        uint32_t familyIndex = 0;
        for (const auto& queueFamily : queueFamilies)
        {
            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
            {
                returnObject.graphicsFamily = familyIndex;
            }

            vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, familyIndex, surface, &presentSupport);
            if (presentSupport)
            {
                returnObject.presentFamily = familyIndex;
            }

            if (returnObject.IsComplete())
            {
                break;
            }

            ++familyIndex;
        }

        return returnObject;
    }

    [[nodiscard]] inline SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice physicalDevice,
                                                                       VkSurfaceKHR surface) noexcept
    {
        SwapChainSupportDetails returnDetails;
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &returnDetails.capabilities);

        uint32_t formatCount = 0;
        vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, nullptr);

        if (formatCount != 0)
        {
            returnDetails.formats.resize(formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, returnDetails.formats.data());
        }

        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, nullptr);

        if (presentModeCount != 0)
        {
            returnDetails.presentModes.resize(presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount,
                                                      returnDetails.presentModes.data());
        }

        return returnDetails;
    }
}
