#include "NovelRT/Windowing/SDL/Windowing.SDL.h"

namespace NovelRT::Windowing::SDL
{
    SDLWindowingPluginProvider::SDLWindowingPluginProvider() noexcept
    {
    }

    SDLWindowingDevice* SDLWindowingPluginProvider::GetWindowingDeviceInternal()
    {
        return _windowingDevice.get();
    }

}
