// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_INK_INKSERVICE_H
#define NOVELRT_INTEROP_INK_INKSERVICE_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_InkService_initialise(NrtInkServiceHandle service);
    NrtResult Nrt_InkService_tearDown(NrtInkServiceHandle service);

    NrtResult Nrt_InkService_createStory(NrtInkServiceHandle service, const char* jsonString, NrtStoryHandle* outputStory);
    NrtResult Nrt_InkService_getRuntimeService(NrtInkServiceHandle service, NrtRuntimeServiceHandle* outputRuntimeService);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_INK_INKSERVICE_H
