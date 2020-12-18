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
    struct MouseClickEventArgs {
      int button = 0;
      int action = 0;
      Maths::GeoVector2<float> mousePosition = Maths::GeoVector2<float>::zero();
    };

    struct KeyboardButtonChangeEventArgs {
      int key = 0;
      int action = 0;
    };


    Utilities::Event<Maths::GeoVector2<float>> WindowResized;
    Utilities::Event<> WindowTornDown;
    Utilities::Event<MouseClickEventArgs> MouseButtonClicked;
    Utilities::Event<KeyboardButtonChangeEventArgs> KeyboardButtonChanged;

  private:   
    Maths::GeoVector2<float> _windowSize;
    std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> _window;
    LoggingService _logger;
    std::string _windowTitle;
    bool _isTornDown;

#if defined(_WIN32) || defined(_WIN64)
    HMODULE _optimus;
    void checkForOptimus(const char* library);
#endif

    void errorCallback(int, const char* error);

  public:
    explicit WindowingService() noexcept;

    void initialiseWindow(int displayNumber, const std::string& windowTitle, bool transparencyEnabled, WindowMode initialWindowMode);
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
