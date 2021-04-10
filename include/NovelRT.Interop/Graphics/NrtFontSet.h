// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_GRAPHICS_FONTSET_H
#define NOVELRT_INTEROP_GRAPHICS_FONTSET_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_FontSet_loadFontAsTextureSet(NrtFontSetHandle fontSet, const char* file, float fontSize);
    NrtResult Nrt_FontSet_getFontFile(NrtFontSetHandle fontSet, const char** outputFontFile);
    NrtResult Nrt_FontSet_getFontSize(NrtFontSetHandle fontSet, float* outputFontSize);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_GRAPHICS_FONTSET_H
