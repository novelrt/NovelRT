// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Ecs.h>

namespace NovelRT::Ecs::Input
{
    InputSystem(std::shared_ptr<PluginManagement::IWindowingPluginProvider> windowingProvider):
          _logger(Utilities::Misc::CONSOLE_LOG_INPUT),
          _service(std::make_shared<Experimental::Input::Glfw::GlfwInputService>())
    {
        _service->Initialise(windowPtr->GetHandle());
    }

    void InputSystem::Update(Timing::Timestamp delta, Ecs::Catalogue catalogue)
    {
        _service->Update(delta);
    }

    void InputSystem::AddDefaultKBMMapping()
    {
        _service->AddInputAction("Up", "W");
        _service->AddInputAction("Down", "S");
        _service->AddInputAction("Left", "A");
        _service->AddInputAction("Right", "D");
        _service->AddInputAction("LeftClick", "LeftMouseButton");
        _service->AddInputAction("A", "K");
        _service->AddInputAction("B", "L");
    }

    InputSystem::~InputSystem() noexcept
    {
    }
}
