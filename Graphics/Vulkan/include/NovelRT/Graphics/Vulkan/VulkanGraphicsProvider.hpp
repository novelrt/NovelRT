#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsProvider.hpp>
#include <NovelRT/Logging/LoggingService.hpp>
#include <NovelRT/Threading/VolatileState.hpp>
#include <NovelRT/Utilities/Lazy.hpp>
#include <NovelRT/Utilities/Span.hpp>

#include <vulkan/vulkan.h>

namespace NovelRT::Graphics::Vulkan
{
    class VulkanGraphicsAdapter;

    class VulkanGraphicsProvider
    {
    private:
        static inline std::string _defaultFailureMessage = "Failed to initialise Vulkan version 1.2. Reason: ";

        VkInstance _vulkanInstance;
        std::vector<std::string> _finalExtensionSet;
        std::vector<std::string> _finalValidationLayerSet;
        NovelRT::Utilities::Lazy<std::vector<VulkanGraphicsAdapter*>> _adapters;
        std::string _engineName;
        Threading::VolatileState _state;
        VkDebugUtilsMessengerEXT _debugLogger;
        LoggingService _logger;
        bool _debugModeEnabled;

        static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                            VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                                                            void* pUserData);

        [[nodiscard]] static VkResult CreateDebugUtilsMessengerEXT(
            VkInstance instance,
            const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
            const VkAllocationCallbacks* pAllocator,
            VkDebugUtilsMessengerEXT* pDebugMessenger) noexcept;

        static void DestroyDebugUtilsMessengerEXT(VkInstance instance,
                                                  VkDebugUtilsMessengerEXT debugMessenger,
                                                  const VkAllocationCallbacks* pAllocator) noexcept;

        [[nodiscard]] std::vector<std::string> GetFinalInstanceExtensionSet() const;
        [[nodiscard]] std::vector<std::string> GetFinalValidationLayerSet() const;
        void CreateDefaultDebugCreateInfoStruct(VkDebugUtilsMessengerCreateInfoEXT& outputResult) noexcept;
        void ConfigureDebugLogger();
        VkInstance CreateInstance();

        std::vector<VulkanGraphicsAdapter*> GetGraphicsAdapters();

    public:
        VulkanGraphicsProvider();
        ~VulkanGraphicsProvider();

        [[nodiscard]] VkInstance GetVulkanInstance() const noexcept
        {
            return _vulkanInstance;
        }

        [[nodiscard]] NovelRT::Utilities::Span<const std::string> GetValidationLayers() const noexcept
        {
            return { _finalValidationLayerSet };
        }

        [[nodiscard]] uint32_t GetApiVersion() const noexcept;

        [[nodiscard]] bool GetDebugModeEnabled() const noexcept;

        std::vector<VulkanGraphicsAdapter*>::iterator begin() noexcept;
        std::vector<VulkanGraphicsAdapter*>::iterator end() noexcept;


    };
}
