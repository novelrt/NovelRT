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
        uint32_t _previousBufferIndex;
        uint32_t _currentBufferIndex;
        bool _isInitialised;
        GLFWwindow* _window;
        std::vector<InputAction> _previousStates;
        NovelRT::Maths::GeoVector2F _mousePos;
        NovelRT::Maths::GeoVector2F _windowDimensions;

        void ProcessKeyInput(int32_t key, int32_t action);
        void ProcessMouseInput(int32_t key, int32_t action, NovelRT::Maths::GeoVector2F pos);
        void ProcessKeyState(int32_t action, KeyState state);

    public:
        GlfwInputDevice() noexcept;

        void Initialise(NovelRT::Windowing::IWindowingDevice* device, uint32_t inputBufferCount) final;
        void Update(Timing::Timestamp delta) final;
        [[nodiscard]] bool IsKeyPressed(const std::string& input) noexcept final;
        [[nodiscard]] bool IsKeyHeld(const std::string& input) noexcept final;
        [[nodiscard]] bool IsKeyReleased(const std::string& input) noexcept final;
        [[nodiscard]] KeyState GetKeyState(const std::string& key) noexcept final;
        [[nodiscard]] InputAction& AddInputAction(const std::string& actionName,
                                                  const std::string& keyIdentifier) final;
        [[nodiscard]] NovelKey& GetAvailableKey(const std::string& keyRequested) final;
        [[nodiscard]] NovelRT::Maths::GeoVector2F GetMousePosition() noexcept final;
        [[nodiscard]] NovelRT::Utilities::Misc::Span<InputAction> GetAllMappings() noexcept final;

        ~GlfwInputDevice() final;
    };
}

#endif // NOVELRT_INPUT_GLFW_GLFWINPUTDEVICE_H
