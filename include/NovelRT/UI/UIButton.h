// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_UI_UIBUTTON_H
#define NOVELRT_UI_UIBUTTON_H

#ifndef NOVELRT_UI_H
#error NovelRT does not support including types explicitly by default. Please include UI.h instead for the Windowing namespace subset.
#endif

namespace NovelRT::UI
{
    struct UIButton
    {
    public:
        const char* Identifer;
        const char* Text;
        UIElementState State = NovelRT::UI::UIElementState::Hidden;
        UIElementType Type = NovelRT::UI::UIElementType::Panel;
        NovelRT::Maths::GeoVector2F Position;
        NovelRT::Maths::GeoVector2F Scale;
        NovelRT::Graphics::RGBAColour HoveredColour;
        NovelRT::Graphics::RGBAColour ActiveColour;
        NovelRT::Graphics::RGBAColour TextColour;
        size_t FontIndex;
    };
}

#endif // NOVELRT_UI_UIBUTTON_H
