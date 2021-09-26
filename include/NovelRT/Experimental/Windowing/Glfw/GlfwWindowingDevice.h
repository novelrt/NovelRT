// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_WINDOWING_GLFW_GLFWWINDOWINGDEVICE_H
#define NOVELRT_EXPERIMENTAL_WINDOWING_GLFW_GLFWWINDOWINGDEVICE_H

#ifndef NOVELRT_EXPERIMENTAL_WINDOWING_GLFW_H
#error NovelRT does not support including types explicitly by default. Please include Windowing.Glfw.h instead for the Windowing::Glfw namespace subset.
#endif

namespace NovelRT::Experimental::Windowing::Glfw
{
    class GlfwWindowingDevice : public IWindowingDevice
    {
    private:
        std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> _window;

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

        ~GlfwWindowingDevice();
    };
} // namespace NovelRT::Experimental::Windowing::Glfw

#endif // NOVELRT_EXPERIMENTAL_WINDOWING_GLFW_GLFWWINDOWINGDEVICE_H
