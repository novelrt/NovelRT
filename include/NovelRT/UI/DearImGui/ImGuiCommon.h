// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef  NOVELRT_UI_DEARIMGUI_IMGUICOMMON_H
#define  NOVELRT_UI_DEARIMGUI_IMGUICOMMON_H

#ifndef NOVELRT_UI_DEARIMGUI_H
#error NovelRT does not support including types explicitly by default. Please include UI::DearImGui.h instead for the NovelRT::UI::DearImGui subset.
#endif

namespace NovelRT::UI::DearImGui
{
    class ImGuiCommon
    {
    protected:
        NovelRT::Maths::GeoVector2F _screenSize;
        NovelRT::Maths::GeoVector2F _translatedPosition;

    public:
        ImGuiCommon(NovelRT::Maths::GeoVector2F screenSize, NovelRT::Maths::GeoVector2F translatedPosition) noexcept : _screenSize(screenSize), _translatedPosition(translatedPosition){}

        virtual void Render(std::shared_ptr<IUIProvider> provider, NovelRT::Maths::GeoVector2F windowSize) = 0;
    };
}

#endif