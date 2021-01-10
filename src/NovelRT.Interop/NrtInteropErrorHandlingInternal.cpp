// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/NrtInteropErrorHandlingInternal.h>
#include <stddef.h>

const char* const errMsgIsNullptr = "Unable to continue! A nullptr was passed when a ptr was expected.";
const char* const errMsgIsNaN = "Unable to continue! Calculation resulted in an object that is not a number (NaN).";
const char* const errMsgIsDivideByZero = "Unable to continue! Divide by zero was attempted.";
const char* const errMsgIsNotSupportedInternal = "The current operation is not supported.";
const char* const errMsgIsAlreadyDeletedOrRemoved =
    "Unable to continue! The specific item has already been deleted or removed.";
const char* const errMsgIsInitialisationFailure = "Unable to continue! Service could not be initialised.";
const char* const errMsgIsFunctionNotFound = "Unable to continue! Failed to locate the specified managed function.";
const char* const errMsgIsNotInitialised = "Unable to continue! The service is currently not initialised.";
const char* const errMsgIsArgumentOutOfRange = "Unable to continue! The argument is out of range.";
const char* const errMsgIsInvalidOperation = "Unable to continue! The current operation is invalid.";
const char* const errMsgIsCharacterNotFound = "Unable to continue! The character can't be found.";
const char* const errMsgIsOutOfMemory = "Insufficient memory to continue the execution of the program.";
const char* currentErrorMessage = nullptr;
bool customMessageSet = false;

#ifdef __cplusplus
extern "C"
{
#endif

    const char* Nrt_getLastErrorInternal()
    {
        if (currentErrorMessage == nullptr)
        {
            return NULL;
        }

        return currentErrorMessage;
    }

    void validateCustomMessageInternal()
    {
        if (!customMessageSet)
        {
            return;
        }

        delete currentErrorMessage;
        customMessageSet = false;
    }

    void Nrt_setErrMsgIsNullptrInternal()
    {
        validateCustomMessageInternal();
        currentErrorMessage = errMsgIsNullptr;
    }

    void Nrt_setErrMsgIsNaNInternal()
    {
        validateCustomMessageInternal();
        currentErrorMessage = errMsgIsNaN;
    }

    void Nrt_setErrMsgIsDivideByZeroInternal()
    {
        validateCustomMessageInternal();
        currentErrorMessage = errMsgIsDivideByZero;
    }

    void Nrt_setErrMsgIsAlreadyDeletedOrRemovedInternal()
    {
        validateCustomMessageInternal();
        currentErrorMessage = errMsgIsAlreadyDeletedOrRemoved;
    }

    void Nrt_setErrMsgIsInitialisationFailureInternal()
    {
        validateCustomMessageInternal();
        currentErrorMessage = errMsgIsInitialisationFailure;
    }

    void Nrt_setErrMsgIsNotSupportedInternal()
    {
        validateCustomMessageInternal();
        currentErrorMessage = errMsgIsNotSupportedInternal;
    }

    void Nrt_setErrMsgIsFunctionNotFoundInternal()
    {
        validateCustomMessageInternal();
        currentErrorMessage = errMsgIsFunctionNotFound;
    }

    void Nrt_setErrMsgIsNotInitialisedInternal()
    {
        validateCustomMessageInternal();
        currentErrorMessage = errMsgIsNotInitialised;
    }

    void Nrt_setErrMsgIsArgumentOutOfRangeInternal()
    {
        validateCustomMessageInternal();
        currentErrorMessage = errMsgIsArgumentOutOfRange;
    }

    void Nrt_setErrMsgIsInvalidOperationInternal()
    {
        validateCustomMessageInternal();
        currentErrorMessage = errMsgIsInvalidOperation;
    }

    void Nrt_setErrMsgIsCharacterNotFoundInternal()
    {
        validateCustomMessageInternal();
        currentErrorMessage = errMsgIsCharacterNotFound;
    }

    void Nrt_setErrMsgIsOutOfMemoryInternal()
    {
        validateCustomMessageInternal();
        currentErrorMessage = errMsgIsOutOfMemory;
    }

    void Nrt_setErrMsgCustomInternal(const char* message)
    {
        currentErrorMessage = message;
        customMessageSet = true;
    }

#ifdef __cplusplus
}
#endif
