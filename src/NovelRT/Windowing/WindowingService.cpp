// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

namespace NovelRT::Windowing {
  WindowingService::WindowingService() noexcept :
    WindowResized(Utilities::Event<Maths::GeoVector2F>()),
    WindowTornDown(Utilities::Event<>()),
    MouseButtonClicked(Utilities::Event<MouseClickEventArgs>()),
    KeyboardButtonChanged(Utilities::Event<KeyboardButtonChangeEventArgs>()),
    _window(std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)>(nullptr, glfwDestroyWindow)),
    _logger(LoggingService(Utilities::Misc::CONSOLE_LOG_WINDOWING)),
#if defined(_WIN32) || defined(_WIN64)
    _optimus(),
#endif
    _isTornDown(false) {
  }

  void WindowingService::errorCallback(int32_t, const char* error) {
    _logger.logError("Could not initialize GLFW: {}", error);
  }

  void WindowingService::initialiseWindow(int32_t /*displayNumber*/, const std::string& windowTitle, bool transparencyEnabled) {
    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* displayData = glfwGetVideoMode(primaryMonitor);

    // create window
    auto wData = static_cast<int32_t>(displayData->width * 0.7f);
    auto hData = static_cast<int32_t>(displayData->height * 0.7f);

    //Check is only for Windows - stays inside definition checks
#if defined(_WIN64)
      static const char* OptimusLibraryName = "nvapi64.dll";
      checkForOptimus(OptimusLibraryName);
#elif defined(_WIN32)
      static const char* OptimusLibraryName = "nvapi.dll";
      checkForOptimus(OptimusLibraryName);
#endif

    //Set Framebuffer Transparency
   if (transparencyEnabled) {
     glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
   }
    _logger.logInfo("Attempting to create OpenGL ES v3.0 context using EGL API");

    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);

    auto window = glfwCreateWindow(wData, hData, windowTitle.c_str(), nullptr, nullptr);

    if (window == nullptr)
    {
      _logger.logWarning("Failed to create OpenGL ES v3.0 context using EGL API");
      _logger.logInfo("Attempting to create OpenGL ES v3.0 context using native API");

      glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
      glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);

      window = glfwCreateWindow(wData, hData, windowTitle.c_str(), nullptr, nullptr);

      if (window == nullptr)
      {
        _logger.logWarning("Failed to create OpenGL ES v3.0 context using native API");
        _logger.logInfo("Attempting to create OpenGL v4.3 forward-compatible core profile context using native API");

        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);

#ifndef NDEBUG
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

        window = glfwCreateWindow(wData, hData, windowTitle.c_str(), nullptr, nullptr);
        _logger.throwIfNullPtr(window, "Failed to create OpenGL v4.3 context using native API");
      }
    }

    _windowTitle = windowTitle;
    _logger.logInfo("Window succesfully created.");

    glfwSetWindowAttrib(window, GLFW_RESIZABLE, GLFW_TRUE);
    glfwSetWindowAttrib(window, GLFW_VISIBLE, GLFW_TRUE);

    _window = std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)>(window, glfwDestroyWindow);

    glfwSetWindowUserPointer(_window.get(), reinterpret_cast<void*>(this));


    glfwSetWindowCloseCallback(_window.get(), [](auto targetWindow) {
      auto thisPtr = reinterpret_cast<WindowingService*>(glfwGetWindowUserPointer(targetWindow));
      thisPtr->_logger.throwIfNullPtr(thisPtr, "Unable to continue! WindowUserPointer is NULL. Did you modify this pointer?");

      thisPtr->tearDown();
      thisPtr->WindowTornDown();
      });

    glfwSetWindowSizeCallback(_window.get(), [](auto targetWindow, auto w, auto h) {
      auto thisPtr = reinterpret_cast<WindowingService*>(glfwGetWindowUserPointer(targetWindow));
      thisPtr->_logger.throwIfNullPtr(thisPtr, "Unable to continue! WindowUserPointer is NULL. Did you modify this pointer?");

      thisPtr->_windowSize = Maths::GeoVector2F(static_cast<float>(w), static_cast<float>(h));
      thisPtr->_logger.logInfo("New size detected! Notifying GFX and other members...");
      thisPtr->WindowResized(thisPtr->_windowSize); });
    _windowSize = Maths::GeoVector2F(static_cast<float>(wData), static_cast<float>(hData));

    glfwSetMouseButtonCallback(_window.get(), [](auto targetWindow, auto mouseButton, auto action, auto /*mods*/) {
      auto thisPtr = reinterpret_cast<WindowingService*>(glfwGetWindowUserPointer(targetWindow));
      thisPtr->_logger.throwIfNullPtr(thisPtr, "Unable to continue! WindowUserPointer is NULL. Did you modify this pointer?");

      double x = 0, y = 0;
      glfwGetCursorPos(targetWindow, &x, &y);
      thisPtr->MouseButtonClicked(MouseClickEventArgs{ mouseButton, action, Maths::GeoVector2F((float)x, (float)y) });
      });



    glfwSetKeyCallback(_window.get(), [](auto targetWindow, auto key, auto /*scancode*/, auto action, auto /*mods*/) {
      auto thisPtr = reinterpret_cast<WindowingService*>(glfwGetWindowUserPointer(targetWindow));
      thisPtr->_logger.throwIfNullPtr(thisPtr, "Unable to continue! WindowUserPointer is NULL. Did you modify this pointer?");
      thisPtr->KeyboardButtonChanged(KeyboardButtonChangeEventArgs{key, action});
      });


  }

#if defined(_WIN64) || defined(_WIN32)
  void WindowingService::checkForOptimus(const char* library) {
    _optimus = LoadLibrary(reinterpret_cast<LPCSTR>(library));
    if (_optimus != nullptr) {
      _logger.logInfo("NVIDIA GPU detected. Enabling...");
    } else {
      _logger.logInfo("NVIDIA GPU not detected. Continuing without Optimus support.");
    }
  }
#endif

  void WindowingService::tearDown() {
    if (_isTornDown) return;
#if defined(_WIN64) || defined(_WIN32)
    if (_optimus != nullptr) {
      FreeLibrary(_optimus);
    }
#endif

    _isTornDown = true;

    glfwDestroyWindow(getWindow());
  }
}
