// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#ifndef NOVELRT_INTEROP_NOVELRTINTEROPERRORHANDLINGINTERNAL_H
#define NOVELRT_INTEROP_NOVELRTINTEROPERRORHANDLINGINTERNAL_H

#ifdef WIN32
#define strcpy strcpy_s
#endif

#ifdef __cplusplus
extern "C" {
#endif

const char* NovelRT_getLastErrorInternal();
void NovelRT_setErrMsgIsNullptrInternal();
void NovelRT_setErrMsgIsNaNInternal();
void NovelRT_setErrMsgIsDivideByZeroInternal();
void NovelRT_setErrMsgIsAlreadyDeletedOrRemovedInternal();
void NovelRT_setErrMsgCustomInternal(const char* message);

#ifdef __cplusplus
}
#endif

#endif //!NOVELRT_INTEROP_NOVELRTINTEROPERRORHANDLINGINTERNAL_H