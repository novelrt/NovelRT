// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/NovelRT.h>
#include <gtest/gtest.h>
#include <vulkan/vulkan.h>

using namespace NovelRT;

TEST(VulkanInstanceTest, canCreateVulkanInstance)
{
    std::vector<std::string>& extensions = EngineConfig::RequiredVulkanInstanceExtensions();

    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Engine_Tests";
    appInfo.pEngineName = "NovelRT";
    appInfo.apiVersion = VK_API_VERSION_1_2;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
#ifdef __APPLE__
    createInfo.flags = VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;

    extensions.emplace_back("VK_KHR_portability_enumeration");
    extensions.emplace_back("VK_KHR_get_physical_device_properties2");
#endif
    std::vector<const char*> allExtensionptrs = NovelRT::Utilities::Misc::GetStringSpanAsCharPtrVector(extensions);
    size_t extensionLength = allExtensionptrs.size();

    createInfo.enabledExtensionCount = extensionLength;
    createInfo.ppEnabledExtensionNames = allExtensionptrs.data();

    VkInstance instance = VK_NULL_HANDLE;
    VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
    ASSERT_EQ(VK_SUCCESS, result);
    EXPECT_NE(result, VK_ERROR_INCOMPATIBLE_DRIVER);
    EXPECT_NE(result, VK_ERROR_EXTENSION_NOT_PRESENT);
    EXPECT_NO_THROW(vkDestroyInstance(instance, nullptr));
}
