// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#ifndef NOVELRT_INTEROP_ECS_NRTPLUGINMANAGEMENTTYPEDEFS_H
#define NOVELRT_INTEROP_ECS_NRTPLUGINMANAGEMENTTYPEDEFS_H

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct NrtIGraphicsPluginProvider* NrtIGraphicsPluginProviderHandle;
    typedef struct NrtIInputPluginProvider* NrtIInputPluginProviderHandle;
    typedef struct NrtIResourceManagementPluginProvider* NrtIResourceManagementPluginProviderHandle;
    typedef struct NrtIWindowingPluginProvider* NrtIWindowingPluginProviderHandle;
    typedef struct NrtDefaultPluginSelector* NrtDefaultPluginSelectorHandle;
#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ECS_NRTPLUGINMANAGEMENTTYPEDEFS_H
