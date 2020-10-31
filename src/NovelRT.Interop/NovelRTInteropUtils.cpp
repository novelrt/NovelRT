// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "NovelRT.Interop/NovelRTInteropUtils.h"
#include "NovelRTInteropErrorHandlingInternal.h"

#ifdef __cplusplus
extern "C" {
#endif

const char* NovelRT_getLastError() {
  return NovelRT_getLastErrorInternal();
}

#ifdef __cplusplus
}
#endif