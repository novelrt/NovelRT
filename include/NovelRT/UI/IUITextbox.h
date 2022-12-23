// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_UI_IUITEXTBOX_H
#define NOVELRT_UI_IUITEXTBOX_H

#ifndef NOVELRT_UI_H
#error NovelRT does not support including types explicitly by default. Please include UI.h instead for the Windowing namespace subset.
#endif

namespace NovelRT::UI
{
    class IUITextbox : public IUIElement
    {
    protected:
        bool _wordWrap;
        std::string _text;
        float _fontSize;
        NovelRT::Graphics::RGBAColour _backgroundColour;

    public:
        [[nodiscard]] inline std::string& Identifier()
        {
            return _identifier;
        }

        [[nodiscard]] inline const std::string& Identifier() const
        {
            return _identifier;
        }

        [[nodiscard]] inline bool& WordWrap()
        {
            return _wordWrap;
        }

        [[nodiscard]] inline const bool& WordWrap() const
        {
            return _wordWrap;
        }

        [[nodiscard]] inline std::string& Text()
        {
            return _text;
        }

        [[nodiscard]] inline const std::string& Text() const
        {
            return _text;
        }

        [[nodiscard]] inline float& FontSize()
        {
            return _fontSize;
        }

        [[nodiscard]] inline const float& FontSize() const
        {
            return _fontSize;
        }

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

#endif // NOVELRT_UI_IUITEXTBOX_H
