// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InitialisationFailureException.h>
#include <NovelRT/Experimental/EngineConfig.h>
#include <NovelRT/Experimental/Graphics/Vulkan/VulkanGraphicsDevice.h>
#include <NovelRT/Utilities/Misc.h>
#include <numeric>

namespace NovelRT::Experimental::Graphics::Vulkan
{
    VulkanGraphicsDevice::VulkanGraphicsDevice() noexcept
        : _instance(VkInstance{}), _logger(LoggingService(Utilities::Misc::CONSOLE_LOG_GFX))
    {
    }

    void VulkanGraphicsDevice::CreateInstance()
    {
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = EngineConfig::ApplicationName.c_str();
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = EngineConfig::EngineName.c_str();
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_2;

        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensionProperties(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensionProperties.data());

        for (auto&& requestedRequiredExt : EngineConfig::RequiredVulkanExtensions)
        {
            auto result = std::find_if(extensionProperties.begin(), extensionProperties.end(),
                                       [&](auto& x) { return requestedRequiredExt.compare(&x.extensionName[0]); });

            if (result == extensionProperties.end())
            {
                throw Exceptions::InitialisationFailureException(
                    "The extension " + requestedRequiredExt +
                    " is not available on this device. Vulkan cannot continue.");
            }
        }

        std::vector<std::string> finalOptionalExtensions{};

        for (auto&& requestedOptionalExt : EngineConfig::OptionalVulkanExtensions)
        {
            auto result = std::find_if(extensionProperties.begin(), extensionProperties.end(),
                                       [&](auto& x) { return requestedOptionalExt.compare(&x.extensionName[0]); });

            if (result == extensionProperties.end())
            {
                _logger.logWarning("The extension " + requestedOptionalExt +
                                   " is not available on this device. Vulkan may not behave as you expect.");
                continue;
            }

            finalOptionalExtensions.emplace_back(requestedOptionalExt);
        }

        size_t extensionLength = EngineConfig::RequiredVulkanExtensions.size() + finalOptionalExtensions.size();
        std::vector<const char*> allExtensions{};
        allExtensions.reserve(extensionLength);

        for (auto&& ext : EngineConfig::RequiredVulkanExtensions)
        {
            allExtensions.push_back(ext.c_str());
        }
        for (auto&& ext : finalOptionalExtensions)
        {
            allExtensions.push_back(ext.c_str());
        }

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensionLength);
        createInfo.ppEnabledExtensionNames = allExtensions.data();
        createInfo.enabledLayerCount = 0;

        if (vkCreateInstance(&createInfo, nullptr, &_instance) != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to create an instance of Vulkan version 1.2.");
        }

        _logger.logInfoLine("Vulkan version 1.2 has been successfully initialised.");
    }

    void VulkanGraphicsDevice::Initialise()
    {
        CreateInstance();
    }

    void VulkanGraphicsDevice::TearDown()
    {
        vkDestroyInstance(_instance, nullptr);
    }
} // namespace NovelRT::Experimental::Graphics::Vulkan
