// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InitialisationFailureException.hpp>
#include <NovelRT/Exceptions/NotSupportedException.hpp>
#include <NovelRT/Exceptions/OutOfMemoryException.hpp>

#include <NovelRT/Graphics/Vulkan/VulkanGraphicsAdapter.hpp>
#include <NovelRT/Graphics/Vulkan/VulkanGraphicsProvider.hpp>
#include <NovelRT/Logging/BuiltInLogSections.hpp>
#include <NovelRT/Utilities/Strings.hpp>

namespace NovelRT::Graphics
{
    using VulkanGraphicsAdapter = GraphicsAdapter<Vulkan::VulkanGraphicsBackend>;
    using VulkanGraphicsProvider = GraphicsProvider<Vulkan::VulkanGraphicsBackend>;

    VKAPI_ATTR VkBool32 VKAPI_CALL
    VulkanGraphicsProvider::DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
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

        // TODO: EngineConfig was here
        if (logLevel != LogLevel::Off && logLevel >= LogLevel::Debug) //EngineConfig::MinimumInternalLoggingLevel())
        {
            reinterpret_cast<VulkanGraphicsProvider*>(pUserData)->_logger.log(std::string(pCallbackData->pMessage),
                                                                              logLevel);
        }

        return VK_FALSE;
    }

    VkResult VulkanGraphicsProvider::CreateDebugUtilsMessengerEXT(VkInstance instance,
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

    void VulkanGraphicsProvider::DestroyDebugUtilsMessengerEXT(VkInstance instance,
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

    std::vector<std::string> VulkanGraphicsProvider::GetFinalInstanceExtensionSet(std::vector<std::string> requiredInstanceExtensions, std::vector<std::string> optionalInstanceExtensions) const
    {
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensionProperties(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensionProperties.data());

        _logger.logInfoLine("Found the following available instance extensions:");

        for (auto&& extensionProperty : extensionProperties)
        {
            _logger.logInfoLine("  Extension Name: '" + std::string(extensionProperty.extensionName) +
                                "' Spec Version: " + std::to_string(extensionProperty.specVersion));
        }

        for (auto&& requestedRequiredExt : requiredInstanceExtensions)
        {
            auto result =
                std::find_if(extensionProperties.begin(), extensionProperties.end(),
                             [&](auto& x) { return strcmp(requestedRequiredExt.c_str(), x.extensionName) == 0; });

            if (result == extensionProperties.end())
            {
                throw Exceptions::InitialisationFailureException(
                    "The required Vulkan extension " + requestedRequiredExt + " is not available on this device.");
            }
        }

        std::vector<std::string> finalOptionalExtensions{};

        for (auto&& requestedOptionalExt : optionalInstanceExtensions)
        {
            auto result =
                std::find_if(extensionProperties.begin(), extensionProperties.end(),
                             [&](auto& x) { return strcmp(requestedOptionalExt.c_str(), x.extensionName) == 0; });

            if (result == extensionProperties.end())
            {
                _logger.logWarningLine("The optional Vulkan extension " + requestedOptionalExt +
                                       " is not available on this device. Vulkan may not behave as you expect.");
                continue;
            }

            finalOptionalExtensions.emplace_back(requestedOptionalExt);
        }

        std::vector<std::string> allExtensions{requiredInstanceExtensions};
        allExtensions.reserve(requiredInstanceExtensions.size() + finalOptionalExtensions.size());
        allExtensions.insert(allExtensions.end(), finalOptionalExtensions.begin(), finalOptionalExtensions.end());

        _logger.logInfoLine("Enabled extensions:");
        for (const auto& ext : allExtensions)
        {
            _logger.logInfoLine("  " + ext);
        }

        return allExtensions;
    }

    std::vector<std::string> VulkanGraphicsProvider::GetFinalValidationLayerSet(std::vector<std::string> requiredInstanceLayers, std::vector<std::string> optionalInstanceLayers) const
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

            _logger.logInfoLine("  Layer Name: '" + std::string(layerProperty.layerName) + "' Spec Version: " +
                                specVersion + " Impl Version: " + std::to_string(layerProperty.implementationVersion) +
                                " Description: " + std::string(layerProperty.description));
        }

        for (auto&& requestedRequiredLayer : requiredInstanceLayers)
        {
            auto result =
                std::find_if(layerProperties.begin(), layerProperties.end(),
                             [&](auto& x) { return strcmp(requestedRequiredLayer.c_str(), x.layerName) == 0; });

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
                _logger.logWarningLine("The optional Vulkan layer " + requestedOptionalLayer +
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

    void VulkanGraphicsProvider::CreateDefaultDebugCreateInfoStruct(
        VkDebugUtilsMessengerCreateInfoEXT& outputResult) noexcept
    {
        outputResult = {};
        outputResult.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        outputResult.messageSeverity =
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        outputResult.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                                   VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                                   VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        outputResult.pfnUserCallback = DebugCallback;
        outputResult.pUserData = this;
    }

    void VulkanGraphicsProvider::ConfigureDebugLogger()
    {
        VkDebugUtilsMessengerCreateInfoEXT createInfo{};
        CreateDefaultDebugCreateInfoStruct(createInfo);

        VkResult debuggerResult =
            CreateDebugUtilsMessengerEXT(GetVulkanInstance(), &createInfo, nullptr, &_debugLogger);

        if (debuggerResult == VK_ERROR_OUT_OF_HOST_MEMORY)
        {
            throw Exceptions::OutOfMemoryException(
                _defaultFailureMessage +
                "The host ran out of memory before the VkDebugUtilsMessengerEXT could be created.");
        }

        if (debuggerResult == VK_ERROR_EXTENSION_NOT_PRESENT)
        {
            _logger.logErrorLine("The VkDebugUtils could not be located and/or loaded on this device. Vulkan logging "
                                 "and validation output will not be displayed.");
            return;
        }

        _logger.logWarningLine("Vulkan debugger enabled! This may harm performance.");
    }

    VkInstance VulkanGraphicsProvider::CreateInstance(
        std::vector<std::string> requiredInstanceExtensions, std::vector<std::string> optionalInstanceExtensions,
        std::vector<std::string> requiredInstanceLayers, std::vector<std::string> optionalInstanceLayers)
    {
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        // TODO: EngineConfig was here
        appInfo.pApplicationName = "NovelRT"; //EngineConfig::ApplicationName().c_str();
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        // TODO: EngineConfig was here
        appInfo.pEngineName = "NovelRT Engine"; //EngineConfig::EngineName().c_str();
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = GetApiVersion();

        _finalExtensionSet = GetFinalInstanceExtensionSet(requiredInstanceExtensions, optionalInstanceExtensions);
        std::vector<const char*> allExtensionullptrs =
            NovelRT::Utilities::GetStringSpanAsCharPtrVector(_finalExtensionSet);
        size_t extensionLength = allExtensionullptrs.size();

        _finalValidationLayerSet = GetFinalValidationLayerSet(requiredInstanceLayers, optionalInstanceLayers);
        std::vector<const char*> allValidationLayerPtrs =
            NovelRT::Utilities::GetStringSpanAsCharPtrVector(_finalValidationLayerSet);
        size_t validationLayerLength = allValidationLayerPtrs.size();

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensionLength);
        createInfo.ppEnabledExtensionNames = allExtensionullptrs.data();
        createInfo.ppEnabledLayerNames = allValidationLayerPtrs.data();
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayerLength);

#ifdef __APPLE__
        createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
#endif

        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
            VkValidationFeaturesEXT validationFeatures = {};

        VkValidationFeatureEnableEXT enables[] = {
        VK_VALIDATION_FEATURE_ENABLE_SYNCHRONIZATION_VALIDATION_EXT};
        // TODO: EngineConfig was here
        if (true)//EngineConfig::EnableDebugOutputFromEngineInternals())
        {
            validationFeatures.sType = VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT;
            validationFeatures.enabledValidationFeatureCount = 1;
            validationFeatures.pEnabledValidationFeatures = enables;
            CreateDefaultDebugCreateInfoStruct(debugCreateInfo);
            createInfo.pNext = &debugCreateInfo;
            debugCreateInfo.pNext = &validationFeatures;
        }
        else
        {
            createInfo.pNext = nullptr;
        }

        VkInstance returnInstance = VK_NULL_HANDLE;
        VkResult instanceResult = vkCreateInstance(&createInfo, nullptr, &returnInstance);
        if (instanceResult != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to initialise the VkInstance.", instanceResult);
        }

        _logger.logInfoLine("VkInstance successfully created.");

        return returnInstance;
    }

    std::vector<std::shared_ptr<VulkanGraphicsAdapter>> VulkanGraphicsProvider::GetGraphicsAdapters()
    {
        VkInstance instance = GetVulkanInstance();

        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

        if (deviceCount == 0)
        {
            throw Exceptions::NotSupportedException(_defaultFailureMessage +
                                                    "A Vulkan-compatible GPU was not found. Please refer "
                                                    "to your GPU manufacturer's documentation for more information.");
        }

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

        std::vector<std::shared_ptr<VulkanGraphicsAdapter>> adapters(devices.size());
        std::transform(devices.begin(), devices.end(), adapters.begin(), [this](const auto& device){
            return std::make_shared<VulkanGraphicsAdapter>(shared_from_this(), device);
        });

        return adapters;
    }

    VulkanGraphicsProvider::GraphicsProvider(
        std::vector<std::string> requiredInstanceExtensions, std::vector<std::string> optionalInstanceExtensions,
        std::vector<std::string> requiredInstanceLayers, std::vector<std::string> optionalInstanceLayers)
        : _vulkanInstance(VK_NULL_HANDLE)
        , _adapters([&]() { return GetGraphicsAdapters(); })
        // TODO: EngineConfig was here
        , _engineName("NovelRT Engine") //EngineConfig::EngineName())
        , _debugLogger(VK_NULL_HANDLE)
        , _logger(LoggingService(NovelRT::Logging::CONSOLE_LOG_GFX))
        // TODO: EngineConfig was here
        , _debugModeEnabled(true) //EngineConfig::EnableDebugOutputFromEngineInternals())
    {
        _vulkanInstance = CreateInstance(requiredInstanceExtensions, optionalInstanceExtensions, requiredInstanceLayers, optionalInstanceLayers);

        if (GetDebugModeEnabled())
        {
            ConfigureDebugLogger();
        }

        static_cast<void>(_state.Transition(Threading::VolatileState::Initialised));
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
        return _finalValidationLayerSet;
    }
}
