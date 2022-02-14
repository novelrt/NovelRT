// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_ECS_PLUGINMANAGEMENT_TYPEDEFS_H
#define NOVELRT_INTEROP_ECS_PLUGINMANAGEMENT_TYPEDEFS_H
#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct NrtIGraphicsPluginProviderPtr* NrtIGraphicsPluginProviderPtrHandle;
    typedef struct NrtIWindowingPluginProviderPtr* NrtIWindowingPluginProviderPtrHandle;
    typedef struct NrtIResourceManagementPluginProviderPtr* NrtIResourceManagementPluginProviderPtrHandle;

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ECS_PLUGINMANAGEMENT_TYPEDEFS_H