// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GLFWINPUTDEVICE_H
#define NOVELRT_GLFWINPUTDEVICE_H

#ifndef NOVELRT_EXPERIMENTAL_INPUT_GLFW_H
#error NovelRT does not support including types explicitly by default. Please include Input.Glfw.h instead for the Input::Glfw namespace subset.
#endif

namespace NovelRT::Experimental::Input::Glfw
{
    class GlfwInputDevice : public IInputDevice
    {
    private:
        void processKeyStates() final;
        void processKeyState(KeyCode code, KeyState state) final;
        void acceptMouseButtonClickPush(int32_t button,
                                        int32_t action,
                                        Maths::GeoVector2F mousePosition) final;
        void acceptKeyboardInputBindingPush(int32_t key, int32_t action) final;

    public:
        GlfwInputDevice() noexcept;

        void consumePlayerInput() final;
    };
} // namespace NovelRT::Experimental::Input::Glfw

#endif // NOVELRT_GLFWINPUTDEVICE_H
