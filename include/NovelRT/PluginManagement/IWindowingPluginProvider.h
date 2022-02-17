// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_PLUGINMANAGEMENT_IWINDOWINGPLUGINPROVIDER_H
#define NOVELRT_PLUGINMANAGEMENT_IWINDOWINGPLUGINPROVIDER_H

#ifndef NOVELRT_PLUGINMANAGEMENT_H
#error NovelRT does not support including types explicitly by default. Please include PluginManagement.h instead for the PluginManagement namespace subset.
#endif

namespace NovelRT::PluginManagement
{
    class IWindowingPluginProvider
    {
    private:
        [[nodiscard]] virtual Windowing::IWindowingDevice* GetWindowingDeviceInternal() = 0;

    public:
        [[nodiscard]] inline std::shared_ptr<Windowing::IWindowingDevice> GetWindowingDevice()
        {
            return std::dynamic_pointer_cast<Windowing::IWindowingDevice>(GetWindowingDeviceInternal()->shared_from_this());
        }
    };
}

#endif // NOVELRT_PLUGINMANAGEMENT_IWINDOWINGPLUGINPROVIDER_H
