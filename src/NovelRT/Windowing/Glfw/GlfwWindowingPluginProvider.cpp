// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include "NovelRT/Windowing/Glfw/Windowing.Glfw.h"

namespace NovelRT::Windowing::Glfw
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
