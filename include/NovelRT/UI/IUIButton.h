
// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_UI_IUIBUTTON_H
#define NOVELRT_UI_IUIBUTTON_H

#ifndef NOVELRT_UI_H
#error NovelRT does not support including types explicitly by default. Please include UI.h instead for the Windowing namespace subset.
#endif

namespace NovelRT::UI
{
    class IUIButton : public IUIElement
    {
    protected:
        NovelRT::Graphics::RGBAColour _backgroundColour;

    public:

        [[nodiscard]] inline NovelRT::Graphics::RGBAColour& BackgroundColour()
        {
            return _backgroundColour;
        }

        [[nodiscard]] inline const NovelRT::Graphics::RGBAColour& BackgroundColour() const
        {
            return _backgroundColour;
        }
    };
}

#endif // NOVELRT_UI_IUIBUTTON_H
