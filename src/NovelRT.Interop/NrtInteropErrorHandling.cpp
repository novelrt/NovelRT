// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/NrtErrorHandling.h>

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

    const char* Nrt_getLastError()
    {
        return Nrt_getLastErrorInternal();
    }

    // Internal

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

    NrtResult Nrt_getNullArgumentErrorInternal()
    {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
    }

    NrtResult Nrt_getNullInstanceErrorInternal()
    {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    NrtResult Nrt_getNaNErrorInternal()
    {
        Nrt_setErrMsgIsNaNInternal();
        return NRT_FAILURE_NOT_A_NUMBER;
    }

    NrtResult Nrt_getDivideByZeroErrorInternal()
    {
        Nrt_setErrMsgIsDivideByZeroInternal();
        return NRT_FAILURE_DIVIDE_BY_ZERO;
    }

    NrtResult Nrt_getAlreadyDeletedOrRemovedErrorInternal()
    {
        Nrt_setErrMsgIsAlreadyDeletedOrRemovedInternal();
        return NRT_FAILURE_ALREADY_DELETED_OR_REMOVED;
    }

    NrtResult Nrt_getNotSupportedErrorInternal()
    {
        Nrt_setErrMsgIsNotSupportedInternal();
        return NRT_FAILURE_NOT_SUPPORTED;
    }

    NrtResult Nrt_getInitialisationFailureErrorInternal()
    {
        Nrt_setErrMsgIsInitialisationFailureInternal();
        return NRT_FAILURE_INITIALISATION_FAILURE;
    }

    NrtResult Nrt_getFunctionNotFoundErrorInternal()
    {
        Nrt_setErrMsgIsFunctionNotFoundInternal();
        return NRT_FAILURE_FUNCTION_NOT_FOUND;
    }

    NrtResult Nrt_getNotInitialisedErrorInternal()
    {
        Nrt_setErrMsgIsNotInitialisedInternal();
        return NRT_FAILURE_NOT_INITIALISED;
    }

    NrtResult Nrt_getArgumentOutOfRangeErrorInternal()
    {
        Nrt_setErrMsgIsArgumentOutOfRangeInternal();
        return NRT_FAILURE_ARGUMENT_OUT_OF_RANGE;
    }

    NrtResult Nrt_getInvalidOperationErrorInternal()
    {
        Nrt_setErrMsgIsInvalidOperationInternal();
        return NRT_FAILURE_INVALID_OPERATION;
    }

    NrtResult Nrt_getCharacterNotFoundErrorInternal()
    {
        Nrt_setErrMsgIsCharacterNotFoundInternal();
        return NRT_FAILURE_CHARACTER_NOT_FOUND;
    }

    NrtResult Nrt_getOutOfMemoryErrorInternal()
    {
        Nrt_setErrMsgIsOutOfMemoryInternal();
        return /*regexo no*/ NRT_FAILURE_OUT_OF_MEMORY;
    }

#ifdef __cplusplus
}
#endif
