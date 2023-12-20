#include "NovelRT/Windowing/SDL/Windowing.SDL.h"

namespace NovelRT::Windowing::SDL
{

    SDLWindowingDevice::SDLWindowingDevice() noexcept : _window(nullptr, nullptr)
    {
    }


    //TODO: fix SDL2 in CMake to continue implementation
    void SDLWindowingDevice::Initialise(NovelRT::Windowing::WindowMode windowMode,
        Maths::GeoVector2F desiredWindowSize)
    {
    }

    void SDLWindowingDevice::TearDown() noexcept
    {
    }


    SDLWindowingDevice::~SDLWindowingDevice()
    {
        TearDown();
    }



    Maths::GeoVector2F SDLWindowingDevice::GetSize() const noexcept
    {
        int32_t width = 0;
        int32_t height = 0;
    }

}
