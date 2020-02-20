// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

namespace NovelRT::Windowing {
  WindowingService::WindowingService(NovelRunner* const runner) :
    WindowResized(Utilities::Event<Maths::GeoVector<float>>()),
    WindowTornDown(Utilities::Event<>()),
    _window(std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)>(nullptr, glfwDestroyWindow)),
    _logger(LoggingService(Utilities::Misc::CONSOLE_LOG_WINDOWING)),
    _runner(runner),
    _isTornDown(false) {
  }

  void WindowingService::errorCallback(int, const char* error) {
    _logger.logError("Could not initialize GLFW: ", error);
  }

  void WindowingService::initialiseWindow(int displayNumber, const std::string& windowTitle) {
    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* displayData = glfwGetVideoMode(primaryMonitor);

    // create window
    float wData = displayData->width * 0.7f;
    float hData = displayData->height * 0.7f;

    _logger.logInfoLine("Attempting to create OpenGL ES v3.0 context using EGL API");

    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);

    auto window = glfwCreateWindow(wData, hData, _windowTitle.c_str(), nullptr, nullptr);

    if (window == nullptr)
    {
      _logger.logWarning("Failed to create OpenGL ES v3.0 context using EGL API");
      _logger.logInfo("Attempting to create OpenGL ES v3.0 context using native API");

      glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
      glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);

      window = glfwCreateWindow(wData, hData, _windowTitle.c_str(), nullptr, nullptr);

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

        window = glfwCreateWindow(wData, hData, _windowTitle.c_str(), nullptr, nullptr);
        _logger.throwIfNullPtr(window, "Failed to create OpenGL v4.3 context using native API");
      }
    }

    _logger.logInfo("Window succesfully created.");

    glfwSetWindowAttrib(window, GLFW_RESIZABLE, GLFW_TRUE);
    glfwSetWindowAttrib(window, GLFW_VISIBLE, GLFW_TRUE);

    _window = std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)>(window, glfwDestroyWindow);

    glfwSetWindowUserPointer(_window.get(), reinterpret_cast<void*>(this));


    glfwSetWindowCloseCallback(_window.get(), [](auto window) {
      auto thisPtr = reinterpret_cast<WindowingService*>(glfwGetWindowUserPointer(window));
      thisPtr->_logger.throwIfNullPtr(thisPtr, "Unable to continue! WindowUserPointer is NULL. Did you modify this pointer?");

      thisPtr->tearDown();
      thisPtr->WindowTornDown();
      });

    glfwSetWindowSizeCallback(_window.get(), [](auto window, auto w, auto h) {
      auto thisPtr = reinterpret_cast<WindowingService*>(glfwGetWindowUserPointer(window));
      thisPtr->_logger.throwIfNullPtr(thisPtr, "Unable to continue! WindowUserPointer is NULL. Did you modify this pointer?");

      thisPtr->_windowSize = Maths::GeoVector<float>(w, h);
      thisPtr->_logger.logInfo("New size detected! Notifying GFX and other members...");
      thisPtr->WindowResized(thisPtr->_windowSize); });
    _windowSize = Maths::GeoVector<float>(wData, hData);

    glfwSetMouseButtonCallback(_window.get(), [](auto window, auto mouseButton, auto action, auto mods) {
      auto thisPtr = reinterpret_cast<WindowingService*>(glfwGetWindowUserPointer(window));
      thisPtr->_logger.throwIfNullPtr(thisPtr, "Unable to continue! WindowUserPointer is NULL. Did you modify this pointer?");

      double x = 0, y = 0;
      glfwGetCursorPos(window, &x, &y);
      thisPtr->_runner->getInteractionService().lock()->acceptMouseButtonClickPush(mouseButton, action, Maths::GeoVector<float>(static_cast<float>(x), static_cast<float>(y)));
      });



    glfwSetKeyCallback(_window.get(), [](auto window, auto key, auto scancode, auto action, auto mods) {
      auto thisPtr = reinterpret_cast<WindowingService*>(glfwGetWindowUserPointer(window));
      thisPtr->_logger.throwIfNullPtr(thisPtr, "Unable to continue! WindowUserPointer is NULL. Did you modify this pointer?");

      thisPtr->_runner->getInteractionService().lock()->acceptKeyboardInputBindingPush(key, action);
      });


  }
  void WindowingService::tearDown() {
    if (_isTornDown) return;

    _isTornDown = true;

    glfwDestroyWindow(getWindow());
  }
}
