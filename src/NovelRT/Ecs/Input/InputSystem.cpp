// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Ecs.h>

namespace NovelRT::Ecs::Input
{
    InputSystem::InputSystem(std::shared_ptr<PluginManagement::IWindowingPluginProvider> windowingProvider, std::shared_ptr<PluginManagement::IInputPluginProvider> inputProvider)
    {
        _actionMap = std::map<NovelRT::Atom, std::string>();
        _firstUpdate = true;
        _service = inputProvider->GetInputService();
        _service->Initialise(windowingProvider->GetWindowingDevice()->GetHandle());
    }

    void InputSystem::Update(Timing::Timestamp delta, Ecs::Catalogue catalogue)
    {
        if (_firstUpdate)
        {
            auto actions = _service->GetAllMappings();
            for (auto act : actions)
            {
                auto entityActionId = catalogue.CreateEntity();
                _actionMap.insert(std::pair<NovelRT::Atom, std::string>(entityActionId, act.actionName));
                _logger.logDebug("Input Mapped: \"{}\" to {}", act.actionName, act.pairedKey.GetKeyName());
            }
            _firstUpdate = false;
        }

        _service->Update(delta);

        auto inputs = catalogue.GetComponentView<InputEventComponent>();

        for (auto [entity, input] : inputs)
        {
            if (_service->GetKeyState(_actionMap.at(input.actionId)) == NovelRT::Input::KeyState::Idle)
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
                if (_service->GetKeyState(action.second) != NovelRT::Input::KeyState::Idle)
                {
                    auto mouse = _service->GetMousePosition();
                    in = InputEventComponent{action.first, _service->GetKeyState(action.second), mouse.x, mouse.y};
                    inputs.AddComponent(action.first, in);
                }
            }
        }
    }

    void InputSystem::AddMapping(std::string name, std::string id)
    {
        unused(_service->AddInputAction(name, id));
    }

    void InputSystem::AddDefaultKBMMapping()
    {
        AddMapping("Up", "W");
        AddMapping("Down", "S");
        AddMapping("Left", "A");
        AddMapping("Right", "D");
        AddMapping("LeftClick", "LeftMouseButton");
        AddMapping("A", "K");
        AddMapping("B", "L");
    }

    std::string& InputSystem::GetMappingName(EntityId id)
    {
        return _actionMap.at(id);
    }

    InputSystem::~InputSystem() noexcept
    {
        _service->TearDown();
    }
}
