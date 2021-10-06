// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_PLUGINMANAGEMENT_DEFAULTPLUGINSELECTOR_H
#define NOVELRT_PLUGINMANAGEMENT_DEFAULTPLUGINSELECTOR_H

#ifndef NOVELRT_PLUGINMANAGEMENT_H
#error
#endif

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
        [[nodiscard]] std::shared_ptr<IGraphicsPluginProvider> GetDefaultPluginTypeOnCurrentPlatformFor<
            IGraphicsPluginProvider>()
        {
            return std::static_pointer_cast<IGraphicsPluginProvider>(GetVulkanPluginProvider());
        }

        template<>
        [[nodiscard]] std::shared_ptr<IWindowingPluginProvider> GetDefaultPluginTypeOnCurrentPlatformFor<
            IWindowingPluginProvider>()
        {
            return std::static_pointer_cast<IWindowingPluginProvider>(GetGlfwPluginProvider());
        }
    };
}

#endif // NOVELRT_PLUGINMANAGEMENT_DEFAULTPLUGINSELECTOR_H
