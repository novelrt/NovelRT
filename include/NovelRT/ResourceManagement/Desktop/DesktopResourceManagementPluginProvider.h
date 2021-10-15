// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_RESOURCEMANAGEMENT_DESKTOP_DESKTOPRESOURCEMANAGEMENTPLUGINPROVIDER_H
#define NOVELRT_RESOURCEMANAGEMENT_DESKTOP_DESKTOPRESOURCEMANAGEMENTPLUGINPROVIDER_H

#ifndef NOVELRT_RESOURCEMANAGEMENT_DESKTOP_H
#error NovelRT does not support including types explicitly by default. Please include ResourceManagement.Desktop.h instead for the ResourceManagement::Desktop namespace subset.
#endif

namespace NovelRT::ResourceManagement::Desktop
{
    class DesktopResourceManagementPluginProvider final : public PluginManagement::IResourceManagementPluginProvider
    {
    private:
        std::shared_ptr<DesktopResourceLoader> _resourceLoader;

    protected:
        [[nodiscard]] DesktopResourceLoader* GetResourceLoaderInternal() final;

    public:
        DesktopResourceManagementPluginProvider() noexcept;
        ~DesktopResourceManagementPluginProvider() final = default;

    };
}

#endif // NOVELRT_RESOURCEMANAGEMENT_DESKTOP_DESKTOPRESOURCEMANAGEMENTPLUGINPROVIDER_H
