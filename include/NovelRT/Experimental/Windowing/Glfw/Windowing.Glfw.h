// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_WINDOWING_GLFW_H
#define NOVELRT_EXPERIMENTAL_WINDOWING_GLFW_H

/**
 * @Brief The default GLFW3 implementation of the Windowing plugin API.
 */
namespace NovelRT::Experimental::Windowing::Glfw
{
    class GlfwWindowingDevice;
}

// Windowing.Glfw dependencies
#include "../../../Maths/GeoVector2F.h"
#include "../Windowing.h"
#include <cstdint>

// TODO: Figure out if this is required
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <memory>

// Windowing.Glfw types
#include "GlfwWindowingDevice.h"

#endif // NOVELRT_EXPERIMENTAL_WINDOWING_GLFW_H
