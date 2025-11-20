#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <memory>
#include <NoveLRT/ResourceManagement/Desktop/DesktopResourceLoader.hpp>

namespace NovelRT::ResourceManagement::Desktop
{
    class DesktopResourceManagementPluginProvider
    {
    private:
        std::shared_ptr<DesktopResourceLoader> _resourceLoader;

    protected:
        [[nodiscard]] DesktopResourceLoader* GetResourceLoaderInternal(bool initAssets);

    public:
        DesktopResourceManagementPluginProvider() noexcept;
        ~DesktopResourceManagementPluginProvider() = default;
    };
}
