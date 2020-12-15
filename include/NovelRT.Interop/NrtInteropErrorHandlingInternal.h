// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#ifndef NOVELRT_INTEROP_NOVELRTINTEROPERRORHANDLINGINTERNAL_H
#define NOVELRT_INTEROP_NOVELRTINTEROPERRORHANDLINGINTERNAL_H

#ifdef __cplusplus
extern "C" {
#endif

const char* Nrt_getLastErrorInternal();
void Nrt_setErrMsgIsNullptrInternal();
void Nrt_setErrMsgIsNaNInternal();
void Nrt_setErrMsgIsDivideByZeroInternal();
void Nrt_setErrMsgIsAlreadyDeletedOrRemovedInternal();
void Nrt_setErrMsgCustomInternal(const char* message);

#ifdef __cplusplus
}
#endif

#endif //!NOVELRT_INTEROP_NOVELRTINTEROPERRORHANDLINGINTERNAL_H