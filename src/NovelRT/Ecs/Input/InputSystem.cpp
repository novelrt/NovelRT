// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Ecs.h>

namespace NovelRT::Ecs::Input
{
    InputSystem::InputSystem(std::shared_ptr<PluginManagement::IWindowingPluginProvider> windowingProvider)
    {
        _actionMap = std::map<NovelRT::Atom, std::string>();
    }

    void InputSystem::Update(Timing::Timestamp delta, Ecs::Catalogue catalogue)
    {
        _service->Update(delta);

        auto inputs = catalogue.GetComponentView<InputEventComponent>();

        for (auto [entity, input] : inputs)
        {
            if (_service->GetKeyState(_actionMap.at(input.actionId)) == Experimental::Input::KeyState::Idle)
            {
                inputs.RemoveComponent(entity);
            }
            else
            {
                auto event = InputEventComponent{input.actionId, _service->GetKeyState(_actionMap.at(input.actionId)), input.mousePositionX, input.mousePositionY};
                inputs.PushComponentUpdateInstruction(entity, event);
            }
        }
        inputs = catalogue.GetComponentView<InputEventComponent>();

        for (auto action : _actionMap)
        {
            InputEventComponent in;
            if(!inputs.TryGetComponent(action.first, in))
            {
                if (_service->GetKeyState(action.second) != NovelRT::Experimental::Input::KeyState::Idle)
                {
                    auto mouse = _service->GetMousePosition();
                    in = InputEventComponent{action.first, _service->GetKeyState(action.second), mouse.x, mouse.y};
                }
            }
        }
    }

    void InputSystem::AddMapping(std::string name, std::string id, Ecs::Catalogue catalogue)
    {
        unused(_service->AddInputAction(name, id));
        auto entityActionId = catalogue.CreateEntity();
        _actionMap.insert(std::pair<NovelRT::Atom, std::string>(entityActionId, name));
    }

    void InputSystem::AddDefaultKBMMapping(Ecs::Catalogue catalogue)
    {
        AddMapping("Down", "S", catalogue);
        AddMapping("Left", "A", catalogue);
        AddMapping("Right", "D", catalogue);
        AddMapping("LeftClick", "LeftMouseButton", catalogue);
        AddMapping("A", "K", catalogue);
        AddMapping("B", "L", catalogue);
    }

    InputSystem::~InputSystem() noexcept
    {
        _service->TearDown();
    }
}
