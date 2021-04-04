// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InitialisationFailureException.h>
#include <NovelRT/Exceptions/NotSupportedException.h>
#include <NovelRT/Experimental/EngineConfig.h>
#include <NovelRT/Experimental/Windowing/Glfw/GlfwWindowingDevice.h>
#include <cmath>

namespace NovelRT::Experimental::Windowing::Glfw
{
    GlfwWindowingDevice::GlfwWindowingDevice() noexcept : _window(nullptr, nullptr)
    {
    }

    void GlfwWindowingDevice::Initialise(NovelRT::Windowing::WindowMode windowMode,
                                         Maths::GeoVector2F desiredWindowSize)
    {
        if (glfwInit() == GLFW_FALSE)
        {
            const char* output = nullptr;
            glfwGetError(&output);
            throw Exceptions::InitialisationFailureException("GLFW3 failed to initialise.", std::string(output));
        }

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        GLFWmonitor* monitor = nullptr;

        switch (windowMode)
        {
            case NovelRT::Windowing::WindowMode::Windowed:
                glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
                break;
            case NovelRT::Windowing::WindowMode::Borderless:
                glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
                break;
            case NovelRT::Windowing::WindowMode::Fullscreen:
                monitor = glfwGetPrimaryMonitor();
                break;
            default:
                throw Exceptions::NotSupportedException(
                    "The specified window mode is either not valid or not supported.");
        }

        auto window =
            glfwCreateWindow(static_cast<int32_t>(floor(desiredWindowSize.x)),
                             static_cast<int32_t>(floor(desiredWindowSize.y)), EngineConfig::ApplicationName().c_str(), monitor, nullptr);

        if (window == nullptr)
        {
            const char* output = nullptr;
            glfwGetError(&output);
            throw Exceptions::InitialisationFailureException("GLFW3 failed to initialise.", std::string(output));
        }

        glfwSetWindowAttrib(window, GLFW_VISIBLE, GLFW_TRUE);
        glfwSetWindowAttrib(window, GLFW_RESIZABLE, windowMode == NovelRT::Windowing::WindowMode::Windowed);

        _window = std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)>(window, glfwDestroyWindow);

        if (glfwVulkanSupported() == GLFW_FALSE)
        {
            return;
        }

        uint32_t extensionCount = 0;
        auto extensions = glfwGetRequiredInstanceExtensions(&extensionCount);
        if (extensionCount == 0)
        {
            const char* output = nullptr;
            glfwGetError(&output);
            throw Exceptions::InitialisationFailureException("GLFW3 failed to initialise.", std::string(output));
        }

        for (size_t i = 0; i < extensionCount; i++)
        {
            EngineConfig::RequiredVulkanExtensions().emplace_back(extensions[i]);
        }
    }

    void GlfwWindowingDevice::TearDown() noexcept
    {
        _window.reset();
    }

    GlfwWindowingDevice::~GlfwWindowingDevice()
    {
        TearDown();
        glfwTerminate();
    }

} // namespace NovelRT::Experimental::Windowing::Glfw