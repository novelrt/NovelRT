// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_UI_DEARIMGUI_H
#define NOVELRT_UI_DEARIMGUI_H

/**
 * @Brief The Dear ImGui implementation of the UI plugin API.
 */
namespace NovelRT::UI::DearImGui
{
    // class ImGuiTextbox;
    // class ImGuiButton;
    // class ImGuiCommon;
}


// UI::DearImGui dependencies
#include "../UI.h"
#define IMGUI_USER_CONFIG "UI.DearImGui.h"
#define IM_VEC2_CLASS_EXTRA                                                     \
        constexpr ImVec2(const NovelRT::Maths::GeoVector2F& f) : x(f.x), y(f.y) {}                   \
        operator NovelRT::Maths::GeoVector2F() const { return NovelRT::Maths::GeoVector2F(x,y); }
#define IM_VEC4_CLASS_EXTRA                                                     \
        constexpr ImVec4(const NovelRT::Graphics::RGBAColour& f) : x(f.r), y(f.g), z(f.b), w(f.a) {}
#include <imgui.h>

// UI::DearImGui includes
// clang-format off

// #include "ImGuiCommon.h"
// #include "ImGuiButton.h"
// #include "ImGuiTextbox.h"

// clang-format on

#endif // NOVELRT_UI_DEARIMGUI_GLFWVULKAN_H
