// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_WINDOWING_GLFW_GLFWWINDOWINGPLUGINPROVIDER_H
#define NOVELRT_EXPERIMENTAL_WINDOWING_GLFW_GLFWWINDOWINGPLUGINPROVIDER_H

#ifndef NOVELRT_EXPERIMENTAL_WINDOWING_GLFW_H
#error NovelRT does not support including types explicitly by default. Please include Windowing.Glfw.h instead for the Windowing::Glfw namespace subset.
#endif

namespace NovelRT::Experimental::Windowing::Glfw
{
    class GlfwWindowingPluginProvider final : public PluginManagement::IWindowingPluginProvider
    {
    private:
        std::shared_ptr<GlfwWindowingDevice> _windowingDevice;

        [[nodiscard]] GlfwWindowingDevice* GetWindowingDeviceInternal() override;

    public:
        GlfwWindowingPluginProvider() noexcept;

        [[nodiscard]] inline std::shared_ptr<GlfwWindowingDevice> GetWindowingDevice()
        {
            return std::dynamic_pointer_cast<GlfwWindowingDevice>(GetWindowingDeviceInternal()->shared_from_this());
        }
    };
}

#endif // NOVELRT_EXPERIMENTAL_WINDOWING_GLFW_GLFWWINDOWINGPLUGINPROVIDER_H
