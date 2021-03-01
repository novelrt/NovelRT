// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_NOVELWINDOWINGSERVICE_H
#define NOVELRT_NOVELWINDOWINGSERVICE_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Windowing
{
    /**
     * @brief Manages the game window and window events such as resizing.
     */
    class WindowingService : public std::enable_shared_from_this<WindowingService>
    {

    public:
        struct MouseClickEventArgs
        {
            int32_t button = 0;
            int32_t action = 0;
            Maths::GeoVector2F mousePosition = Maths::GeoVector2F::zero();
        };

        struct KeyboardButtonChangeEventArgs
        {
            int32_t key = 0;
            int32_t action = 0;
        };

        Utilities::Event<Maths::GeoVector2F> WindowResized;
        Utilities::Event<> WindowTornDown;
        Utilities::Event<MouseClickEventArgs> MouseButtonClicked;
        Utilities::Event<KeyboardButtonChangeEventArgs> KeyboardButtonChanged;

    private:
        Maths::GeoVector2F _windowSize;
        std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> _window;
        LoggingService _logger;
        std::string _windowTitle;
        bool _isTornDown;

#if defined(_WIN32) || defined(_WIN64)
        HMODULE _optimus;
        void checkForOptimus(const char* library);
#endif

        void errorCallback(int32_t, const char* error);

    public:
        explicit WindowingService() noexcept;

        void initialiseWindow(int32_t displayNumber,
                              const std::string& windowTitle,
                              NovelRT::Windowing::WindowMode initialWindowMode,
                              bool transparencyEnabled);
        void tearDown();

        inline GLFWwindow* getWindow() const
        {
            return _window.get();
        }

        inline std::string getWindowTitle() const
        {
            return _windowTitle;
        }

        inline void setWindowTitle(const std::string& value)
        {
            _windowTitle = value;
            return glfwSetWindowTitle(getWindow(), _windowTitle.c_str());
        }

        inline void setWindowSize(Maths::GeoVector2F value)
        {
            _windowSize = value;
            glfwSetWindowSize(getWindow(), static_cast<int32_t>(value.x), static_cast<int32_t>(value.y));
            WindowResized(_windowSize);
        }

        inline Maths::GeoVector2F getWindowSize() const
        {
            return _windowSize;
        }
    };
} // namespace NovelRT::Windowing

#endif // !NOVELRT_NOVELWINDOWSERVICE_H
