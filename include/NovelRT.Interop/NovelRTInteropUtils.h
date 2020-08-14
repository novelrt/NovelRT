// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#ifndef NOVELRT_INTEROP_NOVELRTRESULT_H
#define NOVELRT_INTEROP_NOVELRTRESULT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  NOVELRT_SUCCESS = 0,
  NOVELRT_FAILURE = 1
} NovelRTResult;

typedef uint32_t NovelRTBool;

#define NOVELRT_TRUE 1u
#define NOVELRT_FALSE 0u

extern const char* const cpuLangKey; 
extern const char* const errMsgIsNullptr; 
extern const char* const errMsgIsNaN;
extern const char* const errMsgIsDivideByZero;

const char* NovelRT_translateErrorCode(const char* targetLanguage, const char* errorPtr);
  
#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_NOVELRTRESULT_H
