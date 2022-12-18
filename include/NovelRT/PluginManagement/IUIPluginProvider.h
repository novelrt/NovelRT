// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_PLUGINMANAGEMENT_IUIPLUGINPROVIDER_H
#define NOVELRT_PLUGINMANAGEMENT_IUIPLUGINPROVIDER_H

#ifndef NOVELRT_PLUGINMANAGEMENT_H
#error NovelRT does not support including types explicitly by default. Please include PluginManagement.h instead for the PluginManagement namespace subset.
#endif

namespace NovelRT::PluginManagement
{
    class IUIPluginProvider : public std::enable_shared_from_this<IUIPluginProvider>
    {
    protected:
        [[nodiscard]] virtual NovelRT::UI::IUIProvider* GetUIProviderInternal() = 0;

    public:
        [[nodiscard]] inline std::shared_ptr<NovelRT::UI::IUIProvider> GetUIProvider()
        {
            return GetUIProviderInternal()->shared_from_this();
        }
    };
}

#endif // NOVELRT_PLUGINMANAGEMENT_IUIPLUGINPROVIDER_H
