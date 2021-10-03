// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_VULKANGRAPHICSPROVIDER_H
#define NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_VULKANGRAPHICSPROVIDER_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.Vulkan.h instead for the Graphics::Vulkan namespace subset.
#endif

namespace NovelRT::Experimental::Graphics::Vulkan
{
    class VulkanGraphicsProvider final : public GraphicsProvider
    {
    private:
        static inline std::string _defaultFailureMessage = "Failed to initialise Vulkan version 1.2. Reason: ";

        VkInstance _vulkanInstance;
        std::vector<std::string> _finalExtensionSet;
        std::vector<std::string> _finalValidationLayerSet;
        NovelRT::Utilities::Lazy<std::vector<std::shared_ptr<GraphicsAdapter>>> _adapters;
        std::string _engineName;
        Threading::VolatileState _state;
        VkDebugUtilsMessengerEXT _debugLogger;
        LoggingService _logger;

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

        [[nodiscard]] inline gsl::span<const std::string> GetValidationLayers() const noexcept
        {
            return gsl::span<const std::string>(&(*_finalValidationLayerSet.begin()), _finalValidationLayerSet.size());
        }

        std::vector<std::shared_ptr<GraphicsAdapter>>::iterator begin() noexcept final;
        std::vector<std::shared_ptr<GraphicsAdapter>>::iterator end() noexcept final;

        ~VulkanGraphicsProvider() final;
    };
}

#endif // !NOVELRT_EXPERIMENTAL_GRAPHICS_VULKAN_VULKANGRAPHICSPROVIDER_H
