// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/UI/DearImGui/UI.DearImGui.h>

namespace NovelRT::UI::DearImGui
{
    ImGuiTextbox::ImGuiTextbox() noexcept
    {
        _identifier = "";
        _text = "";
        _wordWrap = false;
        _state = UIElementState::Hidden;
    }

    ImGuiTextbox::ImGuiTextbox(std::string id, bool wordWrap, std::string text) noexcept
    {
        _identifier = id;
        _wordWrap = wordWrap;
        _text = text;
        _state = UIElementState::Hidden;
    }

    void ImGuiTextbox::Render()
    {
        if(_state == UIElementState::Shown)
        {

            ImGui::Begin(_identifier.c_str(), NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
            ImGui::PushItemWidth(200.0f);
            if(_wordWrap)
            {
                ImGui::TextWrapped(_text.c_str());
            }
            else
            {
                ImGui::Text(_text.c_str());
            }
            ImGui::PopItemWidth();
            ImGui::End();


        }
    }

}

