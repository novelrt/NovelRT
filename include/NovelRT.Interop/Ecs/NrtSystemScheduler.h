// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_ECS_SYSTEMSCHEDULER_H
#define NOVELRT_INTEROP_ECS_SYSTEMSCHEDULER_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtSystemSchedulerHandle Nrt_SystemScheduler_CreateWithDefaultThreadCount();

    NrtSystemSchedulerHandle Nrt_SystemScheduler_Create(uint32_t maximumThreadCount);

    void Nrt_SystemScheduler_RegisterSystem(NrtSystemSchedulerHandle scheduler,
                                            NrtSystemUpdateFnPtr systemUpdatePtr,
                                            void* context);

    uint32_t Nrt_SystemScheduler_GetWorkerThreadCount(NrtSystemSchedulerHandle systemScheduler);

    NrtEntityCacheHandle Nrt_SystemScheduler_GetEntityCache(NrtSystemSchedulerHandle systemScheduler);

    NrtComponentCacheHandle Nrt_SystemScheduler_GetComponentCache(NrtSystemSchedulerHandle systemScheduler);

    void Nrt_SystemScheduler_SpinThreads(NrtSystemSchedulerHandle systemScheduler);

    NrtResult Nrt_SystemScheduler_ExecuteIteration(NrtSystemSchedulerHandle systemScheduler, NrtTimestamp delta);

    NrtResult Nrt_SystemScheduler_Destroy(NrtSystemSchedulerHandle systemScheduler);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ECS_SYSTEMSCHEDULER_H
