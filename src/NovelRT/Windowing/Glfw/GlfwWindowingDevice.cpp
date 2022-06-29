// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include "NovelRT/Windowing/Glfw/Windowing.Glfw.h"

namespace NovelRT::Windowing::Glfw
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

        auto window = glfwCreateWindow(static_cast<int32_t>(floor(desiredWindowSize.x)),
                                       static_cast<int32_t>(floor(desiredWindowSize.y)),
                                       EngineConfig::ApplicationName().c_str(), monitor, nullptr);

        if (window == nullptr)
        {
            const char* output = nullptr;
            glfwGetError(&output);
            throw Exceptions::InitialisationFailureException("GLFW3 failed to initialise.", std::string(output));
        }

#ifndef __APPLE__
        glfwSetWindowAttrib(window, GLFW_VISIBLE, GLFW_TRUE);
#endif

        glfwSetWindowAttrib(window, GLFW_RESIZABLE, windowMode == NovelRT::Windowing::WindowMode::Windowed);
        glfwSetWindowUserPointer(window, this);

        glfwSetWindowSizeCallback(window, [](auto window, auto width, auto height) {
            auto thisDevice = reinterpret_cast<GlfwWindowingDevice*>(glfwGetWindowUserPointer(window));
            auto countFfs = thisDevice->SizeChanged.getHandlerCount();
            unused(countFfs);
            thisDevice->SizeChanged(Maths::GeoVector2F(static_cast<float>(width), static_cast<float>(height)));
        });

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
            if (output != nullptr)
            {
                throw Exceptions::InitialisationFailureException("GLFW3 failed to initialise.", std::string(output));
            }
            else
            {
                throw Exceptions::InitialisationFailureException(
                    "GLFW3 failed to initialise.",
                    "Attempting to fetch the required Vulkan extensions failed with a count of zero.");
            }
        }

        auto& requiredExtensions = EngineConfig::RequiredVulkanInstanceExtensions();

        for (size_t i = 0; i < extensionCount; i++)
        {
            requiredExtensions.emplace_back(extensions[i]);
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

    Maths::GeoVector2F GlfwWindowingDevice::GetSize() const noexcept
    {
        int32_t width = 0;
        int32_t height = 0;

        glfwGetFramebufferSize(GetRawGLFWwindowHandle(), &width, &height);

        if (width == 0 || height == 0)
        {
            return Maths::GeoVector2F::zero();
        }

        return Maths::GeoVector2F(static_cast<float>(width), static_cast<float>(height));
    }

    void* GlfwWindowingDevice::GetHandle() const noexcept
    {
        return GetRawGLFWwindowHandle();
    }

    void* GlfwWindowingDevice::GetContextHandle() const noexcept
    {
        return reinterpret_cast<void*>(&glfwCreateWindowSurface);
    }

    Graphics::GraphicsSurfaceKind GlfwWindowingDevice::GetKind() const noexcept
    {
        return Graphics::GraphicsSurfaceKind::Glfw;
    }

    void GlfwWindowingDevice::ProcessAllMessages()
    {
        glfwPollEvents();
    }
} // namespace NovelRT::Windowing::Glfw
