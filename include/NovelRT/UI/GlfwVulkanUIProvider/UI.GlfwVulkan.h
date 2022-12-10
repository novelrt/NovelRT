// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_UI_GLFWVULKAN_H
#define NOVELRT_UI_GLFWVULKAN_H

/**
 * @Brief The default GLFW3 + Vulkan implementation of the UI plugin API.
 */
namespace NovelRT::UI::GlfwVulkan
{
    class GlfwVulkanUIProvider;
    class GlfwVulkanUIPluginProvider;
}

// UI.GlfwVulkan dependencies
#include "NovelRT/Graphics/Graphics.h"
#include "NovelRT/Graphics/Vulkan/Graphics.Vulkan.h"
#include "NovelRT/Windowing/Glfw/Windowing.Glfw.h"
#include "NovelRT/PluginManagement/PluginManagement.h"
#include <imgui_impl_glfw.h>
#include <imgui_impl_vulkan.h>

// UI.GlfwVulkan types
#include "GlfwVulkanUIProvider.h"
#include "GlfwVulkanUIPluginProvider.h"

#endif // NOVELRT_UI_GLFWVULKAN_H
