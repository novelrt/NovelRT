// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_GRAPHICS_IMAGEDATA_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Graphics {
  struct ImageData {
    int32_t width;
    int32_t height;
    png_byte colourType;
    png_byte bitDepth;
    png_bytep* rowPointers = nullptr; //just following the example here
  };
}

#endif // !NOVELRT_GRAPHICS_IMAGEDATA_H
