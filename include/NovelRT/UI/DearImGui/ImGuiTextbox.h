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
    private:
        NovelRT::Maths::GeoVector2F _screenSize;
        NovelRT::Maths::GeoVector2F _translatedPosition;

    public:
        ImGuiTextbox() noexcept;
        ImGuiTextbox(const std::string& identifier, const std::string& text,
            bool wordWrap, NovelRT::Maths::GeoVector2F position,
            NovelRT::Maths::GeoVector2F scale, float fontSize,
            NovelRT::Maths::GeoVector2F screenSize) noexcept;
        void Render(std::shared_ptr<IUIProvider> provider, NovelRT::Maths::GeoVector2F windowSize);
    };
}

#endif // NOVELRT_UI_DEARIMGUI_IMGUITEXTBOX_H
