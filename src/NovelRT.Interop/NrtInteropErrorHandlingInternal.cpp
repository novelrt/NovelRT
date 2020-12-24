// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.Interop/NrtInteropErrorHandlingInternal.h>
#include <stddef.h>

const char* const errMsgIsNullptr = "Unable to continue! A nullptr was passed when a ptr was expected.";
const char* const errMsgIsNaN = "Unable to continue! Calculation resulted in an object that is not a number (NaN).";
const char* const errMsgIsDivideByZero = "Unable to continue! Divide by zero was attempted.";
const char* const errMsgIsNotSUpportedInternal = "The current operation is not supported.";
const char* const errMsgIsAlreadyDeletedOrRemoved = "Unable to continue! The specific item has already been deleted or removed.";
const char* const errMsgIsInitialisationFailure = "Service could not be initialised.";
const char* const errMsgIsFunctionNotFound= "Failed to locate the specified managed function.";
const char* currentErrorMessage = nullptr;
bool customMessageSet = false;

#ifdef __cplusplus
extern "C" {
#endif

const char* Nrt_getLastErrorInternal() {
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

void Nrt_setErrMsgIsNullptrInternal() {
  validateCustomMessageInternal();
  currentErrorMessage = errMsgIsNullptr;
}

void Nrt_setErrMsgIsNaNInternal() {
  validateCustomMessageInternal();
  currentErrorMessage = errMsgIsNaN;
}

void Nrt_setErrMsgIsDivideByZeroInternal() {
  validateCustomMessageInternal();
  currentErrorMessage = errMsgIsDivideByZero;
}

void Nrt_setErrMsgIsAlreadyDeletedOrRemovedInternal() {
  validateCustomMessageInternal();
  currentErrorMessage = errMsgIsAlreadyDeletedOrRemoved;
}

void Nrt_setErrMsgIsInitialisationFailureInternal() {
  validateCustomMessageInternal();
  currentErrorMessage = errMsgIsInitialisationFailure;
}

void Nrt_setErrMsgIsNotSupportedInternal() {
  validateCustomMessageInternal();
  currentErrorMessage = errMsgIsNotSUpportedInternal;
}

void Nrt_setErrMsgIsFunctionNotFound() {
  validateCustomMessageInternal();
  currentErrorMessage = errMsgIsFunctionNotFound;
}

void Nrt_setErrMsgCustomInternal(const char* message) {
  currentErrorMessage = message;
  customMessageSet = true;
}

#ifdef __cplusplus
}
#endif
