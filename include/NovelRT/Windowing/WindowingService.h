// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_NOVELWINDOWINGSERVICE_H
#define NOVELRT_NOVELWINDOWINGSERVICE_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Windowing {
  /**
   * Manages the game window and window events such as resizing.
   */
  class WindowingService {

  public:
    Utilities::Event<Maths::GeoVector2<float>> WindowResized;
    Utilities::Event<> WindowTornDown;

  private:   
    Maths::GeoVector2<float> _windowSize;
    std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> _window;
    LoggingService _logger;
    NovelRunner* const _runner;
    std::string _windowTitle;
    bool _isTornDown;

#if defined(_WIN32) || defined(_WIN64)
    HMODULE _optimus;
    void checkForOptimus(const char* library);
#endif

    void errorCallback(int, const char* error);

  public:
    explicit WindowingService(NovelRunner* const runner);

    void initialiseWindow(int displayNumber, const std::string& windowTitle);
    void tearDown();

    inline GLFWwindow* getWindow() const {
      return _window.get();
    }

    inline std::string getWindowTitle() const {
      return _windowTitle;
    }

    inline void setWindowTitle(const std::string& value) {
      _windowTitle = value;
      return glfwSetWindowTitle(getWindow(), _windowTitle.c_str());
    }

    inline void setWindowSize(const Maths::GeoVector2<float>& value) {
      _windowSize = value;
      glfwSetWindowSize(getWindow(), static_cast<int32_t>(value.getX()), static_cast<int32_t>(value.getY()));
      WindowResized(_windowSize);
    }

    inline Maths::GeoVector2<float> getWindowSize() const {
      return _windowSize;
    }
  };
}

#endif // !NOVELRT_NOVELWINDOWSERVICE_H
