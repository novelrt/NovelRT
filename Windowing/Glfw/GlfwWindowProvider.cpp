// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/InitialisationFailureException.hpp>
#include <NovelRT/Exceptions/NotSupportedException.hpp>

#include <NovelRT/Windowing/Glfw/GlfwWindowProvider.hpp>

#include <vector>

namespace NovelRT::Windowing
{
    using GlfwWindowProvider = WindowProvider<Glfw::GlfwWindowingBackend>;

    GlfwWindowProvider::WindowProvider(
        NovelRT::Windowing::WindowMode windowMode,
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
                                       "NovelRT", monitor, nullptr);
                                       // TODO: EngineConfig was here
                                       //EngineConfig::ApplicationName().c_str(), monitor, nullptr);

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
            auto thisDevice = reinterpret_cast<GlfwWindowProvider*>(glfwGetWindowUserPointer(window));
            thisDevice->SizeChanged(Maths::GeoVector2F(static_cast<float>(width), static_cast<float>(height)));
        });

        glfwSetKeyCallback(window, [](auto window, auto key, auto /*scancode*/, auto action, auto /*mods*/) {
            auto thisPtr = reinterpret_cast<GlfwWindowProvider*>(glfwGetWindowUserPointer(window));
            thisPtr->KeyboardButtonChanged(ButtonChangeEventArgs{key, action});
        });

        glfwSetMouseButtonCallback(window, [](auto window, auto mouseButton, auto action, auto /*mods*/) {
            auto thisPtr = reinterpret_cast<GlfwWindowProvider*>(glfwGetWindowUserPointer(window));
            thisPtr->MouseButtonClicked(ButtonChangeEventArgs{mouseButton, action});
        });

        glfwSetCursorPosCallback(window, [](auto window, double x, double y) {
            auto thisPtr = reinterpret_cast<GlfwWindowProvider*>(glfwGetWindowUserPointer(window));
            thisPtr->CursorMoved(CursorPositionEventArgs{x, y});
        });

        _window = window;
    }

    GlfwWindowProvider::~WindowProvider() noexcept
    {
        if (_window) glfwDestroyWindow(_window);
        glfwTerminate();
    }

    void GlfwWindowProvider::ProcessAllMessages()
    {
        glfwPollEvents();
    }

    bool GlfwWindowProvider::IsVisible() const noexcept
    {
        return glfwGetWindowAttrib(_window, GLFW_VISIBLE) != 0;
    }

    bool GlfwWindowProvider::ShouldClose() const noexcept
    {
        return glfwWindowShouldClose(_window);
    }

    std::string GlfwWindowProvider::GetWindowTitle() const noexcept
    {
        return _currentTitle;
    }

    inline void GlfwWindowProvider::SetWindowTitle(const std::string& newTitle)
    {
        _currentTitle = newTitle;
        glfwSetWindowTitle(_window, _currentTitle.c_str());
    }

    Maths::GeoVector2F GlfwWindowProvider::GetSize() const noexcept
    {
        int32_t width = 0;
        int32_t height = 0;

        glfwGetFramebufferSize(_window, &width, &height);

        if (width == 0 || height == 0)
        {
            return Maths::GeoVector2F::Zero();
        }

        return Maths::GeoVector2F(static_cast<float>(width), static_cast<float>(height));
    }

    void* GlfwWindowProvider::GetHandle() const noexcept
    {
        return _window;
    }

    void* GlfwWindowProvider::GetContextHandle() const noexcept
    {
        return reinterpret_cast<void*>(&glfwCreateWindowSurface);
    }

    Graphics::GraphicsSurfaceKind GlfwWindowProvider::GetKind() const noexcept
    {
        return Graphics::GraphicsSurfaceKind::Glfw;
    }
}
