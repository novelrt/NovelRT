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

const char* const cpuLangKey = "cpu";

const char* const errMsgIsNullptr = "Unable to continue! A nullptr was passed when a ptr was expected.";
const char* const errMsgIsNaN = "Unable to continue! Calculation resulted in an object that is not a number (NaN).";
const char* const errMsgIsDivideByZero = "Unable to continue! Divide by zero was attempted.";

const char* NovelRT_translateErrorCode(const char* targetLanguage, const char* errorPtr);
  
#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_NOVELRTRESULT_H
