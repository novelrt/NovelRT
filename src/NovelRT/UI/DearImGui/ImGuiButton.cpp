// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/UI/DearImGui/UI.DearImGui.h>

namespace NovelRT::UI::DearImGui
{
    ImGuiButton::ImGuiButton() noexcept : ImGuiButton("", NovelRT::Maths::GeoVector2F::Zero(), NovelRT::Maths::GeoVector2F::One(), NovelRT::Graphics::RGBAColour(0,0,0,255), NovelRT::Maths::GeoVector2F::Zero()){}

    ImGuiButton::ImGuiButton(const std::string& identifier, NovelRT::Maths::GeoVector2F position, NovelRT::Maths::GeoVector2F scale, NovelRT::Graphics::RGBAColour backgroundColour, NovelRT::Maths::GeoVector2F screenSize) noexcept : IUIButton(identifier, UIElementState::Hidden, position, scale, backgroundColour), ImGuiCommon(screenSize, position + (screenSize / 2)){}

    void ImGuiButton::Render(std::shared_ptr<IUIProvider> provider, NovelRT::Maths::GeoVector2F windowSize)
    {
        if (_state != UIElementState::Shown)
        {
            return;
        }
        if (windowSize != _screenSize)
        {
            _screenSize = windowSize;
            _translatedPosition = _position + (windowSize / 2);
        }

        ImGui::PushStyleColor(ImGuiCol_WindowBg, _backgroundColour);
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(100, 100));
        ImGui::Begin(_identifier.c_str(), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
        ImGui::SetWindowPos(_translatedPosition);
        ImGui::SetWindowSize(_scale);

        ImGui::Button(_identifier.c_str());

        ImGui::End();
        ImGui::PopStyleVar();
        ImGui::PopStyleColor();
    }
}