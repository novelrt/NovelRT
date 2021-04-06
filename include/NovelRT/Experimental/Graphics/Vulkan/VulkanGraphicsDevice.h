// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_VULKANGRAPHICSDEVICE_H
#define NOVELRT_VULKANGRAPHICSDEVICE_H

#include "../../../LoggingService.h"
#include "../ILLGraphicsDevice.h"
#include "QueueFamilyIndices.h"
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

        [[nodiscard]] std::vector<std::string> GetFinalExtensionSet() const;
        [[nodiscard]] std::vector<std::string> GetFinalValidationLayerSet() const;

        void CreateDefaultDebugCreateInfoStruct(VkDebugUtilsMessengerCreateInfoEXT& outputResult) noexcept;
        void ConfigureDebugLogger();

        void CreateInstance();

        [[nodiscard]] static QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device) noexcept;
        [[nodiscard]] static int32_t RateDeviceSuitability(VkPhysicalDevice device) noexcept;
        void PickPhysicalDevice();

        void CreateLogicalDevice();

    public:
        VulkanGraphicsDevice() noexcept;
        void Initialise() override;
        void TearDown() override;
    };
} // namespace NovelRT::Experimental::Graphics::Vulkan

#endif // NOVELRT_VULKANGRAPHICSDEVICE_H
