#include "NovelRT/Windowing/SDL/Windowing.SDL.h"

//not sure if im going to need this as i saw no reference of it in glfw
// but, just in case, it is possible to use VK as a renderer directly it seems.
// right now im only drawing to it with fillrect..
//review https://github.com/AndreVallestero/sdl-vulkan-tutorial

namespace NovelRT::Windowing::SDL
{
    SDLWindowingDevice::SDLWindowingDevice() noexcept : _window(nullptr, nullptr)
    {

    }

    SDL_Window* window = NULL; //here for scope
    SDL_Surface* monitor = NULL;
    bool quit; //will determine whether the window should be closed or not


    void SDLWindowingDevice::Initialise(NovelRT::Windowing::WindowMode windowMode,
        Maths::GeoVector2F desiredWindowSize)
    {

        window = SDL_CreateWindow("SDLWnd", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, static_cast<int32_t>(desiredWindowSize.x),
                                  static_cast<int32_t>(desiredWindowSize.y), SDL_WINDOW_SHOWN);


        //set window mode
        switch (windowMode)
        {
            case NovelRT::Windowing::WindowMode::Windowed:
                SDL_SetWindowFullscreen(window, 0);
                break;
            case NovelRT::Windowing::WindowMode::Borderless:
                SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
                break;
            case NovelRT::Windowing::WindowMode::Fullscreen:
                SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
                break;

        }



        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            throw Exceptions::InitialisationFailureException("SDL2 failed to initialize! ", SDL_GetError());
        }
        else
        {

            if (window == NULL)
            {
                throw Exceptions::InitialisationFailureException("SDL2 Window could not be created! ", SDL_GetError());
            }
            monitor = SDL_GetWindowSurface(window);
            SDL_FillRect(monitor, NULL, SDL_MapRGB(monitor->format, 0, 0, 0));
            SDL_UpdateWindowSurface(window);
            

            while (quit == false)
            {
                ProcessAllMessages();
            }

        }



    }

    bool SDLWindowShouldClose()
    {
        return quit;
    }

    void SDLWindowingDevice::ProcessAllMessages()
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                quit = true;
        }
    }

    Maths::GeoVector2F SDLWindowingDevice::GetSize() const noexcept
    {
        int32_t width = 0;
        int32_t height = 0;

        SDL_GetWindowSize(window, &width, &height);

        if (width == 0 || height == 0)
        {
            return Maths::GeoVector2F::Zero();
        }

        return Maths::GeoVector2F(static_cast<float>(width), static_cast<float>(height));

    }

    void* SDLWindowingDevice::GetHandle() const noexcept
    {
        return nullptr;
    }

    Graphics::GraphicsSurfaceKind SDLWindowingDevice::GetKind() const noexcept
    {
        return Graphics::GraphicsSurfaceKind::Unknown;
    }

    void SDLWindowingDevice::TearDown() noexcept
    {
        _window.reset();
    }

    //destructor
    SDLWindowingDevice::~SDLWindowingDevice()
    {
        TearDown();
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
}
