// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/UI/DearImGui/UI.DearImGui.h>

namespace NovelRT::UI::DearImGui
{
    ImGuiTextbox::ImGuiTextbox() noexcept
    {
        _screenSize = NovelRT::Maths::GeoVector2F::Zero();
        _position = NovelRT::Maths::GeoVector2F::Zero();
        _scale = NovelRT::Maths::GeoVector2F::One();
        _identifier = "";
        _text = "";
        _wordWrap = false;
        _fontSize = 18.0f;
        _state = UIElementState::Hidden;
        _backgroundColour = NovelRT::Graphics::RGBAColour(0,0,0,255);
    }

    ImGuiTextbox::ImGuiTextbox(std::string id, std::string text,
        bool wordWrap, NovelRT::Maths::GeoVector2F position, NovelRT::Maths::GeoVector2F scale, float fontSize,
        NovelRT::Maths::GeoVector2F screenSize) noexcept
    {
        _screenSize = screenSize;
        _position = position;
        _translatedPosition = position + (screenSize / 2);
        _scale = scale;
        _identifier = id;
        _wordWrap = wordWrap;
        _text = text;
        _fontSize = fontSize;
        _state = UIElementState::Hidden;
        _backgroundColour = NovelRT::Graphics::RGBAColour(0,0,0,255);
    }

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

