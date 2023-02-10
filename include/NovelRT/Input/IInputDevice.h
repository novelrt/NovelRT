// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INPUT_IINPUTSERVICE_H
#define NOVELRT_INPUT_IINPUTSERVICE_H

#ifndef NOVELRT_INPUT_H
#error NovelRT does not support including types explicitly by default. Please include Input.h instead for the Input namespace subset.
#endif

namespace NovelRT::Input
{
    class IInputDevice : public std::enable_shared_from_this<IInputDevice>
    {
    protected:
        LoggingService _logger;
        std::vector<InputAction> _mappedActions;
        std::map<std::string, NovelKey> _availableKeys;

    public:
        virtual void Initialise(void* window) = 0;
        virtual void Update(Timing::Timestamp delta) = 0;
        [[nodiscard]] virtual bool IsKeyPressed(const std::string& key) = 0;
        [[nodiscard]] virtual bool IsKeyHeld(const std::string& key) = 0;
        [[nodiscard]] virtual bool IsKeyReleased(const std::string& key) = 0;
        [[nodiscard]] virtual KeyState GetKeyState(const std::string& key) = 0;
        [[nodiscard]] virtual InputAction& AddInputAction(const std::string& actionName,
                                                          const std::string& keyIdentifier) = 0;
        [[nodiscard]] virtual NovelKey& GetAvailableKey(const std::string& keyRequested) = 0;
        [[nodiscard]] virtual NovelRT::Maths::GeoVector2F GetMousePosition() = 0;
        [[nodiscard]] virtual NovelRT::Utilities::Misc::Span<InputAction> GetAllMappings() = 0;

        virtual ~IInputDevice() = default;
    };
}

#endif // NOVELRT_INPUT_IINPUTSERVICE_H
