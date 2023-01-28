// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/UI/DearImGui/UI.DearImGui.h>

namespace NovelRT::UI::DearImGui
{
    ImGuiTextbox::ImGuiTextbox() noexcept : ImGuiTextbox("", "", false, NovelRT::Maths::GeoVector2F::Zero(), NovelRT::Maths::GeoVector2F::One(), 18.0f, NovelRT::Maths::GeoVector2F::Zero())
    {
    }

    ImGuiTextbox::ImGuiTextbox(const std::string& identifier, const std::string& text,
        bool wordWrap, NovelRT::Maths::GeoVector2F position, NovelRT::Maths::GeoVector2F scale, float fontSize,
        NovelRT::Maths::GeoVector2F screenSize) noexcept :
        IUITextbox(identifier, UIElementState::Hidden, position, scale, wordWrap, text, fontSize, NovelRT::Graphics::RGBAColour(0,0,0,255)),
        _screenSize(screenSize),
        _translatedPosition(position + (screenSize / 2))
    {}
    

    void ImGuiTextbox::Render(std::shared_ptr<IUIProvider> provider, NovelRT::Maths::GeoVector2F screenSize)
    {
        if(_state == UIElementState::Shown)
        {
            if (screenSize != _screenSize)
            {
                _screenSize = screenSize;
                _translatedPosition = _position + (screenSize / 2);
            }
            //auto imguiFontSize = ImGui::GetFontSize();

            ImGui::PushStyleColor(ImGuiCol_WindowBg, _backgroundColour);
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(100, 100));
            ImGui::Begin(_identifier.c_str(), NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
            ImGui::SetWindowPos(_translatedPosition);
            ImGui::SetWindowSize(_scale);
            if(_fontSize != 36.0f)
            {
                ImGui::SetWindowFontScale(_fontSize / 36.0f);
            }

            if(_wordWrap)
            {
                ImGui::TextWrapped(_text.c_str());
            }
            else
            {
                ImGui::Text(_text.c_str());
            }
            

            ImGui::End();
            ImGui::PopStyleVar();
            ImGui::PopStyleColor();
        }
    }

}

