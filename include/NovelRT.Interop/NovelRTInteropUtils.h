// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#ifndef NOVELRT_INTEROP_NOVELRTINTEROPUTILS_H
#define NOVELRT_INTEROP_NOVELRTINTEROPUTILS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

enum {
  NOVELRT_SUCCESS = 0,
  NOVELRT_FAILURE = 1
};


enum {
  NOVELRT_FALSE = 0,
  NOVELRT_TRUE = 1
};

const char* NovelRT_getCpuLangKey();
const char* NovelRT_getErrMsgIsNullptr();
const char* NovelRT_getErrMsgIsNaN();
const char* NovelRT_getErrMsgIsDivideByZero();
const char* NovelRT_getErrMsgIsAlreadyDeletedOrRemoved();
const char* NovelRT_translateErrorCode(const char* targetLanguage, const char* errorPtr);
  
#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_NOVELRTINTEROPUTILS_H
