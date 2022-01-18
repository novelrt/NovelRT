// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_ERRORHANDLING_H
#define NOVELRT_INTEROP_ERRORHANDLING_H

#include "NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    const char* Nrt_getLastError();

    // Internal
    const char* Nrt_getLastErrorInternal();
    void Nrt_setErrMsgIsNullptrInternal();
    void Nrt_setErrMsgIsNaNInternal();
    void Nrt_setErrMsgIsDivideByZeroInternal();
    void Nrt_setErrMsgIsAlreadyDeletedOrRemovedInternal();
    void Nrt_setErrMsgIsNotSupportedInternal();
    void Nrt_setErrMsgIsInitialisationFailureInternal();
    void Nrt_setErrMsgIsFunctionNotFoundInternal();
    void Nrt_setErrMsgIsNotInitialisedInternal();
    void Nrt_setErrMsgIsArgumentOutOfRangeInternal();
    void Nrt_setErrMsgIsInvalidOperationInternal();
    void Nrt_setErrMsgIsCharacterNotFoundInternal();
    void Nrt_setErrMsgIsOutOfMemoryInternal();
    void Nrt_setErrMsgCustomInternal(const char* message);

    NrtResult Nrt_getNullArgumentErrorInternal();
    NrtResult Nrt_getNullInstanceErrorInternal();
    NrtResult Nrt_getNaNErrorInternal();
    NrtResult Nrt_getDivideByZeroErrorInternal();
    NrtResult Nrt_getAlreadyDeletedOrRemovedErrorInternal();
    NrtResult Nrt_getNotSupportedErrorInternal();
    NrtResult Nrt_getInitialisationFailureErrorInternal();
    NrtResult Nrt_getFunctionNotFoundErrorInternal();
    NrtResult Nrt_getNotInitialisedErrorInternal();
    NrtResult Nrt_getArgumentOutOfRangeErrorInternal();
    NrtResult Nrt_getInvalidOperationErrorInternal();
    NrtResult Nrt_getCharacterNotFoundErrorInternal();
    NrtResult Nrt_getOutOfMemoryErrorInternal();

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ERRORHANDLING_H
