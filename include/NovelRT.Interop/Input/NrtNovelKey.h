// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#ifndef NOVELRT_INTEROP_INPUT_NRTNOVELKEY_H
#define NOVELRT_INTEROP_INPUT_NRTNOVELKEY_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtNovelKeyInfo Nrt_NovelKey_ReadAsInfo(NrtNovelKeyHandle key);

    const char* Nrt_NovelKey_GetKeyName(NrtNovelKeyHandle key);
    int32_t Nrt_NovelKey_GetExternalKeyCode(NrtNovelKeyHandle key);
    int32_t Nrt_NovelKey_GetExternalModifierCode(NrtNovelKeyHandle key);

    NrtResult Nrt_NovelKey_PairKey(NrtNovelKeyHandle key, int32_t externalKeyCode);
    NrtResult Nrt_NovelKey_UnpairKey(NrtNovelKeyHandle key);

    NrtBool Nrt_NovelKey_equal(NrtNovelKeyHandle lhs, NrtNovelKeyHandle rhs);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_INPUT_NRTNOVELKEY_H
