// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

namespace NovelRT::Windowing {
  WindowingService::WindowingService(NovelRunner* const runner) :
    _window(std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)>(nullptr, glfwDestroyWindow)),
    _logger(LoggingService(Utilities::Misc::CONSOLE_LOG_WINDOWING)),
    _runner(runner), _isTornDown(false) {}

  void WindowingService::errorCallback(int, const char* error) {
    _logger.logError("Could not initialize GLFW: ", error);
  }

  void WindowingService::initialiseWindow(int displayNumber, const std::string& windowTitle) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_FALSE);

    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* displayData = glfwGetVideoMode(primaryMonitor);

    // create window
    float wData = displayData->width * 0.7f;
    float hData = displayData->height * 0.7f;
    auto window = glfwCreateWindow(wData, hData, _windowTitle.c_str(), nullptr, nullptr);
    glfwSetWindowAttrib(window, GLFW_RESIZABLE, GLFW_TRUE);
    glfwSetWindowAttrib(window, GLFW_VISIBLE, GLFW_TRUE);

    _window = std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)>(window, glfwDestroyWindow);
    if (_window == nullptr) {
      throw std::runtime_error("Unable to continue! Window could not be created.");
    }

    glfwSetWindowUserPointer(_window.get(), reinterpret_cast<void*>(this));


    glfwSetWindowCloseCallback(_window.get(), [](auto window) {
      auto thisPtr = reinterpret_cast<WindowingService*>(glfwGetWindowUserPointer(window));
      if (thisPtr == nullptr) throw std::runtime_error("Unable to continue! WindowUserPointer is NULL. Did you modify this pointer?");

      thisPtr->tearDown();
      thisPtr->raiseWindowTornDown();
      });

    glfwSetWindowSizeCallback(_window.get(), [](auto window, auto w, auto h) {
      auto thisPtr = reinterpret_cast<WindowingService*>(glfwGetWindowUserPointer(window));
      if (thisPtr == nullptr) throw std::runtime_error("Unable to continue! WindowUserPointer is NULL. Did you modify this pointer?");

      thisPtr->_windowSize = Maths::GeoVector<float>(w, h);
      thisPtr->_logger.logInfo("New size detected! Notifying GFX and other members...");
      thisPtr->raiseWindowResized(thisPtr->_windowSize); });
    _windowSize = Maths::GeoVector<float>(wData, hData);

    glfwSetMouseButtonCallback(_window.get(), [](auto window, auto mouseButton, auto action, auto mods) {
      auto thisPtr = reinterpret_cast<WindowingService*>(glfwGetWindowUserPointer(window));
      if (thisPtr == nullptr) throw std::runtime_error("Unable to continue! WindowUserPointer is NULL. Did you modify this pointer?");

      double x = 0, y = 0;
      glfwGetCursorPos(window, &x, &y);
      thisPtr->_runner->getInteractionService()->acceptMouseButtonClickPush(mouseButton, action, Maths::GeoVector<float>(static_cast<float>(x), static_cast<float>(y)));
      });



    glfwSetKeyCallback(_window.get(), [](auto window, auto key, auto scancode, auto action, auto mods) {
      auto thisPtr = reinterpret_cast<WindowingService*>(glfwGetWindowUserPointer(window));
      if (thisPtr == nullptr) throw std::runtime_error("Unable to continue! WindowUserPointer is NULL. Did you modify this pointer?");

      thisPtr->_runner->getInteractionService()->acceptKeyboardInputBindingPush(key, action);
      });


  }
  void WindowingService::tearDown() {
    if (_isTornDown) return;

    _isTornDown = true;

    glfwDestroyWindow(getWindow());
  }
}
