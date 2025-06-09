// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_TYPEDEFS_H
#define NOVELRT_INTEROP_TYPEDEFS_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct NrtDebugService* NrtDebugServiceHandle;
    typedef struct NrtLoggingService* NrtLoggingServiceHandle;

    typedef enum
    {
        NRT_FALSE = 0,
        NRT_TRUE = 1
    } NrtBoolKind;

    // Mapped to the values from spdlog.
    typedef enum
    {
        NOVELRT_LOGLEVEL_DEBUG = 1,
        NOVELRT_LOGLEVEL_INFO = 2,
        NOVELRT_LOGLEVEL_WARN = 3,
        NOVELRT_LOGLEVEL_ERR = 4,
        NOVELRT_LOGLEVEL_OFF = 6
    } NrtLogLevelKind;

    typedef enum
    {
        NRT_DATA_NOT_MODIFIED = 1,
        NRT_SUCCESS = 0,
        NRT_FAILURE_UNKNOWN = -1,
        NRT_FAILURE_NULL_ARGUMENT_PROVIDED = -2,
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
        NRT_FAILURE_RUNTIME_NOT_FOUND = -18,
        NRT_FAILURE_NULL_INSTANCE_PROVIDED = -19,
        NRT_FAILURE_INVALID_DIRECTORY_PATH = -20
    } NrtResultKind;

    typedef uintptr_t NrtAtom;

    typedef int32_t NrtBool;
    typedef int32_t NrtLogLevel;
    typedef int32_t NrtResult;

    // clang-format off

#include "Maths/NrtMathsTypedefs.h"
#include "Timing/NrtTimingTypedefs.h"
#include "Utilities/NrtUtilitiesTypedefs.h"
#include "Ecs/Audio/NrtEcsAudioTypedefs.h"
#include "Ecs/Graphics/NrtEcsGraphicsTypedefs.h"
#include "Ecs/NrtEcsTypedefs.h"
#include "Graphics/NrtGraphicsTypedefs.h"
#include "Input/NrtInputTypedefs.h"
#include "PluginManagement/NrtPluginManagementTypedefs.h"
#include "ResourceManagement/NrtResourceManagementTypedefs.h"
#include "Windowing/NrtWindowingTypedefs.h"

    // clang-format on

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_TYPEDEFS_H
