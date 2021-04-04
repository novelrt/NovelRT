// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GLFWWINDOWINGDEVICE_H
#define NOVELRT_GLFWWINDOWINGDEVICE_H

#include "../../../Maths/GeoVector2F.h"
#include "../IWindowingDevice.h"
#include <cstdint>

// TODO: Figure out if this is required
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <memory>

namespace NovelRT::Experimental::Windowing::Glfw
{
    class GlfwWindowingDevice : public IWindowingDevice
    {
    private:
        std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> _window;

    public:
        GlfwWindowingDevice() noexcept;

        [[nodiscard]] inline GLFWwindow* GetRawGLFWwindowHandle() const noexcept
        {
            return _window.get();
        }

        void Initialise(NovelRT::Windowing::WindowMode windowMode, Maths::GeoVector2F desiredWindowSize) final;

        void TearDown() noexcept final;

        ~GlfwWindowingDevice();
    };
} // namespace NovelRT::Experimental::Windowing::Glfw

#endif // NOVELRT_GLFWWINDOWINGDEVICE_H
