// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_IINPUTDEVICE_H
#define NOVELRT_IINPUTDEVICE_H

#ifndef NOVELRT_EXPERIMENTAL_INPUT_H
#error NovelRT does not support including types explicitly by default. Please include Input.h instead for the Input namespace subset.
#endif

namespace NovelRT::Experimental::Input
{
    class IInputgDevice
    {
    private:
        static inline const uint32_t INPUT_BUFFER_COUNT = 2;

        uint32_t _previousBufferIndex;
        uint32_t _currentBufferIndex;
        std::array<std::map<KeyCode, KeyStateFrameChangeLog>, INPUT_BUFFER_COUNT> _keyStates;

        Maths::GeoVector2F _screenSize;
        Maths::GeoVector2F _cursorPosition;

        //InteractionObject* _clickTarget;
        //void HandleInteractionDraw(InteractionObject* target);

        virtual void processKeyState(KeyCode code, KeyState state) = 0;
        virtual void processKeyStates() = 0;
        virtual void acceptMouseButtonClickPush(int32_t button, int32_t action, Maths::GeoVector2F mousePosition) = 0;
        virtual void acceptKeyboardInputBindingPush(int32_t key, int32_t action) = 0;

    public:
        virtual void consumePlayerInput() = 0;

        // std::unique_ptr<BasicInteractionRect> createBasicInteractionRect(Transform transform, int32_t layer);
        // virtual void executeClickedInteractable() noexcept = 0;

        inline void setScreenSize(Maths::GeoVector2F value) noexcept
        {
            _screenSize = value;
        }
    };
} // namespace NovelRT::Experimental::Input

#endif // NOVELRT_IINPUTDEVICE_H
