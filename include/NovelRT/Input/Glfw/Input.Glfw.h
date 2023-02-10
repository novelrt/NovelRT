// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INPUT_GLFW_H
#define NOVELRT_INPUT_GLFW_H

/**
 * @brief The default GLFW3 implementation of the Input plugin API.
 */
namespace NovelRT::Input::Glfw
{
    class GlfwInputDevice;
}

// Input.Glfw dependencies
#define GLFW_INCLUDE_NONE
#include "NovelRT/Input/Input.h"
#include "NovelRT/PluginManagement/PluginManagement.h"
#include <GLFW/glfw3.h>
#include <cstdint>

// Input.Glfw types
#include "GlfwInputDevice.h"
#include "GlfwInputPluginProvider.h"

#endif // NOVELRT_INPUT_GLFW_H
