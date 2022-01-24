// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_WINDOWING_GLFW_H
#define NOVELRT_WINDOWING_GLFW_H

/**
 * @Brief The default GLFW3 implementation of the Windowing plugin API.
 */
namespace NovelRT::Windowing::Glfw
{
    class GlfwWindowingDevice;
    class GlfwWindowingPluginProvider;
}

// Windowing.Glfw dependencies
#include "NovelRT/Maths/Maths.h"
#include "NovelRT/PluginManagement/PluginManagement.h"
#include "NovelRT/Windowing/Windowing.h"
#include <cstdint>

// TODO: Figure out if this is required
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <memory>

// Windowing.Glfw types
#include "GlfwWindowingDevice.h"
#include "GlfwWindowingPluginProvider.h"

#endif // NOVELRT_WINDOWING_GLFW_H
