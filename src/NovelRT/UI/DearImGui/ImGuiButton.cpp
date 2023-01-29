// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/UI/DearImGui/UI.DearImGui.h>

namespace NovelRT::UI::DearImGui
{
    ImGuiButton::ImGuiButton() noexcept : ImGuiButton("", UIElementState::Hidden, NovelRT::Maths::GeoVector2F::Zero(), NovelRT::Maths::GeoVector2F::One(), NovelRT::Graphics::RGBAColour(0,0,0,255), NovelRT::Maths::GeoVector2F::Zero()){}

    ImGuiButton::ImGuiButton(const std::string& identifier, UIElementState state, NovelRT::Maths::GeoVector2F position, NovelRT::Maths::GeoVector2F scale, NovelRT::Graphics::RGBAColour backgroundColour, NovelRT::Maths::GeoVector2F screenSize) noexcept : IUIButton(identifier, state, position, scale, backgroundColour), ImGuiCommon(screenSize, position + (screenSize / 2)){}

    void ImGuiButton::Render(std::shared_ptr<IUIProvider> provider, NovelRT::Maths::GeoVector2F windowSize)
    {
        unused(provider);
        unused(windowSize);
        if (_state != UIElementState::Shown)
        {
            return;
        }


    }
}