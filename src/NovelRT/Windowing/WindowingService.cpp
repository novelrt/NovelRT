// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

namespace NovelRT::Windowing {
  WindowingService::WindowingService(NovelRunner* const runner) :
    _window(std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)>(nullptr, glfwDestroyWindow)),
    _logger(LoggingService(Utilities::Misc::CONSOLE_LOG_WINDOWING)),
    _runner(runner) {
    runner->getInteractionService()->subscribeToResizeInputDetected([this](auto value) {
      _windowSize = value;
      _logger.logInfo("New size detected! Notifying GFX and other members...");
      raiseWindowResized(_windowSize); });
  }

  void WindowingService::errorCallback(int, const char* error) {
    _logger.logError("Could not initialize GLFW: ", error);
  }

  void WindowingService::initialiseWindow(int displayNumber, const std::string& windowTitle) {
    if(!glfwInit()) {
      const char* err = "";
      glfwGetError(&err);
      _logger.logError("GLFW ERROR: ", err);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_FALSE);

    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* displayData = glfwGetVideoMode(primaryMonitor);

    // create window
    float wData = displayData.w * 0.7f;
    float hData = displayData.h * 0.7f;
    auto window = glfwCreateWindow(wData,hData, _windowTitle.c_str(), NULL, NULL);
    glfwSetWindowAttrib(window, GLFW_RESIZABLE, GLFW_TRUE);
    glfwSetWindowAttrib(window, GLFW_VISIBLE, GLFW_TRUE);

    _window = std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)>(window, glfwDestroyWindow);
    _windowSize = Maths::GeoVector<float>(wData, hData);

    if (_window == nullptr) {
      throw std::runtime_error("Unable to continue! Window could not be created.");
    }
  }
  void WindowingService::tearDown() {
    raiseWindowClosed();
    glfwDestroyWindow(getWindow());
    glfwTerminate()
  }
}
