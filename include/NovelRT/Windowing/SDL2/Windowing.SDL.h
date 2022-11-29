#ifndef NOVELRT_WINDOWING_SDL2_H
#define NOVELRT_WINDOWING_SDL2_H

namespace NovelRT::Windowing::SDL2
{
    class SDLWindowingDevice;
    class SDLWindowingPluginProvider;
}

#include "NovelRT/PluginManagement/PluginManagement.h"
#include "NovelRT/Windowing/Windowing.h"

#include <SDL.h>

#include "SDLWindowingDevice.h"
#include "SDLWindowingPluginProvider.h"

#endif
