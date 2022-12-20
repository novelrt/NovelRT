// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_UI_DEARIMGUI_IMGUITEXTBOX_H
#define NOVELRT_UI_DEARIMGUI_IMGUITEXTBOX_H

#ifndef NOVELRT_UI_DEARIMGUI_H
#error NovelRT does not support including types explicitly by default. Please include UI.DearImgui.h instead for the UI.DearImGui namespace subset.
#endif

namespace NovelRT::UI::DearImGui
{
    class ImGuiTextbox : public UI::IUITextbox
    {

    public:
        ImGuiTextbox() noexcept;
        ImGuiTextbox(std::string id, std::string text, bool wordWrap,
            NovelRT::Maths::GeoVector2F position, NovelRT::Maths::GeoVector2F scale) noexcept;
        void Render(std::shared_ptr<IUIProvider> provider);
    };
}

#endif // NOVELRT_UI_DEARIMGUI_IMGUITEXTBOX_H
