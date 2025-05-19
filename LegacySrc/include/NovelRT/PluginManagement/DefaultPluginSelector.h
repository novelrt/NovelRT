// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_PLUGINMANAGEMENT_DEFAULTPLUGINSELECTOR_H
#define NOVELRT_PLUGINMANAGEMENT_DEFAULTPLUGINSELECTOR_H

#ifndef NOVELRT_PLUGINMANAGEMENT_H
#error
#endif

namespace NovelRT::Graphics::Vulkan
{
    struct VulkanGraphicsBackend;
}

namespace NovelRT::PluginManagement
{
    class DefaultPluginSelector
    {
    public:
        template<typename TPluginType>
        [[nodiscard]] std::shared_ptr<TPluginType> GetDefaultPluginTypeOnCurrentPlatformFor()
        {
            throw Exceptions::NotSupportedException();
        }

        template<>
        [[nodiscard]] std::shared_ptr<IGraphicsPluginProvider<NovelRT::Graphics::Vulkan::VulkanGraphicsBackend>>
        GetDefaultPluginTypeOnCurrentPlatformFor<
            IGraphicsPluginProvider<NovelRT::Graphics::Vulkan::VulkanGraphicsBackend>>()
        {
            return std::static_pointer_cast<IGraphicsPluginProvider<NovelRT::Graphics::Vulkan::VulkanGraphicsBackend>>(
                GetVulkanPluginProvider());
        }

        template<>
        [[nodiscard]] std::shared_ptr<IWindowingPluginProvider> GetDefaultPluginTypeOnCurrentPlatformFor<
            IWindowingPluginProvider>()
        {
            return std::static_pointer_cast<IWindowingPluginProvider>(GetGlfwWindowPluginProvider());
        }

        template<>
        [[nodiscard]] std::shared_ptr<IResourceManagementPluginProvider> GetDefaultPluginTypeOnCurrentPlatformFor<
            IResourceManagementPluginProvider>()
        {
            return std::static_pointer_cast<IResourceManagementPluginProvider>(
                GetDesktopResourceManagementPluginProvider());
        }

        template<>
        [[nodiscard]] std::shared_ptr<IInputPluginProvider> GetDefaultPluginTypeOnCurrentPlatformFor<
            IInputPluginProvider>()
        {
            return std::static_pointer_cast<IInputPluginProvider>(GetGlfwInputPluginProvider());
        }
    };
}

#endif // NOVELRT_PLUGINMANAGEMENT_DEFAULTPLUGINSELECTOR_H
