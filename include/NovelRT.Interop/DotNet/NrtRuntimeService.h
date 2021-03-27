// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_DOTNET_RUNTIMESERVICE_H
#define NOVELRT_INTEROP_DOTNET_RUNTIMESERVICE_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtRuntimeServiceHandle Nrt_RuntimeService_create();
    NrtResult Nrt_RuntimeService_destroy(NrtRuntimeServiceHandle service);

    NrtResult Nrt_RuntimeService_initialise(NrtRuntimeServiceHandle service);
    NrtResult Nrt_RuntimeService_tearDown(NrtRuntimeServiceHandle service);

    NrtResult Nrt_RuntimeService_freeObject(NrtRuntimeServiceHandle service, intptr_t obj);
    NrtResult Nrt_RuntimeService_freeString(NrtRuntimeServiceHandle service, const char* str);

    NrtResult Nrt_RuntimeService_getInkService(NrtRuntimeServiceHandle service, NrtInkServiceHandle* outputInkService);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_DOTNET_RUNTIMESERVICE_H
