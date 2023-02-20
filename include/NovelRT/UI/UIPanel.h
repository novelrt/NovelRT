// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_UI_UIPANEL_H
#define NOVELRT_UI_UIPANEL_H

#ifndef NOVELRT_UI_H
#error NovelRT does not support including types explicitly by default. Please include UI.h instead for the Windowing namespace subset.
#endif

namespace NovelRT::UI
{
    struct UIPanel : public UIElement
    {
    public:
        std::vector<UIElement>* ChildElements = new std::vector<UIElement>();

        UIPanel& operator+=(const UIElement& element)
        {
            ChildElements->emplace_back(element);
            return *this;
        }
    };
}

#endif // NOVELRT_UI_UIPANEL_H
