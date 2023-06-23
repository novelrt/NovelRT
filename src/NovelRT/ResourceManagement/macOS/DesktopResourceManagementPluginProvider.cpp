// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/ResourceManagement/Desktop/ResourceManagement.Desktop.h>

namespace NovelRT::ResourceManagement::Desktop
{
    DesktopResourceManagementPluginProvider::DesktopResourceManagementPluginProvider() noexcept
        : _resourceLoader(std::make_shared<DesktopResourceLoader>())
    {
    }

    DesktopResourceLoader* DesktopResourceManagementPluginProvider::GetResourceLoaderInternal()
    {
        if (!_resourceLoader->GetIsAssetDBInitialised())
        {
            _resourceLoader->InitAssetDatabase();
        }

        return _resourceLoader.get();
    }
}
