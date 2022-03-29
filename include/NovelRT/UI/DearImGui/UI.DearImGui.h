// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_UI_DEARIMGUI_H
#define NOVELRT_UI_DEARIMGUI_H

// UI.ImGui dependencies
#include "../../LoggingService.h"
#include "../../PluginManagement/PluginManagement.h"
#include "../UI.h"
#include <imgui.h>

/**
 * @brief The default ImGui implementation for the UI plugin API.
 */
namespace NovelRT::UI::DearImGui
{
    class ImGuiUIProvider;
    class ImGuiUIPluginProvider;
}

// UI.ImGui types

// clang-format off

#include "ImGuiUIProvider.h"
#include "ImGuiUIPluginProvider.h"

// clang-format on

#endif // NOVELRT_UI_IMGUI_H
