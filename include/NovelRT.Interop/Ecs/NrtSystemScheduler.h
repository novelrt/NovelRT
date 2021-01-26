// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_NRTSYSTEMSCHEDULER_H
#define NOVELRT_NRTSYSTEMSCHEDULER_H

#include "../NrtInteropUtils.h"
#include "NrtEcsUtils.h"
#include "../Timing/NrtTimestamp.h"
#include "NrtCatalogue.h"

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct SystemSchedulerHandle* NrtSystemScheduler;

    typedef (*NrtSystemUpdatePtr)(NrtTimestamp, NrtCatalogue);

    NrtSystemScheduler Nrt_SystemScheduler_CreateWithDefaultThreadCount();

    NrtSystemScheduler Nrt_SystemScheduler_Create(uint32_t maximumThreadCount);

    void Nrt_SystemScheduler_RegisterSystem(NrtSystemScheduler scheduler, NrtSystemUpdatePtr systemUpdatePtr);

    uint32_t Nrt_SystemScheduler_GetWorkerThreadCount(NrtSystemScheduler systemScheduler);

    NrtEntityCache Nrt_SystemScheduler_GetEntityCache(NrtSystemScheduler systemScheduler);

    NrtComponentCache Nrt_SystemScheduler_GetComponentCache(NrtSystemScheduler systemScheduler);

    void Nrt_SystemScheduler_SpinThreads(NrtSystemScheduler systemScheduler);

    NrtResult Nrt_SystemScheduler_ExecuteIteration(NrtSystemScheduler systemScheduler, NrtTimestamp delta);

    NrtResult Nrt_SystemScheduler_Destroy(NrtSystemScheduler systemScheduler);

#ifdef __cplusplus
};
#endif

#endif // !NOVELRT_NRTSYSTEMSCHEDULER_H
