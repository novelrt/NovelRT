// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Experimental/Input/Glfw/Input.Glfw.h>

namespace NovelRT::Experimental::Input::Glfw
{
    GlfwInputPluginProvider::GlfwInputPluginProvider() noexcept
        : _inputService(std::make_shared<GlfwInputService>())
    {
    }

    GlfwInputService* GlfwInputPluginProvider::GetInputServiceInternal()
    {
        return _inputService.get();
    }
}
