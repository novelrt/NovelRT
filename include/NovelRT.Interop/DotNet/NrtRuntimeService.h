// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_DOTNET_RUNTIMESERVICE_H
#define NOVELRT_INTEROP_DOTNET_RUNTIMESERVICE_H

#include "../NrtInteropUtils.h"
#include "NrtRuntimeTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtRuntimeService Nrt_RuntimeService_create();
    NrtResult Nrt_RuntimeService_destroy(NrtRuntimeService service);

    NrtResult Nrt_RuntimeService_initialise(NrtRuntimeService service);
    NrtResult Nrt_RuntimeService_tearDown(NrtRuntimeService service);

    NrtResult Nrt_RuntimeService_freeObject(NrtRuntimeService service, intptr_t obj);
    NrtResult Nrt_RuntimeService_freeString(NrtRuntimeService service, const char* str);

    NrtResult Nrt_RuntimeService_getInkService(NrtRuntimeService service, NrtInkService* outputInkService);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_DOTNET_RUNTIMESERVICE_H
