// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Experimental/EngineConfig.h>
#include <NovelRT/Experimental/Graphics/Vulkan/VulkanGraphicsDevice.h>
#include <NovelRT/Exceptions/InitialisationFailureException.h>
#include <numeric>

namespace NovelRT::Experimental::Graphics::Vulkan
{
    void VulkanGraphicsDevice::CreateInstance()
    {
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = EngineConfig::ApplicationName.c_str();
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = EngineConfig::EngineName.c_str();
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_2;

        size_t extensionLength =
            EngineConfig::RequiredVulkanExtensions.size() + EngineConfig::OptionalVulkanExtensions.size();
        std::vector<const char*> allExtensions;
        allExtensions.reserve(extensionLength);

        for (auto& ext : EngineConfig::RequiredVulkanExtensions)
        {
            allExtensions.push_back(ext.c_str());
        }
        for (auto& ext : EngineConfig::OptionalVulkanExtensions)
        {
            allExtensions.push_back(ext.c_str());
        }

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        createInfo.enabledExtensionCount = extensionLength;
        createInfo.ppEnabledExtensionNames = allExtensions.data();
        createInfo.enabledLayerCount = 0;

        if (vkCreateInstance(&createInfo, nullptr, &_instance) != VK_SUCCESS)
        {
            throw Exceptions::InitialisationFailureException("Failed to create an instance of Vulkan 1.2.");
        }
    }

    void VulkanGraphicsDevice::Initialise()
    {
        CreateInstance();
    }

    void VulkanGraphicsDevice::TearDown()
    {
    }
} // namespace NovelRT::Experimental::Graphics::Vulkan
