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

    void SDLWindowingDevice::Initialise(NovelRT::Windowing::WindowMode windowMode,
        Maths::GeoVector2F desiredWindowSize)
    {
        SDL_Surface* moniter = NULL;


        window = SDL_CreateWindow("SDLWnd", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, desiredWindowSize.x,
                                   desiredWindowSize.y, SDL_WINDOW_SHOWN);

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
            moniter = SDL_GetWindowSurface(window);
            SDL_FillRect(moniter, NULL, SDL_MapRGB(moniter->format, 0, 0, 0));
            SDL_UpdateWindowSurface(window);

            //hack to keep the window open for now
            SDL_Event e;
            bool quit = false;
            while (quit == false)
            {
                while (SDL_PollEvent(&e))
                {
                    if (e.type == SDL_QUIT)
                        quit = true;
                }
            }

        }



    }

    void SDLWindowShouldClose(SDL_Window * window);

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
