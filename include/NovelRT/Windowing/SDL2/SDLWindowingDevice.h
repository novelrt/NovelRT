#ifndef NOVELRT_SDL2_WINDOWING_DEVICE_H
#define NOVELRT_SDL2_WINDOWING_DEVICE_H

#ifndef NOVELRT_WINDOWING_SDL2_H
#error NovelRT does not support including types explicitly by default. Please include Windowing.SDL2.h instead for the Windowing::SDl2 namespace subset.
#endif

namespace NovelRT::Windowing::SDL2
{
    class SDLWindowingDevice : public IWindowingDevice
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

        [[nodiscard]] inline SDL_Window*  




    };
}


#endif
