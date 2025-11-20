#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <png.h>
#include <cstdint>

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
