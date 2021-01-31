// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_NRTCOMPONENTCACHE_H
#define NOVELRT_NRTCOMPONENTCACHE_H

#include "../NrtInteropUtils.h"
#include "NrtComponentBufferMemoryContainer.h"
#include "NrtEcsUtils.h"

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct ComponentCacheHandle* NrtComponentCache;

    NrtComponentCache Nrt_ComponentCache_Create(size_t poolSize);

    NrtResult Nrt_ComponentCache_GetComponentBufferById(NrtComponentCache componentCache,
                                                        NrtComponentTypeId id,
                                                        NrtComponentBufferMemoryContainer* outputResult);

    void Nrt_ComponentCache_PrepAllBuffersForNextFrame(NrtComponentCache componentCache,
                                                       NrtEntityIdVector entitiesToDelete);

    NrtResult Nrt_ComponentCache_Delete(NrtComponentCache componentCache);

#ifdef __cplusplus
};
#endif

#endif // !NOVELRT_NRTCOMPONENTCACHE_H
