// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_ECS_INPUT_INPUTSYSTEM_H
#define NOVELRT_INTEROP_ECS_INPUT_INPUTSYSTEM_H

#include "../../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtInputSystemHandle Nrt_InputSystem_Create(
        NrtIWindowingPluginProviderPtrHandle windowingProvider,
        NrtIInputPluginProviderPtrHandle inputProvider);
    NrtResult Nrt_InputSystem_Destroy(NrtInputSystemHandle system);

    NrtResult Nrt_InputSystem_Update(NrtInputSystemHandle system, NrtTimestamp delta, NrtCatalogueHandle catalogue);
    NrtResult Nrt_InputSystem_AddMapping(NrtInputSystemHandle system, const char* name, const char* id);
    NrtResult Nrt_InputSystem_AddDefaultKBMMapping(NrtInputSystemHandle system);
    NrtResult Nrt_InputSystem_GetMappingId(
        NrtInputSystemHandle system,
        const char* mappingName,
        NrtAtom *outputResult);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ECS_INPUT_INPUTSYSTEM_H
