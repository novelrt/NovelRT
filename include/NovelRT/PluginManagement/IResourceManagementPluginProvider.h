// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_PLUGINMANAGEMENT_IRESOURCEMANAGEMENTPLUGINPROVIDER_H
#define NOVELRT_PLUGINMANAGEMENT_IRESOURCEMANAGEMENTPLUGINPROVIDER_H

#ifndef NOVELRT_PLUGINMANAGEMENT_H
#error NovelRT does not support including types explicitly by default. Please include PluginManagement.h instead for the PluginManagement namespace subset.
#endif

namespace NovelRT::PluginManagement
{
    class IResourceManagementPluginProvider : public std::enable_shared_from_this<IResourceManagementPluginProvider>
    {
    private:
        [[nodiscard]] virtual ResourceManagement::ResourceLoader* GetResourceLoaderInternal() = 0;

    public:
        [[nodiscard]] inline std::shared_ptr<ResourceManagement::ResourceLoader> GetResourceLoader()
        {
            return GetResourceLoaderInternal()->shared_from_this();
        }

        virtual ~IResourceManagementPluginProvider() = default;
    };
}

#endif // !NOVELRT_PLUGINMANAGEMENT_IRESOURCEMANAGEMENTPLUGINPROVIDER_H
