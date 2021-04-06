// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/Exceptions.h>
#include <NovelRT/Experimental/EngineConfig.h>
#include <NovelRT/Experimental/Graphics/Vulkan/VulkanGraphicsDevice.h>
#include <NovelRT/Utilities/Misc.h>
#include <numeric>

namespace NovelRT::Experimental::Graphics::Vulkan
{
    VKAPI_ATTR VkBool32 VKAPI_CALL
    VulkanGraphicsDevice::DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                        VkDebugUtilsMessageTypeFlagsEXT /*messageType*/,
                                        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                                        void* pUserData)
    {
        LogLevel logLevel = LogLevel::Off;
        switch (messageSeverity)
        {
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
                logLevel = LogLevel::Debug;
                break;
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
                logLevel = LogLevel::Info;
                break;
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
                logLevel = LogLevel::Warn;
                break;
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
                logLevel = LogLevel::Err;
                break;
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_FLAG_BITS_MAX_ENUM_EXT:
                throw Exceptions::NotSupportedException("A Vk debug utils message cannot be all the types at once.");
        }

        if (logLevel != LogLevel::Off && logLevel >= EngineConfig::MinimumInternalLoggingLevel())
        {
            reinterpret_cast<VulkanGraphicsDevice*>(pUserData)->_logger.log(std::string(pCallbackData->pMessage),
                                                                            logLevel);
        }

        return VK_FALSE;
    }

    VkResult VulkanGraphicsDevice::CreateDebugUtilsMessengerEXT(VkInstance instance,
                                                                const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
                                                                const VkAllocationCallbacks* pAllocator,
                                                                VkDebugUtilsMessengerEXT* pDebugMessenger) noexcept
    {
        auto func = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(
            vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT"));

        if (func != nullptr)
        {
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        }

        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }

    void VulkanGraphicsDevice::DestroyDebugUtilsMessengerEXT(VkInstance instance,
                                                             VkDebugUtilsMessengerEXT debugMessenger,
                                                             const VkAllocationCallbacks* pAllocator) noexcept
    {
        auto func = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(
            vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT"));
        if (func != nullptr)
        {
            func(instance, debugMessenger, pAllocator);
        }
    }

    VulkanGraphicsDevice::VulkanGraphicsDevice() noexcept
        : _instance(VK_NULL_HANDLE),
          _logger(LoggingService(Utilities::Misc::CONSOLE_LOG_GFX)),
          _debugLogger(VK_NULL_HANDLE),
          _debuggerWasCreated(false),
          _physicalDevice(VK_NULL_HANDLE)
    {
    }

    std::vector<const char*> VulkanGraphicsDevice::GetStringVectorAsCharPtrVector(
        const std::vector<std::string>& target) noexcept
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

        _logger.logInfoLine("Found the following available instance extensions:");

        for (auto&& extensionProperty : extensionProperties)
        {
            _logger.logInfoLine("  Extension Name: " + std::string(extensionProperty.extensionName) +
                                "  Spec Version: " + std::to_string(extensionProperty.specVersion));
        }

        for (auto&& requestedRequiredExt : EngineConfig::RequiredVulkanExtensions())
        {
            auto result = std::find_if(extensionProperties.begin(), extensionProperties.end(), [&](auto& x) {
                return strcmp(requestedRequiredExt.c_str(), x.extensionName) == 0;
            });

            if (result == extensionProperties.end())
            {
                throw Exceptions::InitialisationFailureException(
                    "The required Vulkan extension " + requestedRequiredExt + " is not available on this device.");
            }
        }

        std::vector<std::string> finalOptionalExtensions{};

        for (auto&& requestedOptionalExt : EngineConfig::OptionalVulkanExtensions())
        {
            auto result = std::find_if(extensionProperties.begin(), extensionProperties.end(), [&](auto& x) {
                return strcmp(requestedOptionalExt.c_str(), x.extensionName) == 0;
            });

            if (result == extensionProperties.end())
            {
                _logger.logWarningLine("The optional Vulkan extension " + requestedOptionalExt +
                                       " is not available on this device. Vulkan may not behave as you expect.");
                continue;
            }

            finalOptionalExtensions.emplace_back(requestedOptionalExt);
        }

        std::vector<std::string> allExtensions = EngineConfig::RequiredVulkanExtensions();
        allExtensions.insert(allExtensions.end(), finalOptionalExtensions.begin(), finalOptionalExtensions.end());
        return allExtensions;
    }

    std::vector<std::string> VulkanGraphicsDevice::GetFinalValidationLayerSet() const
    {
        uint32_t layerCount = 0;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> layerProperties(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, layerProperties.data());

        _logger.logInfoLine("Found the following available instance layers:");

        for (auto&& layerProperty : layerProperties)
        {
            std::string specVersion = std::to_string(VK_VERSION_MAJOR(layerProperty.specVersion)) + "." +
                                      std::to_string(VK_VERSION_MINOR(layerProperty.specVersion)) + "." +
                                      std::to_string(VK_VERSION_PATCH(layerProperty.specVersion));

            _logger.logInfoLine("  Layer Name: " + std::string(layerProperty.layerName) + "  Spec Version: " +
                                specVersion + "  Impl Version: " + std::to_string(layerProperty.implementationVersion) +
                                "  Description:  " + std::string(layerProperty.description));
        }

        for (auto&& requestedRequiredLayer : EngineConfig::RequiredVulkanLayers())
        {
            auto result = std::find_if(layerProperties.begin(), layerProperties.end(), [&](auto& x) {
                return strcmp(requestedRequiredLayer.c_str(), x.layerName) == 0;
            });

            if (result == layerProperties.end())
            {
                throw Exceptions::InitialisationFailureException("The required Vulkan layer " + requestedRequiredLayer +
                                                                 " is not available on this device.");
            }
        }

        std::vector<std::string> finalOptionalLayers{};

        for (auto&& requestedOptionalLayer : EngineConfig::OptionalVulkanLayers())
        {
            auto result = std::find_if(layerProperties.begin(), layerProperties.end(),
                                       [&](auto& x) { return strcmp(requestedOptionalLayer.c_str(), x.layerName); });

            if (result == layerProperties.end())
            {
                _logger.logWarningLine("The optional Vulkan layer " + requestedOptionalLayer +
                                       " is not available on this device. Vulkan may not behave as you expect.");
                continue;
            }

            finalOptionalLayers.emplace_back(requestedOptionalLayer);
        }

        std::vector<std::string> allValidationLayers = EngineConfig::RequiredVulkanLayers();
        allValidationLayers.insert(allValidationLayers.end(), finalOptionalLayers.begin(), finalOptionalLayers.end());
        return allValidationLayers;
    }

    void VulkanGraphicsDevice::CreateDefaultDebugCreateInfoStruct(
        VkDebugUtilsMessengerCreateInfoEXT& outputResult) noexcept
    {
        outputResult = {};
        outputResult.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        outputResult.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                                       VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                                       VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        outputResult.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                                   VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                                   VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        outputResult.pfnUserCallback = DebugCallback;
        outputResult.pUserData = this;
    }

    void VulkanGraphicsDevice::ConfigureDebugLogger()
    {
        VkDebugUtilsMessengerCreateInfoEXT createInfo{};
        CreateDefaultDebugCreateInfoStruct(createInfo);

        VkResult debuggerResult = CreateDebugUtilsMessengerEXT(_instance, &createInfo, nullptr, &_debugLogger);

        if (debuggerResult == VK_ERROR_OUT_OF_HOST_MEMORY)
        {
            throw Exceptions::OutOfMemoryException(
                defaultFailureMessage +
                "The host ran out of memory before the VkDebugUtilsMessengerEXT could be created.");
        }
        else if (debuggerResult == VK_ERROR_EXTENSION_NOT_PRESENT)
        {
            _logger.logErrorLine("The VkDebugUtils could not be located and/or loaded on this device. Vulkan logging "
                                 "and validation output will not be displayed.");
            return;
        }

        _debuggerWasCreated = true;
        _logger.logWarningLine("Vulkan debugger enabled! This may harm performance.");
    }

    void VulkanGraphicsDevice::CreateInstance()
    {
        if (EngineConfig::EnableDebugOutputFromEngineInternals())
        {
            NovelRT::EngineConfig::OptionalVulkanLayers().emplace_back("VK_LAYER_KHRONOS_validation");
            NovelRT::EngineConfig::OptionalVulkanExtensions().emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = EngineConfig::ApplicationName().c_str();
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = EngineConfig::EngineName().c_str();
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

        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};

        if (EngineConfig::EnableDebugOutputFromEngineInternals())
        {
            CreateDefaultDebugCreateInfoStruct(debugCreateInfo);
            createInfo.pNext = &debugCreateInfo;
        }
        else
        {
            createInfo.pNext = nullptr;
        }

        VkResult instanceResult = vkCreateInstance(&createInfo, nullptr, &_instance);
        if (instanceResult != VK_SUCCESS)
        {
            // this was originally going to be a switch, but compiler warnings as errors, lol
            if (instanceResult == VK_ERROR_OUT_OF_HOST_MEMORY)
            {
                throw Exceptions::OutOfMemoryException(
                    defaultFailureMessage + "The host ran out of memory before the VkInstance could be created.");
            }
            else if (instanceResult == VK_ERROR_OUT_OF_DEVICE_MEMORY)
            {
                throw Exceptions::OutOfMemoryException(
                    defaultFailureMessage + "The device ran out of memory before the VkInstance could be created.");
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

        _logger.logInfoLine("VkInstance successfully created.");
    }

    bool VulkanGraphicsDevice::IsDeviceSuitable(VkPhysicalDevice device)
    {
        VkPhysicalDeviceProperties deviceProperties;
        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);
        vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

        return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
               deviceFeatures.geometryShader;
    }

    void VulkanGraphicsDevice::PickPhysicalDevice()
    {
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(_instance, &deviceCount, nullptr);

        if (deviceCount == 0)
        {
            throw Exceptions::NotSupportedException("A Vulkan-compatible GPU was not found. Please refer "
                                                    "to your GPU manufacturer's documentation for more information.");
        }

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(_instance, &deviceCount, devices.data());

        for (const auto& device : devices)
        {
            if (!IsDeviceSuitable(device))
            {
                continue;
            }
        }

        if (_physicalDevice == VK_NULL_HANDLE)
        {
            throw Exceptions::NotSupportedException(
                "None of the supplied Vulkan-compatible GPUs were deemed suitable for the NovelRT render pipeline. "
                "Please refer to the NovelRT documentation and your GPU manufacturer's documentation for more "
                "information.");
        }
    }

    void VulkanGraphicsDevice::Initialise()
    {
        CreateInstance();

        if (EngineConfig::EnableDebugOutputFromEngineInternals())
        {
            ConfigureDebugLogger();
        }

        //PickPhysicalDevice();

        _logger.logInfoLine("Vulkan version 1.2 has been successfully initialised.");
    }

    void VulkanGraphicsDevice::TearDown()
    {
        if (_debuggerWasCreated)
        {
            DestroyDebugUtilsMessengerEXT(_instance, _debugLogger, nullptr);
        }

        vkDestroyInstance(_instance, nullptr);
    }
} // namespace NovelRT::Experimental::Graphics::Vulkan
