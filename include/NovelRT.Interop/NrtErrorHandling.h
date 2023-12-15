// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_ERRORHANDLING_H
#define NOVELRT_INTEROP_ERRORHANDLING_H

#include "NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    const char* Nrt_GetLastError();

    // Internal
    const char* Nrt_GetLastErrorInternal();
    void Nrt_SetErrMsgIsNullInstanceProvidedInternal();
    void Nrt_SetErrMsgIsNullArgumentProvidedInternal();
    void Nrt_SetErrMsgIsNaNInternal();
    void Nrt_SetErrMsgDupKeyGivenInternal();
    void Nrt_SetErrMsgCompilationErrorInternal();
    void Nrt_SetErrMsgIsFileNotFoundInternal();
    void Nrt_SetErrMsgIsDivideByZeroInternal();
    void Nrt_SetErrMsgIsAlreadyDeletedOrRemovedInternal();
    void Nrt_SetErrMsgIsNotSupportedInternal();
    void Nrt_SetErrMsgIsInitialisationFailureInternal();
    void Nrt_SetErrMsgIsFunctionNotFoundInternal();
    void Nrt_SetErrMsgIsNotInitialisedInternal();
    void Nrt_SetErrMsgIsArgumentOutOfRangeInternal();
    void Nrt_SetErrMsgIsInvalidOperationInternal();
    void Nrt_SetErrMsgIsCharacterNotFoundInternal();
    void Nrt_SetErrMsgIsOutOfMemoryInternal();
    void Nrt_SetErrMsgKeyNotFoundInternal();
    void Nrt_SetErrMsgRuntimeNotFoundInternal();
    void Nrt_SetErrMsgErrorUnknownInternal();
    void Nrt_SetErrMsgIsInvalidPathInternal();
    void Nrt_SetErrMsgCustomInternal(const char* message);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ERRORHANDLING_H
