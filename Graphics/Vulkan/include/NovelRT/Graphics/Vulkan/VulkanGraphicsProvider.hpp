#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <vulkan/vulkan.h>
#include <NovelRT/Graphics/GraphicsProvider.hpp>
#include <NovelRT/Threading/Threading.h>
#include <NovelRT/Utilities/Lazy.h>

namespace NovelRT::Graphics::Vulkan
{
    class VulkanGraphicsAdapter;

    class VulkanGraphicsProvider : public std::enable_shared_from_this<VulkanGraphicsProvider>
    {
    private:
        static inline std::string _defaultFailureMessage = "Failed to initialise Vulkan version 1.2. Reason: ";

        VkInstance _vulkanInstance;
        std::vector<std::string> _finalExtensionSet;
        std::vector<std::string> _finalValidationLayerSet;
        NovelRT::Utilities::Lazy<std::vector<std::shared_ptr<VulkanGraphicsAdapter>>> _adapters;
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

        std::vector<std::shared_ptr<VulkanGraphicsAdapter>> GetGraphicsAdapters();

    public:
        VulkanGraphicsProvider();

        [[nodiscard]] inline VkInstance GetVulkanInstance() const noexcept
        {
            return _vulkanInstance;
        }

        [[nodiscard]] inline NovelRT::Utilities::Misc::Span<const std::string> GetValidationLayers() const noexcept
        {
            return NovelRT::Utilities::Misc::Span<const std::string>(&(*_finalValidationLayerSet.begin()),
                                                                     _finalValidationLayerSet.size());
        }

        [[nodiscard]] uint32_t GetApiVersion() const noexcept;

        [[nodiscard]] bool GetDebugModeEnabled() const noexcept;

        std::vector<std::shared_ptr<VulkanGraphicsAdapter>>::iterator begin() noexcept;
        std::vector<std::shared_ptr<VulkanGraphicsAdapter>>::iterator end() noexcept;

        ~VulkanGraphicsProvider();
    };
}
