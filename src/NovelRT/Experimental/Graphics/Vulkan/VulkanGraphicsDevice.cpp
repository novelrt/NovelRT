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

    std::vector<const char*> VulkanGraphicsDevice::GetStringVectorAsCharPtrVector(
        const std::vector<std::string>& target) const noexcept
    {
        size_t extensionLength = target.size();
        std::vector<const char*> targetPtrs{};
        targetPtrs.reserve(extensionLength);

        for (auto&& extension : target)
        {
            targetPtrs.emplace_back(extension.c_str());
        }

        return targetPtrs;
    }

    std::vector<std::string> VulkanGraphicsDevice::GetFinalExtensionSet() const
    {
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensionProperties(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensionProperties.data());

        for (auto&& requestedRequiredExt : EngineConfig::RequiredVulkanExtensions)
        {
            auto result = std::find_if(extensionProperties.begin(), extensionProperties.end(),
                                       [&](auto& x) { return requestedRequiredExt.compare(x.extensionName); });

            if (result == extensionProperties.end())
            {
                throw Exceptions::InitialisationFailureException(
                    "The required Vulkan extension " + requestedRequiredExt +
                    " is not available on this device.");
            }
        }

        std::vector<std::string> finalOptionalExtensions{};

        for (auto&& requestedOptionalExt : EngineConfig::OptionalVulkanExtensions)
        {
            auto result = std::find_if(extensionProperties.begin(), extensionProperties.end(),
                                       [&](auto& x) { return requestedOptionalExt.compare(x.extensionName); });

            if (result == extensionProperties.end())
            {
                _logger.logWarning("The optional Vulkan extension " + requestedOptionalExt +
                                   " is not available on this device. Vulkan may not behave as you expect.");
                continue;
            }

            finalOptionalExtensions.emplace_back(requestedOptionalExt);
        }

        std::vector<std::string> allExtensions = EngineConfig::RequiredVulkanExtensions;
        allExtensions.insert(allExtensions.end(), finalOptionalExtensions.begin(), finalOptionalExtensions.end());
        return allExtensions;
    }

    std::vector<std::string> VulkanGraphicsDevice::GetFinalValidationLayerSet() const
    {
        uint32_t layerCount = 0;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> validationLayerProperties(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, validationLayerProperties.data());

        for (auto&& requestedRequiredLayer : EngineConfig::RequiredVulkanLayers)
        {
            auto result = std::find_if(validationLayerProperties.begin(), validationLayerProperties.end(),
                                       [&](auto& x) { return requestedRequiredLayer.compare(x.layerName); });

            if (result == validationLayerProperties.end())
            {
                throw Exceptions::InitialisationFailureException(
                    "The required Vulkan layer " + requestedRequiredLayer +
                    " is not available on this device.");
            }
        }

        std::vector<std::string> finalOptionalLayers{};

        for (auto&& requestedOptionalLayer : EngineConfig::OptionalVulkanLayers)
        {
            auto result = std::find_if(validationLayerProperties.begin(), validationLayerProperties.end(),
                                       [&](auto& x) { return requestedOptionalLayer.compare(x.layerName); });

            if (result == validationLayerProperties.end())
            {
                _logger.logWarning("The optional Vulkan layer " + requestedOptionalLayer +
                                   " is not available on this device. Vulkan may not behave as you expect.");
                continue;
            }

            finalOptionalLayers.emplace_back(requestedOptionalLayer);
        }

        std::vector<std::string> allValidationLayers = EngineConfig::RequiredVulkanLayers;
        allValidationLayers.insert(allValidationLayers.end(), finalOptionalLayers.begin(), finalOptionalLayers.end());
        return allValidationLayers;
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

        std::vector<std::string> allExtensions = GetFinalExtensionSet();
        std::vector<const char*> allExtensionPtrs = GetStringVectorAsCharPtrVector(allExtensions);
        size_t extensionLength = allExtensionPtrs.size();

        std::vector<std::string> allValidationLayers = GetFinalValidationLayerSet();
        std::vector<const char*> allValidationLayerPtrs  = GetStringVectorAsCharPtrVector(allValidationLayers);
        size_t validationLayerLength = allValidationLayers.size();

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensionLength);
        createInfo.ppEnabledExtensionNames = allExtensionPtrs.data();
        createInfo.ppEnabledLayerNames = allValidationLayerPtrs.data();
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayerLength);

        if (vkCreateInstance(&createInfo, nullptr, &_instance) != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to create an instance of Vulkan version 1.2.");
        }
    }

    void VulkanGraphicsDevice::Initialise()
    {
        CreateInstance();
        _logger.logInfoLine("Vulkan version 1.2 has been successfully initialised.");
    }

    void VulkanGraphicsDevice::TearDown()
    {
        vkDestroyInstance(_instance, nullptr);
    }
} // namespace NovelRT::Experimental::Graphics::Vulkan
