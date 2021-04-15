// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_VULKANGRAPHICSDEVICE_H
#define NOVELRT_VULKANGRAPHICSDEVICE_H

#include "../../../LoggingService.h"
#include "../IGraphicsSurface.h"
#include "../ILLGraphicsDevice.h"
#include "QueueFamilyIndices.h"
#include "SwapChainSupportDetails.h"
#include <vulkan/vulkan.h>

namespace NovelRT::Experimental::Graphics::Vulkan
{
    class VulkanGraphicsDevice : public ILLGraphicsDevice
    {
    private:
        static inline std::string _defaultFailureMessage = "Failed to initialise Vulkan version 1.2. Reason: ";

        std::vector<std::string> _finalExtensionSet;
        std::vector<std::string> _finalValidationLayerSet;

        VkInstance _instance;
        LoggingService _logger;
        VkDebugUtilsMessengerEXT _debugLogger;
        bool _debuggerWasCreated;

        VkPhysicalDevice _physicalDevice;
        VkDevice _device;

        VkQueue _graphicsQueue;
        VkQueue _presentQueue;

        VkSurfaceKHR _surface;

        VkSwapchainKHR _swapChain;
        std::vector<VkImage> _swapChainImages;
        VkFormat _swapChainImageFormat;
        VkExtent2D _swapChainExtent;

        std::vector<VkImageView> _swapChainImageViews;

        std::shared_ptr<IGraphicsSurface> _nrtSurface;

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

        [[nodiscard]] static std::vector<const char*> GetStringVectorAsCharPtrVector(
            const std::vector<std::string>& target) noexcept;

        [[nodiscard]] std::vector<std::string> GetFinalInstanceExtensionSet() const;
        [[nodiscard]] std::vector<std::string> GetFinalValidationLayerSet() const;
        [[nodiscard]] std::vector<std::string> GetFinalPhysicalDeviceExtensionSet() const;
        [[nodiscard]] bool CheckPhysicalDeviceRequiredExtensionSupport(VkPhysicalDevice physicalDevice) const noexcept;
        [[nodiscard]] int32_t GetPhysicalDeviceOptionalExtensionSupportScore(
            VkPhysicalDevice physicalDevice) const noexcept;

        void CreateDefaultDebugCreateInfoStruct(VkDebugUtilsMessengerCreateInfoEXT& outputResult) noexcept;
        void ConfigureDebugLogger();

        void CreateInstance();

        void ConfigureOutputSurface(std::shared_ptr<IGraphicsSurface> targetSurface);

        [[nodiscard]] QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice physicalDevice) const noexcept;
        [[nodiscard]] SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice physicalDevice) const noexcept;
        [[nodiscard]] int32_t RateDeviceSuitability(VkPhysicalDevice physicalDevice) const noexcept;
        void PickPhysicalDevice();

        void CreateLogicalDevice();

        [[nodiscard]] VkSurfaceFormatKHR ChooseSwapSurfaceFormat(
            const std::vector<VkSurfaceFormatKHR>& availableFormats) const noexcept;

        [[nodiscard]] VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes) const noexcept;
        [[nodiscard]] VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) const noexcept;

        void CreateSwapChain();

        void CreateImageViews();

    public:
        VulkanGraphicsDevice() noexcept;
        void Initialise(std::shared_ptr<IGraphicsSurface> targetSurface) final;
        void TearDown() final;
        ~VulkanGraphicsDevice();
    };
} // namespace NovelRT::Experimental::Graphics::Vulkan

#endif // NOVELRT_VULKANGRAPHICSDEVICE_H
