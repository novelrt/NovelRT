// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "NovelRTInteropErrorHandlingInternal.h"
#include <stddef.h>

const char* const errMsgIsNullptr = "Unable to continue! A nullptr was passed when a ptr was expected.";
const char* const errMsgIsNaN = "Unable to continue! Calculation resulted in an object that is not a number (NaN).";
const char* const errMsgIsDivideByZero = "Unable to continue! Divide by zero was attempted.";
const char* const errMsgIsAlreadyDeletedOrRemoved = "Unable to continue! The specific item has already been deleted or removed.";
const char* currentErrorMessage = nullptr;
bool customMessageSet = false;

#ifdef __cplusplus
extern "C" {
#endif

const char* NovelRT_getLastErrorInternal() {
  if (currentErrorMessage == nullptr) {
    return NULL;
  }

  return currentErrorMessage;
}

void validateCustomMessageInternal() {
  if (!customMessageSet) {
    return;
  }

  delete currentErrorMessage;
  customMessageSet = false;
}

void NovelRT_setErrMsgIsNullptrInternal() {
  validateCustomMessageInternal();
  currentErrorMessage = errMsgIsNullptr;
}

void NovelRT_setErrMsgIsNaNInternal() {
  validateCustomMessageInternal();
  currentErrorMessage = errMsgIsNaN;
}

void NovelRT_setErrMsgIsDivideByZeroInternal() {
  validateCustomMessageInternal();
  currentErrorMessage = errMsgIsDivideByZero;
}

void NovelRT_setErrMsgIsAlreadyDeletedOrRemovedInternal() {
  validateCustomMessageInternal();
  currentErrorMessage = errMsgIsAlreadyDeletedOrRemoved;
}

void NovelRT_setErrMsgCustomInternal(const char* message) {
  currentErrorMessage = message;
  customMessageSet = true;
}

#ifdef __cplusplus
}
#endif