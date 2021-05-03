// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Experimental/EngineConfig.h>
#include <NovelRT/Experimental/Graphics/Vulkan/Graphics.Vulkan.h>
#include <NovelRT/Utilities/Misc.h>
#include <map>
#include <numeric>
#include <set>
#include <utility>

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
          _physicalDevice(VK_NULL_HANDLE),
          _device(VK_NULL_HANDLE),
          _graphicsQueue(VK_NULL_HANDLE),
          _presentQueue(VK_NULL_HANDLE),
          _surface(VK_NULL_HANDLE),
          _swapChain(VK_NULL_HANDLE),
          _swapChainImages(std::vector<VkImage>{}),
          _swapChainImageFormat(VkFormat{}),
          _swapChainExtent(VkExtent2D{}),
          _swapChainImageViews(std::vector<VkImageView>{})
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

    std::vector<std::string> VulkanGraphicsDevice::GetFinalInstanceExtensionSet() const
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

        for (auto&& requestedRequiredExt : EngineConfig::RequiredVulkanInstanceExtensions())
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

        for (auto&& requestedOptionalExt : EngineConfig::OptionalVulkanInstanceExtensions())
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

        std::vector<std::string> allExtensions = EngineConfig::RequiredVulkanInstanceExtensions();
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

    std::vector<std::string> VulkanGraphicsDevice::GetFinalPhysicalDeviceExtensionSet() const
    {
        uint32_t extensionCount = 0;
        vkEnumerateDeviceExtensionProperties(_physicalDevice, nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensionProperties(extensionCount);
        vkEnumerateDeviceExtensionProperties(_physicalDevice, nullptr, &extensionCount, extensionProperties.data());

        _logger.logInfoLine("Found the following available physical device extensions:");

        for (auto&& extensionProperty : extensionProperties)
        {
            _logger.logInfoLine("  Extension Name: " + std::string(extensionProperty.extensionName) +
                                "  Spec Version: " + std::to_string(extensionProperty.specVersion));
        }

        for (auto&& requestedRequiredExt : EngineConfig::RequiredVulkanPhysicalDeviceExtensions())
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

        for (auto&& requestedOptionalExt : EngineConfig::OptionalVulkanPhysicalDeviceExtensions())
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

        std::vector<std::string> allExtensions = EngineConfig::RequiredVulkanPhysicalDeviceExtensions();
        allExtensions.insert(allExtensions.end(), finalOptionalExtensions.begin(), finalOptionalExtensions.end());
        return allExtensions;
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
                _defaultFailureMessage +
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
            NovelRT::EngineConfig::OptionalVulkanInstanceExtensions().emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = EngineConfig::ApplicationName().c_str();
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = EngineConfig::EngineName().c_str();
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_2;

        _finalExtensionSet = GetFinalInstanceExtensionSet();
        std::vector<const char*> allExtensionPtrs = GetStringVectorAsCharPtrVector(_finalExtensionSet);
        size_t extensionLength = allExtensionPtrs.size();

        _finalValidationLayerSet = GetFinalValidationLayerSet();
        std::vector<const char*> allValidationLayerPtrs = GetStringVectorAsCharPtrVector(_finalValidationLayerSet);
        size_t validationLayerLength = allValidationLayerPtrs.size();

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
            throw Exceptions::InitialisationFailureException("Failed to initialise the VkInstance.", instanceResult);
        }

        _logger.logInfoLine("VkInstance successfully created.");
    }

    void VulkanGraphicsDevice::ConfigureOutputSurface(std::shared_ptr<IGraphicsSurface> targetSurface)
    {
        _nrtSurface = std::move(targetSurface);

        switch (_nrtSurface->GetKind())
        {
            case GraphicsSurfaceKind::Glfw:
            {
                auto func =
                    reinterpret_cast<VkResult (*)(VkInstance, void*, const VkAllocationCallbacks*, VkSurfaceKHR*)>(
                        _nrtSurface->GetContextHandle());

                VkResult funcResult = func(_instance, _nrtSurface->GetHandle(), nullptr, &_surface);
                if (funcResult != VK_SUCCESS)
                {
                    throw Exceptions::InitialisationFailureException("Failed to initialise the VkSurfaceKHR.",
                                                                     funcResult);
                }

                _logger.logInfoLine("VkSurfaceKHR successfully created.");
                break;
            }
            case GraphicsSurfaceKind::Unknown:
            case GraphicsSurfaceKind::Android:
            case GraphicsSurfaceKind::Wayland:
            case GraphicsSurfaceKind::Win32:
            case GraphicsSurfaceKind::Xcb:
            case GraphicsSurfaceKind::Xlib:
            default:
                throw Exceptions::NotSupportedException(
                    "The specified graphics surface kind is not supported by this graphics device.");
        }
    }

    QueueFamilyIndices VulkanGraphicsDevice::FindQueueFamilies(VkPhysicalDevice physicalDevice) const noexcept
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

            vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, familyIndex, _surface, &presentSupport);
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

    bool VulkanGraphicsDevice::CheckPhysicalDeviceRequiredExtensionSupport(
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

    int32_t VulkanGraphicsDevice::GetPhysicalDeviceOptionalExtensionSupportScore(
        VkPhysicalDevice physicalDevice) const noexcept
    {
        float currentPercentageValue = 0;

        uint32_t extensionCount = 0;
        vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, availableExtensions.data());

        std::set<std::string> optionalExtensionSet(EngineConfig::OptionalVulkanPhysicalDeviceExtensions().begin(),
                                                   EngineConfig::OptionalVulkanPhysicalDeviceExtensions().end());

        float percentageStep = (1.0f / optionalExtensionSet.size()) * 100;

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

    SwapChainSupportDetails VulkanGraphicsDevice::QuerySwapChainSupport(VkPhysicalDevice physicalDevice) const noexcept
    {
        SwapChainSupportDetails returnDetails;
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, _surface, &returnDetails.capabilities);

        uint32_t formatCount = 0;
        vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, _surface, &formatCount, nullptr);

        if (formatCount != 0)
        {
            returnDetails.formats.resize(formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, _surface, &formatCount, returnDetails.formats.data());
        }

        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, _surface, &presentModeCount, nullptr);

        if (presentModeCount != 0)
        {
            returnDetails.presentModes.resize(presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, _surface, &presentModeCount,
                                                      returnDetails.presentModes.data());
        }

        return returnDetails;
    }

    int32_t VulkanGraphicsDevice::RateDeviceSuitability(VkPhysicalDevice physicalDevice) const noexcept
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

        score += deviceProperties.limits.maxImageDimension2D;
        score += GetPhysicalDeviceOptionalExtensionSupportScore(physicalDevice);

        SwapChainSupportDetails supportDetails = QuerySwapChainSupport(physicalDevice);

        QueueFamilyIndices indices = FindQueueFamilies(physicalDevice);
        if (deviceFeatures.geometryShader == VK_FALSE || !indices.IsComplete() ||
            !CheckPhysicalDeviceRequiredExtensionSupport(physicalDevice) || supportDetails.formats.empty() ||
            supportDetails.presentModes.empty())
        {
            score = -1;
        }

        return score;
    }

    void VulkanGraphicsDevice::PickPhysicalDevice()
    {
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(_instance, &deviceCount, nullptr);

        if (deviceCount == 0)
        {
            throw Exceptions::NotSupportedException(_defaultFailureMessage +
                                                    "A Vulkan-compatible GPU was not found. Please refer "
                                                    "to your GPU manufacturer's documentation for more information.");
        }

        EngineConfig::RequiredVulkanPhysicalDeviceExtensions().emplace_back(
            std::string(VK_KHR_SWAPCHAIN_EXTENSION_NAME));

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(_instance, &deviceCount, devices.data());

        std::multimap<int32_t, VkPhysicalDevice> candidates{};

        for (const auto& device : devices)
        {
            candidates.emplace(RateDeviceSuitability(device), device);
        }

        if (candidates.rbegin()->first <= 0)
        {
            throw Exceptions::NotSupportedException(
                _defaultFailureMessage +
                "None of the supplied Vulkan-compatible GPUs were deemed suitable for the NovelRT render pipeline. "
                "Please refer to the NovelRT documentation and your GPU manufacturer's documentation for more "
                "information.");
        }

        _physicalDevice = candidates.rbegin()->second;

        VkPhysicalDeviceProperties deviceProperties;
        vkGetPhysicalDeviceProperties(_physicalDevice, &deviceProperties);
        _logger.logInfoLine("GPU device successfully chosen: " + std::string(deviceProperties.deviceName));
    }

    void VulkanGraphicsDevice::CreateLogicalDevice()
    {
        QueueFamilyIndices indices = FindQueueFamilies(_physicalDevice);

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos{};
        std::set<uint32_t> uniqueQueueFamilies{indices.graphicsFamily.value(), indices.presentFamily.value()};

        float queuePriority = 1.0f;
        for (uint32_t queueFamily : uniqueQueueFamilies)
        {
            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamily;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }

        auto physicalDeviceExtensions = GetFinalPhysicalDeviceExtensionSet();
        auto physicalDeviceExtensionPtrs = GetStringVectorAsCharPtrVector(physicalDeviceExtensions);

        VkPhysicalDeviceFeatures deviceFeatures{};

        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        createInfo.pQueueCreateInfos = queueCreateInfos.data();
        createInfo.pEnabledFeatures = &deviceFeatures;
        createInfo.enabledExtensionCount = static_cast<uint32_t>(physicalDeviceExtensionPtrs.size());
        createInfo.ppEnabledExtensionNames = physicalDeviceExtensionPtrs.data();

        if (_debuggerWasCreated)
        {
            createInfo.enabledLayerCount = static_cast<uint32_t>(_finalValidationLayerSet.size());
            std::vector<const char*> allValidationLayerPtrs = GetStringVectorAsCharPtrVector(_finalValidationLayerSet);
            createInfo.ppEnabledLayerNames = allValidationLayerPtrs.data();
        }
        else
        {
            createInfo.enabledLayerCount = 0;
        }

        VkResult deviceResult = vkCreateDevice(_physicalDevice, &createInfo, nullptr, &_device);

        if (deviceResult != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to initialise the VkDevice.", deviceResult);
        }

        vkGetDeviceQueue(_device, indices.graphicsFamily.value(), 0, &_graphicsQueue);
        vkGetDeviceQueue(_device, indices.presentFamily.value(), 0, &_presentQueue);

        _logger.logInfoLine("VkDevice successfully created.");
    }

    VkSurfaceFormatKHR VulkanGraphicsDevice::ChooseSwapSurfaceFormat(
        const std::vector<VkSurfaceFormatKHR>& availableFormats) const noexcept
    {
        VkSurfaceFormatKHR returnFormat{};
        returnFormat.format = VK_FORMAT_UNDEFINED;

        for (const auto& availableFormat : availableFormats)
        {
            if (availableFormat.format == VK_FORMAT_R8G8B8A8_UNORM ||
                availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM)
            {
                if (returnFormat.format != VK_FORMAT_R8G8B8A8_UINT)
                {
                    returnFormat = availableFormat;
                }
            }
        }

        if (returnFormat.format == VK_FORMAT_UNDEFINED)
        {
            _logger.logWarningLine(
                "Vulkan was unable to detect one of the preferred VkFormats for the specified surface. The first "
                "format found is now being used. This may result in unexpected behaviour.");

            returnFormat = availableFormats[0];
        }
        else
        {
            _logger.logInfo("Preferred VkFormat detected.");
        }

        return returnFormat;
    }

    // TODO: freesync and gsync support will go here in a later PR.
    VkPresentModeKHR VulkanGraphicsDevice::ChooseSwapPresentMode(
        const std::vector<VkPresentModeKHR>& /*availablePresentModes*/) const noexcept
    {
        return VK_PRESENT_MODE_FIFO_KHR;
    }

    VkExtent2D VulkanGraphicsDevice::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) const noexcept
    {
        if (capabilities.currentExtent.width != UINT32_MAX)
        {
            return capabilities.currentExtent;
        }

        auto localSize = _nrtSurface->GetSize();

        VkExtent2D actualExtent = {static_cast<uint32_t>(localSize.x), static_cast<uint32_t>(localSize.y)};

        actualExtent.width = std::max(capabilities.minImageExtent.width,
                                      std::min(capabilities.maxImageExtent.width, actualExtent.width));
        actualExtent.height = std::max(capabilities.minImageExtent.height,
                                       std::min(capabilities.maxImageExtent.height, actualExtent.height));

        return actualExtent;
    }

    void VulkanGraphicsDevice::CreateSwapChain()
    {
        SwapChainSupportDetails swapChainSupport = QuerySwapChainSupport(_physicalDevice);

        VkSurfaceFormatKHR surfaceFormat = ChooseSwapSurfaceFormat(swapChainSupport.formats);
        VkPresentModeKHR presentMode = ChooseSwapPresentMode(swapChainSupport.presentModes);
        VkExtent2D extent = ChooseSwapExtent(swapChainSupport.capabilities);
        uint32_t imageCount = swapChainSupport.capabilities.minImageCount +
                              1; // this variable gets re-used for the actual image count later

        if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount)
        {
            imageCount = swapChainSupport.capabilities.maxImageCount;
        }

        VkSwapchainCreateInfoKHR createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        createInfo.surface = _surface;
        createInfo.minImageCount = imageCount;
        createInfo.imageFormat = surfaceFormat.format;
        createInfo.imageColorSpace = surfaceFormat.colorSpace;
        createInfo.imageExtent = extent;
        createInfo.imageArrayLayers = 1;
        createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        QueueFamilyIndices indices = FindQueueFamilies(_physicalDevice);
        uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(), indices.presentFamily.value()};

        if (indices.graphicsFamily != indices.presentFamily)
        {
            createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            createInfo.queueFamilyIndexCount = 2;
            createInfo.pQueueFamilyIndices = queueFamilyIndices;
        }
        else
        {
            createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
            createInfo.queueFamilyIndexCount = 0;
            createInfo.pQueueFamilyIndices = nullptr;
        }

        createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
        createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        createInfo.presentMode = presentMode;
        createInfo.clipped = VK_TRUE;
        createInfo.oldSwapchain = VK_NULL_HANDLE;

        VkResult swapChainResult = vkCreateSwapchainKHR(_device, &createInfo, nullptr, &_swapChain);
        if (swapChainResult != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to create the VkSwapchainKHR.", swapChainResult);
        }

        _logger.logInfoLine("VkSwapchainKHR successfully created. Retrieving VkImages...");

        VkResult imagesKHRQuery = vkGetSwapchainImagesKHR(_device, _swapChain, &imageCount, nullptr);

        if (imagesKHRQuery != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to retrieve the VkImages from the VkSwapchainKHR.",
                                                             imagesKHRQuery);
        }

        _swapChainImages.resize(imageCount);
        imagesKHRQuery = vkGetSwapchainImagesKHR(_device, _swapChain, &imageCount, _swapChainImages.data());

        if (imagesKHRQuery != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to retrieve the VkImages from the VkSwapchainKHR.",
                                                             imagesKHRQuery);
        }

        _swapChainImageFormat = surfaceFormat.format;
        _swapChainExtent = extent;

        _logger.logInfoLine("VkImages successfully retrieved.");
    }

    void VulkanGraphicsDevice::CreateImageViews()
    {
        _swapChainImageViews.resize(_swapChainImages.size());

        for (size_t i = 0; i < _swapChainImages.size(); i++)
        {
            VkImageViewCreateInfo createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            createInfo.image = _swapChainImages[i];
            createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
            createInfo.format = _swapChainImageFormat;
            createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            createInfo.subresourceRange.baseMipLevel = 0;
            createInfo.subresourceRange.levelCount = 1;
            createInfo.subresourceRange.baseArrayLayer = 0;
            createInfo.subresourceRange.layerCount = 1;

            VkResult imageViewResult = vkCreateImageView(_device, &createInfo, nullptr, &_swapChainImageViews[i]);

            if (imageViewResult != VK_SUCCESS)
            {
                throw Exceptions::InitialisationFailureException(
                    "Failed to initialise a VkImageView onto the provided VkImage.", imageViewResult);
            }
        }

        _logger.logInfoLine("Successfully initialised VkImageViews.");
    }

    void VulkanGraphicsDevice::Initialise(std::shared_ptr<IGraphicsSurface> targetSurface)
    {
        CreateInstance();

        if (EngineConfig::EnableDebugOutputFromEngineInternals())
        {
            ConfigureDebugLogger();
        }

        ConfigureOutputSurface(targetSurface);

        PickPhysicalDevice();
        CreateLogicalDevice();
        CreateSwapChain();
        CreateImageViews();

        _logger.logInfoLine("Vulkan version 1.2 has been successfully initialised.");
    }

    void VulkanGraphicsDevice::TearDown()
    {
        for (auto&& imageView : _swapChainImageViews)
        {
            vkDestroyImageView(_device, imageView, nullptr);
        }

        vkDestroySwapchainKHR(_device, _swapChain, nullptr);
        vkDestroySurfaceKHR(_instance, _surface, nullptr);
        vkDestroyDevice(_device, nullptr);

        if (_debuggerWasCreated)
        {
            DestroyDebugUtilsMessengerEXT(_instance, _debugLogger, nullptr);
        }

        vkDestroyInstance(_instance, nullptr);

        _logger.logInfoLine("Vulkan version 1.2 instance successfully torn down.");
    }

    std::shared_ptr<ShaderProgram> VulkanGraphicsDevice::CreateShaderProgram(std::string entryPointName,
                                                                             ShaderProgramKind kind,
                                                                             gsl::span<uint8_t> byteData)
    {
        return std::shared_ptr<ShaderProgram>(
            new VulkanShaderProgram(*this, std::move(entryPointName), kind, byteData));
    }

    VulkanGraphicsDevice::~VulkanGraphicsDevice()
    {
        TearDown();
    }
} // namespace NovelRT::Experimental::Graphics::Vulkan
