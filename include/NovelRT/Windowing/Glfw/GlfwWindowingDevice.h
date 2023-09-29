// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_WINDOWING_GLFW_GLFWWINDOWINGDEVICE_H
#define NOVELRT_WINDOWING_GLFW_GLFWWINDOWINGDEVICE_H

#ifndef NOVELRT_WINDOWING_GLFW_H
#error NovelRT does not support including types explicitly by default. Please include Windowing.Glfw.h instead for the Windowing::Glfw namespace subset.
#endif

namespace NovelRT::Windowing::Glfw
{
    class GlfwWindowingDevice final : public IWindowingDevice
    {
    public:
        struct MouseClickEventArgs
        {
            int32_t button = 0;
            int32_t action = 0;
            Maths::GeoVector2F mousePosition = Maths::GeoVector2F::Zero();
        };

        struct KeyboardButtonChangeEventArgs
        {
            int32_t key = 0;
            int32_t action = 0;
        };

        Utilities::Event<MouseClickEventArgs> MouseButtonClicked;
        Utilities::Event<KeyboardButtonChangeEventArgs> KeyboardButtonChanged;

    private:
        std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> _window;
        std::string _currentTitle;

    public:
        GlfwWindowingDevice() noexcept;

        [[nodiscard]] Maths::GeoVector2F GetSize() const noexcept final;
        [[nodiscard]] void* GetHandle() const noexcept final;
        [[nodiscard]] void* GetContextHandle() const noexcept final;
        [[nodiscard]] Graphics::GraphicsSurfaceKind GetKind() const noexcept final;

        [[nodiscard]] inline GLFWwindow* GetRawGLFWwindowHandle() const noexcept
        {
            return _window.get();
        }

        void Initialise(NovelRT::Windowing::WindowMode windowMode, Maths::GeoVector2F desiredWindowSize) final;
        void TearDown() noexcept final;

        [[nodiscard]] inline bool GetIsVisible() const noexcept final
        {
            return glfwGetWindowAttrib(GetRawGLFWwindowHandle(), GLFW_VISIBLE) != 0;
        }

        [[nodiscard]] inline bool GetShouldClose() const noexcept final
        {
            return glfwWindowShouldClose(GetRawGLFWwindowHandle());
        }

        [[nodiscard]] inline std::string GetWindowTitle() const noexcept final
        {
            return _currentTitle;
        }

        inline void SetWindowTitle(const std::string& newTitle) final
        {
            _currentTitle = newTitle;
            glfwSetWindowTitle(_window.get(), _currentTitle.c_str());
        }

        void ProcessAllMessages() final;
        ~GlfwWindowingDevice() final;
    };
}

#endif // NOVELRT_WINDOWING_GLFW_GLFWWINDOWINGDEVICE_H
