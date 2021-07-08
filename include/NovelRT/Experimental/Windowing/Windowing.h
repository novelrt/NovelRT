// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_WINDOWING_H
#define NOVELRT_EXPERIMENTAL_WINDOWING_H

/**
 * @Brief The experimental windowing plugin API.
 */
namespace NovelRT::Experimental::Windowing
{
    class IWindowingDevice;
}

// Windowing dependencies
#include "../Graphics/Graphics.h"
#include "../../Maths/GeoVector2F.h"
#include "../../Windowing/WindowMode.h"

// Windowing types
#include "IWindowingDevice.h"

#endif // NOVELRT_EXPERIMENTAL_WINDOWING_H
