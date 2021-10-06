// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Experimental/Windowing/Glfw/GlfwWindowingPluginProvider.h>
#include <NovelRT/Experimental/Windowing/Glfw/Windowing.Glfw.h>

namespace NovelRT::Experimental::Windowing::Glfw
{
    GlfwWindowingPluginProvider::GlfwWindowingPluginProvider() noexcept
        : _windowingDevice(std::make_shared<GlfwWindowingDevice>())
    {
    }

    GlfwWindowingDevice* GlfwWindowingPluginProvider::GetWindowingDeviceInternal()
    {
        return _windowingDevice.get();
    }
}
