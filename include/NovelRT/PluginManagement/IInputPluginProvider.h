// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_PLUGINMANAGEMENT_IINPUTPLUGINPROVIDER_H
#define NOVELRT_PLUGINMANAGEMENT_IINPUTPLUGINPROVIDER_H

#ifndef NOVELRT_PLUGINMANAGEMENT_H
#error NovelRT does not support including types explicitly by default. Please include PluginManagement.h instead for the PluginManagement namespace subset.
#endif

namespace NovelRT::PluginManagement
{
    class IInputPluginProvider
    {
    private:
        [[nodiscard]] virtual Experimental::Input::IInputService* GetInputServiceInternal() = 0;

    public:
        [[nodiscard]] inline std::shared_ptr<Experimental::Input::IInputService> GetInputService()
        {
            return GetInputServiceInternal()->shared_from_this();
        }
    };
}

#endif // NOVELRT_PLUGINMANAGEMENT_IINPUTPLUGINPROVIDER_H
