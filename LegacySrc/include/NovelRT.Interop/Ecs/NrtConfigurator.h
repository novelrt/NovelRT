// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#ifndef NOVELRT_INTEROP_ECS_NRTCONFIGURATOR_H
#define NOVELRT_INTEROP_ECS_NRTCONFIGURATOR_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtConfiguratorHandle Nrt_Configurator_Create();

    NrtResult Nrt_Configurator_Destroy(NrtConfiguratorHandle configurator);

    NrtResult Nrt_Configurator_AddDefaultSystemsAndComponents(NrtConfiguratorHandle configurator);

    NrtResult Nrt_Configurator_AddGraphicsPluginProvider(NrtConfiguratorHandle configurator,
                                                         NrtIGraphicsPluginProviderHandle provider);

    NrtResult Nrt_Configurator_AddWindowingPluginProvider(NrtConfiguratorHandle configurator,
                                                          NrtIWindowingPluginProviderHandle provider);

    NrtResult Nrt_Configurator_AddResourceManagementPluginProvider(NrtConfiguratorHandle configurator,
                                                                   NrtIResourceManagementPluginProviderHandle provider);

    NrtResult Nrt_Configurator_AddInputPluginProvider(NrtConfiguratorHandle configurator,
                                                      NrtIInputPluginProviderHandle provider);

    // The given scheduler is owned by the API consumer! Make sure to destroy it once you're done with it.
    NrtResult Nrt_Configurator_InitialiseAndRegisterComponents(NrtConfiguratorHandle configurator,
                                                               NrtSystemSchedulerHandle* outputSystemScheduler);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ECS_NRTCONFIGURATOR_H
