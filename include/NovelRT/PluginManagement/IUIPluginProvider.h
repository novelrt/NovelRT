// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_UI_IUIPLUGINPROVIDER_H
#define NOVELRT_UI_IUIPLUGINPROVIDER_H

#ifndef NOVELRT_PLUGINMANAGEMENT_H
#error NovelRT does not support including types explicitly by default. Please include PluginManagement.h instead for the PluginManagement namespace subset.
#endif

namespace NovelRT::PluginManagement
{
    class IUIPluginProvider
    {
    protected:
        [[nodiscard]] virtual UI::UIProvider* GetUIProviderInternal() = 0;

    public:
        [[nodiscard]] inline std::shared_ptr<UI::UIProvider> GetUIProvider()
        {
            return GetUIProviderInternal()->shared_from_this();
        }

        virtual ~IUIPluginProvider() = default;
    };
}

#endif // NOVELRT_UI_IUIPLUGINPROVIDER_H
