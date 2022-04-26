// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_ECS_COMPONENTCACHE_H
#define NOVELRT_INTEROP_ECS_COMPONENTCACHE_H

#include <NovelRT.Interop/NrtTypedefs.h>

#ifdef __cplusplus
extern "C"
{
#endif

    NrtComponentCacheHandle Nrt_ComponentCache_Create(size_t poolSize);

    NrtResult Nrt_ComponentCache_RegisterComponentTypeUnsafe(NrtComponentCacheHandle componentCache,
                                                             size_t sizeOfDataType,
                                                             const void* deleteInstructionState,
                                                             NrtComponentUpdateFnPtr updateFnPtr,
                                                             const char* serialisedTypeName,
                                                             void* context,
                                                             NrtComponentTypeId* outputResult);

    NrtResult Nrt_ComponentCache_GetComponentBufferById(NrtComponentCacheHandle componentCache,
                                                        NrtComponentTypeId id,
                                                        NrtComponentBufferMemoryContainerHandle* outputResult);

    void Nrt_ComponentCache_PrepAllBuffersForNextFrame(NrtComponentCacheHandle componentCache,
                                                       NrtEntityIdVectorHandle entitiesToDelete);

    NrtResult Nrt_ComponentCache_Destroy(NrtComponentCacheHandle componentCache);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ECS_COMPONENTCACHE_H
