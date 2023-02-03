// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_UI_DEARIMGUI_GLFWVULKAN_H
#define NOVELRT_UI_DEARIMGUI_GLFWVULKAN_H

/**
 * @Brief The default GLFW3 + Vulkan implementation of the UI plugin API.
 */
namespace NovelRT::UI::DearImGui::GlfwVulkan
{
    class GlfwVulkanUIProvider;
    class GlfwVulkanUIPluginProvider;
}

// UI.GlfwVulkan dependencies
#include "../../../Graphics/Graphics.h"
#include "../../../Graphics/Vulkan/Graphics.Vulkan.h"
#include "../../../Windowing/Glfw/Windowing.Glfw.h"
#include "../../../Input/Glfw/Input.Glfw.h"
#include "../../../PluginManagement/PluginManagement.h"
#include "../UI.DearImGui.h"
#include <imgui_impl_glfw.h>
#include <imgui_impl_vulkan.h>

// UI::DearImGui.GlfwVulkan types
#include "GlfwVulkanUIProvider.h"
#include "GlfwVulkanUIPluginProvider.h"

#endif // NOVELRT_UI_DEARIMGUI_GLFWVULKAN_H
