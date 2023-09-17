#ifndef NOVELRT_SDL_WINDOWING_DEVICE_H
#define NOVELRT_SDL_WINDOWING_DEVICE_H

#ifndef NOVELRT_WINDOWING_SDL_H
#error NovelRT does not support including types explicitly by default. Please include Windowing.SDL.h instead for the Windowing::SDl2 namespace subset.
#endif

namespace NovelRT::Windowing::SDL
{
    class SDLWindowingDevice final : public IWindowingDevice
    {

    private:
        std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> _window;
        std::string _currentTitle;

    public:
        SDLWindowingDevice() noexcept;


        [[nodiscard]] Maths::GeoVector2F GetSize() const noexcept final;
        [[nodiscard]] void* GetHandle() const noexcept final;
        [[nodiscard]] void* GetContextHandle() const noexcept final;
        [[nodiscard]] Graphics::GraphicsSurfaceKind GetKind() const noexcept final;

        [[nodiscard]] inline SDL_Window* GetRawSDLWindowHandle() const noexcept
        {
            return _window.get();
        }

        void Initialise(NovelRT::Windowing::WindowMode windowMode, Maths::GeoVector2F desiredWindowSize) final;
        void TearDown() noexcept final;

        [[nodiscard]] inline bool GetIsVisible() const noexcept final
        {
            return SDL_GetWindowFlags(GetRawSDLWindowHandle()) != SDL_WINDOW_HIDDEN;
        }

        [[nodiscard]] inline bool GetShouldClose() const noexcept final;


        [[nodiscard]] inline std::string GetWindowTitle() const noexcept final
        {
            return _currentTitle;
        }

        inline void SetWindowTitle(const std::string& newTitle) final
        {
            _currentTitle = newTitle;
            SDL_SetWindowTitle(_window.get(), _currentTitle.c_str());
        }

        void ProcessAllMessages() final;
        ~SDLWindowingDevice() final;
    };
}


#endif
