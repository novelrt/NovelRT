// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_RESOURCEMANAGEMENT_DESKTOP_IMAGEDATA_H
#define NOVELRT_RESOURCEMANAGEMENT_DESKTOP_IMAGEDATA_H

#ifndef NOVELRT_RESOURCEMANAGEMENT_DESKTOP_H
#error NovelRT does not support including types explicitly by default. Please include ResourceManagement.Desktop.h instead for the ResourceManagement::Desktop namespace subset.
#endif

namespace NovelRT::ResourceManagement::Desktop
{
    struct ImageData
    {
        uint32_t width;
        uint32_t height;
        png_byte colourType;
        png_byte bitDepth;
        png_bytep* rowPointers = nullptr; // just following the example here
    };
}

#endif // !NOVELRT_RESOURCEMANAGEMENT_DESKTOP_IMAGEDATA_H
