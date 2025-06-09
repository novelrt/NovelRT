// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InitialisationFailureException.hpp>
#include <NovelRT/Exceptions/NotSupportedException.hpp>
#include <NovelRT/Exceptions/OutOfMemoryException.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsAdapter.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsProvider.hpp>
#include <NovelRT/Logging/BuiltInLogSections.hpp>
#include <NovelRT/Utilities/Strings.hpp>

#include <atomic>

namespace NovelRT::Graphics
{
    using VulkanGraphicsAdapter = GraphicsAdapter<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsProvider = GraphicsProvider<Vulkan::VulkanGraphicsBackend>;

    VKAPI_ATTR VkBool32 VKAPI_CALL static DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                        VkDebugUtilsMessageTypeFlagsEXT /*messageType*/,
                                                        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                                                        void* pUserData)
    {
        LoggingService* logger = static_cast<LoggingService*>(pUserData);

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
                logger->logWarningLine("Unable to map from vulkan message severity, assuming error");
                logLevel = LogLevel::Err;
                break;
        }

        // TODO: EngineConfig was here
        if (logLevel != LogLevel::Off && logLevel >= LogLevel::Debug) // EngineConfig::MinimumInternalLoggingLevel())
        {
            logger->log(std::string(pCallbackData->pMessage), logLevel);
        }

        return VK_FALSE;
    }

    static PFN_vkCreateDebugUtilsMessengerEXT cached_vkCreateDebugUtilsMessengerEXT = nullptr;
    static VkResult CreateDebugUtilsMessengerEXT(VkInstance instance,
                                                 const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
                                                 const VkAllocationCallbacks* pAllocator,
                                                 VkDebugUtilsMessengerEXT* pDebugMessenger)
    {
        PFN_vkCreateDebugUtilsMessengerEXT func = cached_vkCreateDebugUtilsMessengerEXT;

        if (func == nullptr)
        {
            void* actual = reinterpret_cast<void*>(vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT"));
            if (actual == nullptr)
            {
                return VK_ERROR_EXTENSION_NOT_PRESENT;
            }

            cached_vkCreateDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(actual);
            func = cached_vkCreateDebugUtilsMessengerEXT;
        }

        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    }

    static PFN_vkDestroyDebugUtilsMessengerEXT cached_vkDestroyDebugUtilsMessengerEXT = nullptr;
    static void DestroyDebugUtilsMessengerEXT(VkInstance instance,
                                              VkDebugUtilsMessengerEXT debugMessenger,
                                              const VkAllocationCallbacks* pAllocator)
    {
        PFN_vkDestroyDebugUtilsMessengerEXT func = cached_vkDestroyDebugUtilsMessengerEXT;

        if (func == nullptr)
        {
            void* actual = reinterpret_cast<void*>(vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT"));
            if (actual == nullptr)
            {
                return;
            }

            cached_vkDestroyDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(actual);
            func = cached_vkDestroyDebugUtilsMessengerEXT;
        }

        func(instance, debugMessenger, pAllocator);
    }

    static std::vector<std::string> GetAvailableInstanceExtensions(const LoggingService& logger,
                                                                   std::vector<std::string> requiredInstanceExtensions,
                                                                   std::vector<std::string> optionalInstanceExtensions)
    {
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensionProperties(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensionProperties.data());

        logger.logInfoLine("Found the following available instance extensions:");

        for (auto&& extensionProperty : extensionProperties)
        {
            logger.logInfoLine("  Extension Name: '" + std::string(extensionProperty.extensionName) +
                               "' Spec Version: " + std::to_string(extensionProperty.specVersion));
        }

        for (auto&& requestedRequiredExt : requiredInstanceExtensions)
        {
            auto result = std::find_if(extensionProperties.begin(), extensionProperties.end(), [&](auto& x)
                                       { return strcmp(requestedRequiredExt.c_str(), x.extensionName) == 0; });

            if (result == extensionProperties.end())
            {
                throw Exceptions::InitialisationFailureException(
                    "The required Vulkan extension " + requestedRequiredExt + " is not available on this device.");
            }
        }

        std::vector<std::string> finalOptionalExtensions{};

        for (auto&& requestedOptionalExt : optionalInstanceExtensions)
        {
            auto result = std::find_if(extensionProperties.begin(), extensionProperties.end(), [&](auto& x)
                                       { return strcmp(requestedOptionalExt.c_str(), x.extensionName) == 0; });

            if (result == extensionProperties.end())
            {
                logger.logWarningLine("The optional Vulkan extension " + requestedOptionalExt +
                                      " is not available on this device. Vulkan may not behave as you expect.");
                continue;
            }

            finalOptionalExtensions.emplace_back(requestedOptionalExt);
        }

        std::vector<std::string> allExtensions{requiredInstanceExtensions};
        allExtensions.reserve(requiredInstanceExtensions.size() + finalOptionalExtensions.size());
        allExtensions.insert(allExtensions.end(), finalOptionalExtensions.begin(), finalOptionalExtensions.end());

        logger.logInfoLine("Enabled extensions:");
        for (const auto& ext : allExtensions)
        {
            logger.logInfoLine("  " + ext);
        }

        return allExtensions;
    }

    static std::vector<std::string> GetAvailableInstanceLayers(const LoggingService& logger,
                                                               std::vector<std::string> requiredInstanceLayers,
                                                               std::vector<std::string> optionalInstanceLayers)
    {
        uint32_t layerCount = 0;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> layerProperties(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, layerProperties.data());

        logger.logInfoLine("Found the following available instance layers:");

        for (auto&& layerProperty : layerProperties)
        {
            std::string specVersion = std::to_string(VK_VERSION_MAJOR(layerProperty.specVersion)) + "." +
                                      std::to_string(VK_VERSION_MINOR(layerProperty.specVersion)) + "." +
                                      std::to_string(VK_VERSION_PATCH(layerProperty.specVersion));

            logger.logInfoLine("  Layer Name: '" + std::string(layerProperty.layerName) + "' Spec Version: " +
                               specVersion + " Impl Version: " + std::to_string(layerProperty.implementationVersion) +
                               " Description: " + std::string(layerProperty.description));
        }

        for (auto&& requestedRequiredLayer : requiredInstanceLayers)
        {
            auto result = std::find_if(layerProperties.begin(), layerProperties.end(), [&](auto& x)
                                       { return strcmp(requestedRequiredLayer.c_str(), x.layerName) == 0; });

            if (result == layerProperties.end())
            {
                throw Exceptions::InitialisationFailureException("The required Vulkan layer " + requestedRequiredLayer +
                                                                 " is not available on this device.");
            }
        }

        std::vector<std::string> finalOptionalLayers{};

        for (auto&& requestedOptionalLayer : optionalInstanceLayers)
        {
            auto result = std::find_if(layerProperties.begin(), layerProperties.end(),
                                       [&](auto& x) { return strcmp(requestedOptionalLayer.c_str(), x.layerName); });

            if (result == layerProperties.end())
            {
                logger.logWarningLine("The optional Vulkan layer " + requestedOptionalLayer +
                                      " is not available on this device. Vulkan may not behave as you expect.");
                continue;
            }

            finalOptionalLayers.emplace_back(requestedOptionalLayer);
        }

        // TODO: EngineConfig was here
        std::vector<std::string> allLayers{requiredInstanceLayers};
        allLayers.reserve(requiredInstanceLayers.size() + finalOptionalLayers.size());
        allLayers.insert(allLayers.end(), finalOptionalLayers.begin(), finalOptionalLayers.end());
        return allLayers;
    }

    static VkInstance CreateInstance(VkApplicationInfo appInfo,
                                     std::vector<std::string> instanceExtensions,
                                     std::vector<std::string> instanceLayers,
                                     VkDebugUtilsMessengerCreateInfoEXT* debugLogger,
                                     std::vector<VkValidationFeatureEnableEXT> enabledValidationFeatures,
                                     std::vector<VkValidationFeatureDisableEXT> disabledValidationFeatures)
    {
        std::vector<const char*> instanceExtensionPtrs =
            NovelRT::Utilities::GetStringSpanAsCharPtrVector(instanceExtensions);
        size_t extensionCount = instanceExtensionPtrs.size();

        std::vector<const char*> instanceLayerPtrs = NovelRT::Utilities::GetStringSpanAsCharPtrVector(instanceLayers);
        size_t layerCount = instanceLayerPtrs.size();

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensionCount);
        createInfo.ppEnabledExtensionNames = instanceExtensionPtrs.data();
        createInfo.ppEnabledLayerNames = instanceLayerPtrs.data();
        createInfo.enabledLayerCount = static_cast<uint32_t>(layerCount);

#ifdef __APPLE__
        createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
#endif

        const void** pNextPointer = &createInfo.pNext;
        if (debugLogger != nullptr)
        {
            *pNextPointer = debugLogger;
            pNextPointer = &debugLogger->pNext;
        }

        VkValidationFeaturesEXT validationFeatures{};
        if (!enabledValidationFeatures.empty() || !disabledValidationFeatures.empty())
        {
            validationFeatures.sType = VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT;
            validationFeatures.enabledValidationFeatureCount = enabledValidationFeatures.size();
            validationFeatures.pEnabledValidationFeatures = enabledValidationFeatures.data();
            validationFeatures.disabledValidationFeatureCount = disabledValidationFeatures.size();
            validationFeatures.pDisabledValidationFeatures = disabledValidationFeatures.data();

            *pNextPointer = &validationFeatures;
            pNextPointer = &validationFeatures.pNext;
        }

        *pNextPointer = nullptr;
        pNextPointer = nullptr;

        VkInstance returnInstance = VK_NULL_HANDLE;
        VkResult instanceResult = vkCreateInstance(&createInfo, nullptr, &returnInstance);
        if (instanceResult != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to initialise the VkInstance.", instanceResult);
        }

        return returnInstance;
    }

    static std::vector<std::shared_ptr<VulkanGraphicsAdapter>> GetGraphicsAdapters(
        const std::shared_ptr<VulkanGraphicsProvider>& provider)
    {
        VkInstance instance = provider->GetVulkanInstance();

        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

        std::vector<std::shared_ptr<VulkanGraphicsAdapter>> adapters(devices.size());
        std::transform(devices.begin(), devices.end(), adapters.begin(), [&provider](const auto& device)
                       { return std::make_shared<VulkanGraphicsAdapter>(provider, device); });

        return adapters;
    }

    static void CheckDeviceCount(VkInstance instance)
    {
        uint32_t deviceCount = 0;
        const VkResult result = vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

        if (result == VK_ERROR_INITIALIZATION_FAILED || deviceCount == 0)
        {
            throw Exceptions::NotSupportedException("Failed to initialise Vulkan: A Vulkan-compatible GPU was not "
                                                    "found. Please refer to your GPU manufacturer's documentation "
                                                    "for more information.");
        }

        else if (result == VK_ERROR_OUT_OF_HOST_MEMORY || result == VK_ERROR_OUT_OF_DEVICE_MEMORY)
        {
            throw Exceptions::InitialisationFailureException(
                "Failed to initialise Vulkan: unable to allocate enough memory"
                "while enumerating attached compatible devices.");
        }
    }

    VulkanGraphicsProvider::GraphicsProvider(bool enableDebugMode,
                                             std::vector<std::string> requiredInstanceExtensions,
                                             std::vector<std::string> optionalInstanceExtensions,
                                             std::vector<std::string> requiredInstanceLayers,
                                             std::vector<std::string> optionalInstanceLayers)
        : _vulkanInstance(VK_NULL_HANDLE),
          _debugLogger(VK_NULL_HANDLE),
          _logger(LoggingService(NovelRT::Logging::CONSOLE_LOG_GFX)),
          _debugModeEnabled(enableDebugMode),
          _adapters([this]() { return GetGraphicsAdapters(shared_from_this()); })
    {
        if (GetDebugModeEnabled())
        {
            optionalInstanceLayers.emplace_back("VK_LAYER_KHRONOS_validation");
            optionalInstanceExtensions.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        _finalInstanceExtensions = GetAvailableInstanceExtensions(_logger, std::move(requiredInstanceExtensions),
                                                                  std::move(optionalInstanceExtensions));
        _finalInstanceLayers =
            GetAvailableInstanceLayers(_logger, std::move(requiredInstanceLayers), std::move(optionalInstanceLayers));

        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        // TODO: EngineConfig was here
        appInfo.pApplicationName = "NovelRT"; // EngineConfig::ApplicationName().c_str();
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        // TODO: EngineConfig was here
        appInfo.pEngineName = "NovelRT Engine"; // EngineConfig::EngineName().c_str();
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = GetApiVersion();

        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
        std::vector<VkValidationFeatureEnableEXT> enabledValidationFeatures{};
        std::vector<VkValidationFeatureDisableEXT> disabledValidationFeatures{};

        if (GetDebugModeEnabled())
        {
            debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
            debugCreateInfo.messageSeverity =
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
            debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                                          VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                                          VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

            debugCreateInfo.pfnUserCallback = &DebugCallback;
            debugCreateInfo.pUserData = &_logger;

            enabledValidationFeatures.push_back(VK_VALIDATION_FEATURE_ENABLE_SYNCHRONIZATION_VALIDATION_EXT);
        }

        _vulkanInstance = CreateInstance(appInfo, _finalInstanceExtensions, _finalInstanceLayers,
                                         GetDebugModeEnabled() ? &debugCreateInfo : nullptr,
                                         std::move(enabledValidationFeatures), std::move(disabledValidationFeatures));

        if (_vulkanInstance != VK_NULL_HANDLE)
        {
            _logger.logInfoLine("VkInstance successfully created.");
        }

        if (GetDebugModeEnabled())
        {
            VkResult debuggerResult =
                CreateDebugUtilsMessengerEXT(_vulkanInstance, &debugCreateInfo, nullptr, &_debugLogger);

            if (debuggerResult == VK_ERROR_OUT_OF_HOST_MEMORY)
            {
                throw Exceptions::OutOfMemoryException("Failed to initialise Vulkan: The host ran out of memory "
                                                       "before the VkDebugUtilsMessengerEXT could be created.");
            }

            else if (debuggerResult == VK_ERROR_EXTENSION_NOT_PRESENT)
            {
                _logger.logErrorLine("The VkDebugUtils could not be located and/or loaded on "
                                     "this device. Vulkan logging and validation output will "
                                     "not be displayed.");
            }

            else
            {
                _logger.logWarningLine("Vulkan debugger enabled! This may harm performance.");
            }
        }

        CheckDeviceCount(_vulkanInstance);
    }

    VulkanGraphicsProvider::~GraphicsProvider()
    {
        if (_debugLogger != VK_NULL_HANDLE)
        {
            DestroyDebugUtilsMessengerEXT(_vulkanInstance, _debugLogger, nullptr);
        }

        vkDestroyInstance(_vulkanInstance, nullptr);
    }

    uint32_t VulkanGraphicsProvider::GetApiVersion() const noexcept
    {
        return VK_API_VERSION_1_2;
    }

    bool VulkanGraphicsProvider::GetDebugModeEnabled() const noexcept
    {
        return _debugModeEnabled;
    }

    auto VulkanGraphicsProvider::begin() noexcept -> iterator
    {
        return _adapters.Get().begin();
    }

    auto VulkanGraphicsProvider::begin() const noexcept -> const_iterator
    {
        return _adapters.Get().begin();
    }

    auto VulkanGraphicsProvider::end() noexcept -> iterator
    {
        return _adapters.Get().end();
    }

    auto VulkanGraphicsProvider::end() const noexcept -> const_iterator
    {
        return _adapters.Get().end();
    }

    VkInstance VulkanGraphicsProvider::GetVulkanInstance() const noexcept
    {
        return _vulkanInstance;
    }

    NovelRT::Utilities::Span<const std::string> VulkanGraphicsProvider::GetValidationLayers() const noexcept
    {
        return _finalInstanceLayers;
    }
}
