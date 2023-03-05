#ifndef NOVELRT_WINDOWING_SDL_H
#define NOVELRT_WINDOWING_SDL_H

namespace NovelRT::Windowing::SDL
{
    class SDLWindowingDevice;
    class SDLWindowingPluginProvider;
}

#include "NovelRT/PluginManagement/PluginManagement.h"
#include "NovelRT/Windowing/Windowing.h"

#include <SDL2/SDL.h>

#include "SDLWindowingDevice.h"
#include "SDLWindowingPluginProvider.h"

#endif
