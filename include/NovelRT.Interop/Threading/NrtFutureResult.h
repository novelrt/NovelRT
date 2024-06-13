// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_THREADING_FUTURERESULT_H
#define NOVELRT_INTEROP_THREADING_FUTURERESULT_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    // FutureResult<TextureInfo>
    NrtResult Nrt_FutureResultOfTextureInfo_Destroy(NrtFutureResultOfTextureInfoHandle handle);

    NrtBool Nrt_FutureResultOfTextureInfo_TryGetValue(NrtFutureResultOfTextureInfoHandle handle,
                                                      NrtTextureInfoHandle* outValue);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_THREADING_FUTURERESULT_H
