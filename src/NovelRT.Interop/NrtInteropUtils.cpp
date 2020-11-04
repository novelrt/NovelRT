// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "NovelRT.Interop/NrtInteropUtils.h"
#include "NrtInteropErrorHandlingInternal.h"

#ifdef __cplusplus
extern "C" {
#endif

const char* Nrt_getLastError() {
  return Nrt_getLastErrorInternal();
}

#ifdef __cplusplus
}
#endif