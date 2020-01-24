// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_NOVELWINDOWINGSERVICE_H
#define NOVELRT_NOVELWINDOWINGSERVICE_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Windowing {
  class WindowingService {

  NOVELRT_EVENT(WindowResized, Maths::GeoVector<float>)
  NOVELRT_PARAMETERLESS_EVENT(WindowClosed)

  private:
    Maths::GeoVector<float> _windowSize;
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> _window;
    LoggingService _logger;
    NovelRunner* _runner;

  public:
    explicit WindowingService(NovelRunner* const runner);
    void initialiseWindow(int displayNumber, const std::string& windowTitle);
    void tearDown();

    inline SDL_Window* getWindow() const {
      return _window.get();
    }

    inline std::string getWindowTitle() const {
      return SDL_GetWindowTitle(getWindow());
    }

    inline void setWindowTitle(const std::string& value) {
      return SDL_SetWindowTitle(getWindow(), value.c_str());
    }

    inline void setWindowSize(const Maths::GeoVector<float>& value) {
      _windowSize = value;
      SDL_SetWindowSize(getWindow(), value.getX(), value.getY());
      raiseWindowResized(_windowSize);
    }

    inline Maths::GeoVector<float> getWindowSize() const {
      return _windowSize;
    }
  };
}

#endif // !NOVELRT_NOVELWINDOWSERVICE_H
