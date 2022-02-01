// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INPUT_GLFW_GLFWINPUTDEVICE_H
#define NOVELRT_INPUT_GLFW_GLFWINPUTDEVICE_H

#ifndef NOVELRT_INPUT_GLFW_H
#error NovelRT does not support including types explicitly by default. Please include Input.Glfw.h instead for the Input::Glfw namespace subset.
#endif

namespace NovelRT::Input::Glfw
{
    class GlfwInputDevice final : public Input::IInputDevice
    {
    private:
        bool _isInitialised;
        GLFWwindow* _window;
        NovelRT::Timing::StepTimer _timer;
        NovelRT::Utilities::Event<Timing::Timestamp> _dummyEvent;
        std::vector<InputAction> _previousStates;
        NovelRT::Maths::GeoVector2F _mousePos;

    public:
        GlfwInputDevice() noexcept;

        void Initialise(void* window) final;
        void Update(Timing::Timestamp delta) final;
        [[nodiscard]] bool IsKeyPressed(const std::string& input) final;
        [[nodiscard]] bool IsKeyHeld(const std::string& input) final;
        [[nodiscard]] bool IsKeyReleased(const std::string& input) final;
        [[nodiscard]] KeyState GetKeyState(const std::string& key) final;
        [[nodiscard]] InputAction& AddInputAction(const std::string& actionName, const std::string& keyIdentifier) final;
        [[nodiscard]] NovelKey& GetAvailableKey(const std::string& keyRequested) final;
        [[nodiscard]] NovelRT::Maths::GeoVector2F GetMousePosition() final;
        [[nodiscard]] gsl::span<InputAction> GetAllMappings() final;

        ~GlfwInputDevice() final;
    };
}

#endif // NOVELRT_INPUT_GLFW_GLFWINPUTDEVICE_H
