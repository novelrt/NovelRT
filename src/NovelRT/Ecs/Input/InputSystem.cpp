// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Ecs.h>

namespace NovelRT::Ecs::Input
{
    InputSystem::InputSystem(std::shared_ptr<PluginManagement::IWindowingPluginProvider> windowingProvider,
                             std::shared_ptr<PluginManagement::IInputPluginProvider> inputProvider) :
                             _logger(Utilities::Misc::CONSOLE_LOG_ECS_INPUT)
    {
        _inputMap = std::map<std::string, NovelRT::Atom>();
        _device = inputProvider->GetInputService();
        _device->Initialise(windowingProvider->GetWindowingDevice().get());
    }

    void InputSystem::Update(Timing::Timestamp delta, Ecs::Catalogue catalogue)
    {
        _device->Update(delta);

        auto inputs = catalogue.GetComponentView<InputEventComponent>();
        auto mouse = _device->GetMousePosition();
        for (auto&& input : _inputMap)
        {
            InputEventComponent in;
            auto state = _device->GetKeyState(input.first);
            if (inputs.TryGetComponent(input.second, in))
            {

                switch (state)
                {
                    case NovelRT::Input::KeyState::KeyUp:
                    case NovelRT::Input::KeyState::KeyDown:
                    case NovelRT::Input::KeyState::KeyDownHeld:
                    {

                        auto event = InputEventComponent{in.actionId, state, mouse.x, mouse.y};
                        inputs.PushComponentUpdateInstruction(in.actionId, event);
                        break;
                    }
                    case NovelRT::Input::KeyState::Idle:
                    default:
                    {
                        inputs.RemoveComponent(input.second);
                        break;
                    }
                }
            }
            else
            {
                if (state != NovelRT::Input::KeyState::Idle)
                {
                    in = InputEventComponent{input.second, state, mouse.x, mouse.y};
                    inputs.AddComponent(input.second, in);
                }
            }
        }
    }

    void InputSystem::AddMapping(std::string name, std::string id)
    {
        static AtomFactory& _entityIdFactory = AtomFactoryDatabase::GetFactory("EntityId");

        unused(_device->AddInputAction(name, id));
        auto entityMappingId = _entityIdFactory.GetNext();
        _inputMap.insert(std::pair<std::string, NovelRT::Atom>(name, entityMappingId));
        _logger.logDebug("Input Mapped: \"{}\" to {}", name, id);
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

    NovelRT::Atom InputSystem::GetMappingId(const std::string& mappingName) const
    {
        return _inputMap.at(mappingName);
    }

}
