// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICS_VULKAN_VULKANGRAPHICSPROVIDER_H
#define NOVELRT_GRAPHICS_VULKAN_VULKANGRAPHICSPROVIDER_H

#ifndef NOVELRT_GRAPHICS_VULKAN_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.Vulkan.h instead for the Graphics::Vulkan namespace subset.
#endif

namespace NovelRT::Graphics::Vulkan
{
    class VulkanGraphicsProvider final : public GraphicsProvider
    {
    private:
        static inline std::string _defaultFailureMessage = "Failed to initialise Vulkan version 1.2. Reason: ";

        VkInstance _vulkanInstance;
        std::vector<std::string> _finalExtensionSet;
        std::vector<std::string> _finalValidationLayerSet;
        NovelRT::Core::Utilities::Lazy<std::vector<std::shared_ptr<GraphicsAdapter>>> _adapters;
        std::string _engineName;
        Threading::VolatileState _state;
        VkDebugUtilsMessengerEXT _debugLogger;
        NovelRT::Core::LoggingService _logger;

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

        std::vector<std::shared_ptr<GraphicsAdapter>> GetGraphicsAdapters();

    public:
        VulkanGraphicsProvider();

        [[nodiscard]] inline VkInstance GetVulkanInstance() const noexcept
        {
            return _vulkanInstance;
        }

        [[nodiscard]] inline NovelRT::Core::Utilities::Misc::Span<const std::string> GetValidationLayers() const noexcept
        {
            return NovelRT::Core::Utilities::Misc::Span<const std::string>(&(*_finalValidationLayerSet.begin()),
                                                                     _finalValidationLayerSet.size());
        }

        std::vector<std::shared_ptr<GraphicsAdapter>>::iterator begin() noexcept final;
        std::vector<std::shared_ptr<GraphicsAdapter>>::iterator end() noexcept final;

        ~VulkanGraphicsProvider() final;
    };
}

#endif // !NOVELRT_GRAPHICS_VULKAN_VULKANGRAPHICSPROVIDER_H
