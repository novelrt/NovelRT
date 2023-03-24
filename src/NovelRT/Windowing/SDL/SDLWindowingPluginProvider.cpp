#include "NovelRT/Windowing/SDL/Windowing.SDL.h"

namespace NovelRT::Windowing::SDL
{
    SDLWindowingPluginProvider::SDLWindowingPluginProvider() noexcept
        : _windowingDevice(std::make_shared<SDLWindowingDevice>())
    {
    }

    SDLWindowingDevice* SDLWindowingPluginProvider::GetWindowingDeviceInternal()
    {
        return _windowingDevice.get();
    }
}
