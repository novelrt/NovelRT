#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Threading/Threading.h>
#include <NovelRT/Utilities/Lazy.h>
#include <string>
#include <vulkan/vulkan.h>

namespace NovelRT::Graphics::Vulkan
{
    class VulkanGraphicsDevice;
    class VulkanGraphicsProvider;
    class VulkanGraphicsSurfaceContext;

    class VulkanGraphicsAdapter : public std::enable_shared_from_this<VulkanGraphicsAdapter>
    {
    private:
        std::weak_ptr<VulkanGraphicsProvider> _provider;
        VkPhysicalDevice _vulkanPhysicalDevice;
        NovelRT::Utilities::Lazy<VkPhysicalDeviceProperties> _vulkanPhysicalDeviceProperties;
        NovelRT::Utilities::Lazy<VkPhysicalDeviceMemoryProperties> _vulkanPhysicalDeviceMemoryProperties;
        NovelRT::Utilities::Lazy<std::string> _name;

        [[nodiscard]] std::string GetNameInternal();
        [[nodiscard]] VkPhysicalDeviceProperties GetVulkanPhysicalDevicePropertiesInternal();
        [[nodiscard]] VkPhysicalDeviceMemoryProperties GetVulkanPhysicalDeviceMemoryPropertiesInternal();

    public:
        VulkanGraphicsAdapter(std::shared_ptr<VulkanGraphicsProvider> provider, VkPhysicalDevice physicalDevice);

        ~VulkanGraphicsAdapter() = default;

        [[nodiscard]] inline VkPhysicalDevice GetVulkanPhysicalDevice() const noexcept
        {
            return _vulkanPhysicalDevice;
        }

        [[nodiscard]] inline const VkPhysicalDeviceProperties& GetVulkanPhysicalDeviceProperties()
        {
            return _vulkanPhysicalDeviceProperties.getActual();
        }

        [[nodiscard]] inline const VkPhysicalDeviceMemoryProperties& GetVulkanPhysicalDeviceMemoryProperties()
        {
            return _vulkanPhysicalDeviceMemoryProperties.getActual();
        }

        [[nodiscard]] uint32_t GetDeviceId()
        {
            return GetVulkanPhysicalDeviceProperties().deviceID;
        }

        [[nodiscard]] const std::string& GetName()
        {
            return _name.getActual();
        }

        [[nodiscard]] inline uint32_t GetVendorId()
        {
            return GetVulkanPhysicalDeviceProperties().vendorID;
        }

        [[nodiscard]] std::shared_ptr<VulkanGraphicsDevice> CreateDevice(
            std::shared_ptr<VulkanGraphicsSurfaceContext> surfaceContext,
            int32_t contextCount);

        [[nodiscard]] inline std::shared_ptr<VulkanGraphicsProvider> GetProvider() const
        {
            if (_provider.expired())
            {
                throw std::runtime_error("Provider has expired.");
            }

            return _provider.lock();
        }
    };
}
