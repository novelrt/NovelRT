// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_UI_DEARIMGUI_IMGUIBUTTON_H
#define NOVELRT_UI_DEARIMGUI_IMGUIBUTTON_H

#ifndef NOVELRT_UI_DEARIMGUI_H
#error NovelRT does not support including types explicitly by default. Please include UI::DearImGui.h instead for the UI::DearImGui namespace subset.
#endif

namespace NovelRT::UI::DearImGui
{
    class ImGuiButton : public IUIButton, public ImGuiCommon
    {
    public:
        ImGuiButton() noexcept;

        ImGuiButton(const std::string& identifier,
                    NovelRT::Maths::GeoVector2F position,
                    NovelRT::Maths::GeoVector2F scale,
                    NovelRT::Graphics::RGBAColour backgroundColour,
                    NovelRT::Maths::GeoVector2F screenSize) noexcept;

        virtual void Render(std::shared_ptr<IUIProvider> provider, NovelRT::Maths::GeoVector2F windowSize) final;
    };
}

#endif