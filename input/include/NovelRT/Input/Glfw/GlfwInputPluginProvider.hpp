// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INPUT_GLFW_GLFWINPUTPLUGINPROVIDER_H
#define NOVELRT_INPUT_GLFW_GLFWINPUTPLUGINPROVIDER_H

namespace NovelRT::Input::Glfw
{
    class GlfwInputPluginProvider final : public PluginManagement::IInputPluginProvider
    {
    protected:
        std::shared_ptr<GlfwInputDevice> _inputDevice;

        [[nodiscard]] GlfwInputDevice* GetInputDeviceInternal() override;

    public:
        GlfwInputPluginProvider() noexcept;

        [[nodiscard]] inline std::shared_ptr<GlfwInputDevice> GetInputDevice()
        {
            return std::dynamic_pointer_cast<GlfwInputDevice>(GetInputDeviceInternal()->shared_from_this());
        }
    };
}

#endif // NOVELRT_INPUT_GLFW_GLFWINPUTPLUGINPROVIDER_H
