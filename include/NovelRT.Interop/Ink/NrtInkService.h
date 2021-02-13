// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_INK_INKSERVICE_H
#define NOVELRT_INTEROP_INK_INKSERVICE_H

#include "../DotNet/NrtRuntimeTypedefs.h"
#include "../NrtInteropUtils.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_InkService_initialise(NrtInkService service);
    NrtResult Nrt_InkService_tearDown(NrtInkService service);

    NrtResult Nrt_InkService_createStory(NrtInkService service, const char* jsonString, NrtStory* outputStory);
    NrtResult Nrt_InkService_getRuntimeService(NrtInkService service, NrtRuntimeService* outputRuntimeService);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_INK_INKSERVICE_H
