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
    struct VulkanGraphicsBackend;
}

namespace NovelRT::Graphics
{
    template<>
    class GraphicsProvider<Vulkan::VulkanGraphicsBackend>
        : public std::enable_shared_from_this<GraphicsProvider<Vulkan::VulkanGraphicsBackend>>
    {
    public:
        using iterator =
            typename std::vector<std::shared_ptr<GraphicsAdapter<Vulkan::VulkanGraphicsBackend>>>::iterator;
        using const_iterator =
            typename std::vector<std::shared_ptr<GraphicsAdapter<Vulkan::VulkanGraphicsBackend>>>::const_iterator;

    private:
        static inline std::string _defaultFailureMessage = "Failed to initialise Vulkan version 1.2. Reason: ";

        VkInstance _vulkanInstance;
        std::vector<std::string> _finalExtensionSet;
        std::vector<std::string> _finalValidationLayerSet;
        NovelRT::Utilities::Lazy<std::vector<std::shared_ptr<GraphicsAdapter<Vulkan::VulkanGraphicsBackend>>>>
            _adapters;
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

        [[nodiscard]] std::vector<std::string> GetFinalInstanceExtensionSet(
            std::vector<std::string> requiredInstanceExtensions,
            std::vector<std::string> optionalInstanceExtensions) const;
        [[nodiscard]] std::vector<std::string> GetFinalValidationLayerSet(
            std::vector<std::string> requiredInstanceLayers,
            std::vector<std::string> optionalInstanceLayers) const;
        void CreateDefaultDebugCreateInfoStruct(VkDebugUtilsMessengerCreateInfoEXT& outputResult) noexcept;
        void ConfigureDebugLogger();
        VkInstance CreateInstance(std::vector<std::string> requiredInstanceExtensions,
                                  std::vector<std::string> optionalInstanceExtensions,
                                  std::vector<std::string> requiredInstanceLayers,
                                  std::vector<std::string> optionalInstanceLayers);

        std::vector<std::shared_ptr<GraphicsAdapter<Vulkan::VulkanGraphicsBackend>>> GetGraphicsAdapters();

    public:
        GraphicsProvider(std::vector<std::string> requiredInstanceExtensions,
                         std::vector<std::string> optionalInstanceExtensions,
                         std::vector<std::string> requiredInstanceLayers,
                         std::vector<std::string> optionalInstanceLayers);
        ~GraphicsProvider();

        [[nodiscard]] bool GetDebugModeEnabled() const noexcept;

        // NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        [[nodiscard]] iterator begin() noexcept;
        // NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        [[nodiscard]] const_iterator begin() const noexcept;
        // NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        [[nodiscard]] iterator end() noexcept;
        // NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        [[nodiscard]] const_iterator end() const noexcept;

        [[nodiscard]] uint32_t GetApiVersion() const noexcept;

        [[nodiscard]] VkInstance GetVulkanInstance() const noexcept;

        [[nodiscard]] NovelRT::Utilities::Span<const std::string> GetValidationLayers() const noexcept;
    };
}
