// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_UI_UIFONTMETADATA_H
#define NOVELRT_UI_UIFONTMETADATA_H

#ifndef NOVELRT_UI_H
#error NovelRT does not support including types explicitly by default. Please include UI.h instead for the Windowing namespace subset.
#endif

namespace NovelRT::UI
{
    struct UIFontMetadata
    {
    public:
        size_t Index;
        const char* FontName;
        float FontSize;
        bool Bold;
        bool Italicised;
    };
}

#endif // NOVELRT_UI_UIFONTMETADATA_H
