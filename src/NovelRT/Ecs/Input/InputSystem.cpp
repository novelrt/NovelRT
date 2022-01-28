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
        auto mappings = _service->GetAllMappings();

        for (auto [entity, input] : inputs)
        {
            if (_service->GetKeyState(_actionMap.at(input.actionId)) == Experimental::Input::KeyState::Idle)
            {
                inputs.RemoveComponent(entity);
            }
            else
            {
                auto mouse = _service->GetMousePosition();
                auto event = InputEventComponent{input.actionId, _service->GetKeyState(_actionMap.at(input.actionId)), input.mousePositionX, input.mousePositionY};
                inputs.PushComponentUpdateInstruction(entity, event);
            }
        }
        inputs = catalogue.GetComponentView<InputEventComponent>();



        for (auto action : mappings)
        {
            bool found = false;
            auto findResult = std::find_if(inputs.begin(), inputs.end(),  [&](const std::pair<EntityId, InputEventComponent> &pair){
                                               auto x = _actionMap.at(pair.second.actionId);
                                    return _actionMap.at(pair.second.actionId). == action;
                                });


            if (findResult == inputs.end())
            {
                auto entity = catalogue.CreateEntity();
                inputs.AddComponent(entity, InputEventComponent{});
            }
        }
    }

    void InputSystem::AddMapping(std::string name, std::string id)
    {
        unused(_service->AddInputAction(name, id));
        _actionMap.insert(std::pair<NovelRT::Atom, std::string>(NovelRT::Atom::GetNextEcsInputActionId(), name));
    }

    void InputSystem::AddDefaultKBMMapping()
    {
        AddMapping("Down", "S");
        AddMapping("Left", "A");
        AddMapping("Right", "D");
        AddMapping("LeftClick", "LeftMouseButton");
        AddMapping("A", "K");
        AddMapping("B", "L");
    }

    InputSystem::~InputSystem() noexcept
    {
        _service->TearDown();
    }
}
