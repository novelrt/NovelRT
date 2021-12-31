// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_INPUT_GLFW_H
#define NOVELRT_EXPERIMENTAL_INPUT_GLFW_H

/**
 * @Brief The default GLFW3 implementation of the Input plugin API.
 */
namespace NovelRT::Experimental::Input::Glfw
{
    class GlfwInputService;
}

// Input.Glfw dependencies
#include "../../../PluginManagement/PluginManagement.h"
#include "../Input.h"
#include "../../../Timing/StepTimer.h"
#include <cstdint>
#include <GLFW/glfw3.h>

// Input.Glfw types
#include "GlfwInputService.h"
#include "GlfwInputPluginProvider.h"

#endif // NOVELRT_EXPERIMENTAL_INPUT_GLFW_H
