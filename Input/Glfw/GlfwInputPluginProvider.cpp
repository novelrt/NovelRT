// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Input/Glfw/GlfwInputPluginProvider.hpp>

namespace NovelRT::Input::Glfw
{
    GlfwInputPluginProvider::GlfwInputPluginProvider() noexcept : _inputDevice(std::make_shared<GlfwInputDevice>())
    {
    }

    GlfwInputDevice* GlfwInputPluginProvider::GetInputDeviceInternal()
    {
        return _inputDevice.get();
    }
}
