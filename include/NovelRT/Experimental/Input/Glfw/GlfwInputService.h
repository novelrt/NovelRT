// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_INPUT_GLFW_GLFWINPUTSERVICE_H
#define NOVELRT_EXPERIMENTAL_INPUT_GLFW_GLFWINPUTSERVICE_H

#ifndef NOVELRT_EXPERIMENTAL_INPUT_GLFW_H
#error NovelRT does not support including types explicitly by default. Please include Input.Glfw.h instead for the Input::Glfw namespace subset.
#endif

namespace NovelRT::Experimental::Input::Glfw
{
    class GlfwInputService final : public Input::IInputService
    {
    private:
        bool _isInitialised;
        void KeyCallback(GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mods);
        GLFWwindow* _window;
    public:
        GlfwInputService() noexcept;

        void Initialise(void* window) final;
        void TearDown() noexcept final;
        void Update(Timing::Timestamp delta) final;
        [[nodiscard]] bool IsKeyPressed(std::string key) final;
        void AddInputAction(InputAction action) noexcept final;
        NovelKey& GetAvailableKey(std::string keyRequested) final;


        ~GlfwInputService() final;
    };
}

#endif // NOVELRT_EXPERIMENTAL_INPUT_GLFW_GLFWINPUTSERVICE_H
