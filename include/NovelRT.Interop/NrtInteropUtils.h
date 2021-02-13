// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_NOVELRTINTEROPUTILS_H
#define NOVELRT_INTEROP_NOVELRTINTEROPUTILS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

    typedef int32_t NrtResult;

    enum NrtResultKind
    {
        NRT_DATA_NOT_MODIFIED = 1,
        NRT_SUCCESS = 0,
        NRT_FAILURE_UNKNOWN = -1,
        NRT_FAILURE_NULLPTR_PROVIDED = -2,
        NRT_FAILURE_NOT_A_NUMBER = -3,
        NRT_FAILURE_DIVIDE_BY_ZERO = -4,
        NRT_FAILURE_ALREADY_DELETED_OR_REMOVED = -5,
        NRT_FAILURE_ARGUMENT_OUT_OF_RANGE = -6,
        NRT_FAILURE_FILE_NOT_FOUND = -7,
        NRT_FAILURE_NOT_SUPPORTED = -8,
        NRT_FAILURE_CHARACTER_NOT_FOUND = -9,
        NRT_FAILURE_INITIALISATION_FAILURE = -10,
        NRT_FAILURE_NOT_INITIALISED = -11,
        NRT_FAILURE_FUNCTION_NOT_FOUND = -12,
        NRT_FAILURE_INVALID_OPERATION = -13,
        NRT_FAILURE_DUPLICATE_KEY_PROVIDED = -14,
        NRT_FAILURE_KEY_NOT_FOUND = -15,
        NRT_FAILURE_OUT_OF_MEMORY = -16,
        NRT_FAILURE_COMPILATION_ERROR = -17,
        NRT_FAILURE_RUNTIME_NOT_FOUND = -18
    };

    typedef int32_t NrtBool;

    enum NrtBoolKind
    {
        NRT_FALSE = 0,
        NRT_TRUE = 1
    };

    typedef uintptr_t NrtAtom;

    const char* Nrt_getLastError();

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_NOVELRTINTEROPUTILS_H
