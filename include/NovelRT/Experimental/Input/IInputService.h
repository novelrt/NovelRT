// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_INPUT_IINPUTSERVICE_H
#define NOVELRT_EXPERIMENTAL_INPUT_IINPUTSERVICE_H

#ifndef NOVELRT_EXPERIMENTAL_INPUT_H
#error NovelRT does not support including types explicitly by default. Please include Input.h instead for the Input namespace subset.
#endif

namespace NovelRT::Experimental::Input
{
    class IInputService : public std::enable_shared_from_this<IInputService>
    {
    protected:
        LoggingService _logger;
        std::list<InputAction> _mappedActions;

        std::map<std::string, NovelKey> _availableKeys;
    public:
        virtual void Initialise(void* window) = 0;
        virtual void TearDown() noexcept = 0;
        virtual void Update(Timing::Timestamp delta) = 0;
        [[nodiscard]] virtual bool IsKeyPressed(std::string key) = 0;
        [[nodiscard]] virtual bool IsKeyHeld(std::string key) = 0;
        [[nodiscard]] virtual bool IsKeyReleased(std::string key) = 0;
        [[nodiscard]] virtual InputAction& AddInputAction(std::string actionName, std::string keyIdentifier) = 0;
        virtual NovelKey& GetAvailableKey(std::string keyRequested) = 0;
        virtual NovelRT::Maths::GeoVector2F& GetMousePosition() = 0;

        virtual ~IInputService() = default;
    };
}

#endif // NOVELRT_EXPERIMENTAL_INPUT_IINPUTSERVICE_H
