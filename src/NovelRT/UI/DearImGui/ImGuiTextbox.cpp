// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/UI/DearImGui/UI.DearImGui.h>

namespace NovelRT::UI::DearImGui
{
    ImGuiTextbox::ImGuiTextbox() noexcept
    {
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
        bool wordWrap, NovelRT::Maths::GeoVector2F position, NovelRT::Maths::GeoVector2F scale) noexcept
    {
        _position = position;
        _scale = scale;
        _identifier = id;
        _wordWrap = wordWrap;
        _text = text;
        _fontSize = 18.0f;
        _state = UIElementState::Hidden;
        _backgroundColour = NovelRT::Graphics::RGBAColour(0,0,0,255);
    }

    void ImGuiTextbox::Render(std::shared_ptr<IUIProvider> provider)
    {
        if(_state == UIElementState::Shown)
        {
            ImGui::PushStyleColor(ImGuiCol_WindowBg, _backgroundColour);
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(100, 100));
            ImGui::Begin(_identifier.c_str(), NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
            ImGui::SetWindowPos(ImVec2(_position.x, _position.y));
            ImGui::SetWindowSize(ImVec2(_scale.x, _scale.y));
            auto fontSize = ImGui::GetFontSize();
            if(fontSize != _fontSize)
            {
                ImGui::SetWindowFontScale(_fontSize / fontSize);
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

