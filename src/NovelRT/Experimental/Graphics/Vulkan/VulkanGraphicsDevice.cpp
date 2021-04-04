// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/Exceptions.h>
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
                    "The required Vulkan extension " + requestedRequiredExt + " is not available on this device.");
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
                    "The required Vulkan layer " + requestedRequiredLayer + " is not available on this device.");
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
        std::vector<const char*> allValidationLayerPtrs = GetStringVectorAsCharPtrVector(allValidationLayers);
        size_t validationLayerLength = allValidationLayers.size();

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensionLength);
        createInfo.ppEnabledExtensionNames = allExtensionPtrs.data();
        createInfo.ppEnabledLayerNames = allValidationLayerPtrs.data();
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayerLength);

        VkResult instanceResult = vkCreateInstance(&createInfo, nullptr, &_instance);
        if (instanceResult != VK_SUCCESS)
        {
            std::string defaultFailureMessage = "Failed to initialise Vulkan version 1.2. Reason: ";
            //this was originally going to be a switch, but compiler warnings as errors, lol
            if (instanceResult == VK_ERROR_OUT_OF_HOST_MEMORY)
            {
                throw Exceptions::OutOfMemoryException(
                    defaultFailureMessage + "The host ran out of memory before the operation could complete.");
            }
            else if (instanceResult == VK_ERROR_OUT_OF_DEVICE_MEMORY)
            {
                throw Exceptions::OutOfMemoryException(
                    defaultFailureMessage + "The device ran out of memory before the operation could complete.");
            }
            else if (instanceResult == VK_ERROR_INITIALIZATION_FAILED)
            {
                throw Exceptions::InitialisationFailureException(
                    defaultFailureMessage + "The VkInstance could not be initialised correctly. This could indicate a "
                                            "problem with the VK implementation.");
            }
            else if (instanceResult == VK_ERROR_LAYER_NOT_PRESENT)
            {
                throw Exceptions::InitialisationFailureException(
                    defaultFailureMessage + "The requested VkLayer was found originally, but could not be found during "
                                            "initialisation of the VkInstance.");
            }
            else if (instanceResult == VK_ERROR_EXTENSION_NOT_PRESENT)
            {
                throw Exceptions::InitialisationFailureException(
                    defaultFailureMessage +
                    "The requested VkExtension was found originally, but could not be found during "
                    "initialisation of the VkInstance.");
            }
            else if (instanceResult == VK_ERROR_INCOMPATIBLE_DRIVER)
            {
                throw Exceptions::InitialisationFailureException(
                    defaultFailureMessage +
                    "The device driver is not compatible with either this version of Vulkan, or Vulkan in its "
                    "entirety. Please check your GPU vendor for additional information.");
            }
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
