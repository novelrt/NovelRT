#ifndef NOVELRT_WINDOWING_SDL_SDLWINDOWINGDEVICE_H
#define NOVELRT_WINDOWING_SDL_SDLWINDOWINGDEVICE_H

#ifndef NOVELRT_WINDOWING_SDL_H
#error NovelRT does not support including types explicitly by default. Please include Windowing.Sdl.h instead for the Windowing:Sdl namespace subset.
#endif


namespace NovelRT::Windowing::SDL
{
    class SDLWindowingDevice final : public IWindowingDevice
    {
    public:
        struct CursorPositionEventArgs
        {
            double x = 0;
            double y = 0;
        };

        struct ButtonChangeEventArgs
        {
            int32_t key = 0;
            int32_t action = 0;
        };

        Utilities::Event<CursorPositionEventArgs> CurosrMoved;
        Utilities::Event<ButtonChangeEventArgs> MouseButtonClicked;
        Utilities::Event<ButtonChangeEventArgs> KeyboardButtonChanged;

    private:
        std::unique_ptr<SDLWindow, decltype(&SDLDestroyWindow)> _window;
        std::string _currentTitle;

    public:
        SDLWindowingDevice() noexcept;
        [[nodiscard]] Maths::GeoVector2F GetSize() const noexcept final;
        [[nodiscard]] void* GetHandle() const noexcept final; 
        [[nodiscard]] void* GetContextHandle() const noexcept final;
        [[nodiscard]] Graphics::GraphicsSurfaceKind GetKind() const noexcept final;

        [[nodiscard]] inline SDLWindow* GetRawSDLWindowHandle() const noexcept
        {
            return _window.get();
        }
        void Initialise(NovelRT::Windowing::WindowMode windowMode, Maths::GeoVector2F desiredWindowSize) final;
        void TearDown() noexcept final;


        [[nodiscard]] inline bool GetIsVisible() const noexcept final
        {
            return SDL_GetWindowFlags(GetRawSDLWindowHandle()) & SDL_WINDOW_SHOWN;
        }
        //unable to directly check if a window should close via window handle alone like GLFW can.
        //TODO: if the window should close, SDL_PollEvent has quit, when this is created, if event.type == SDL_QUIT it will set this off!
        [[nodiscard]] inline bool GetShouldClose() const noexcept final;
        [[nodiscard]] inline std::string GetWindowTitle() const noexcept final
        {
            return _currentTitle;
        }

        inline void SetWindowTitle(const std::string& newTitle) final
        {
            _currentTitle = newTitle;
        }
        void ProcessAllMessages() final;
        ~SDLWindowingDevice() final;
    };
}


#endif // !NOVELRT_WINDOWING_SDL_SDLWINDOWINGDEVICE_H
