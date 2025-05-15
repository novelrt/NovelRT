// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Ecs/Graphics/NrtDefaultRenderingSystem.h>
#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT/Ecs/Ecs.h>

using namespace NovelRT::Ecs;
//using namespace NovelRT::Ecs::Graphics;

NrtResult Nrt_DefaultRenderingSystem_FindInScheduler(NrtSystemSchedulerHandle scheduler,
                                                     NrtDefaultRenderingSystemHandle* outputResult)
{
    unused(scheduler);
    unused(outputResult);
    return NRT_FAILURE_UNKNOWN;
    //if (scheduler == nullptr)
    //{
    //    Nrt_setErrMsgIsNullInstanceProvidedInternal();
    //    return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    //}

    //if (outputResult == nullptr)
    //{
    //    Nrt_setErrMsgIsNullArgumentProvidedInternal();
    //    return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
    //}

    //try
    //{
    //    auto* sched = reinterpret_cast<SystemScheduler*>(scheduler);
    //    std::shared_ptr<DefaultRenderingSystem> system = sched->GetRegisteredIEcsSystemAs<DefaultRenderingSystem>();
    //    *outputResult = reinterpret_cast<NrtDefaultRenderingSystemHandle>(system.get());

    //    return NRT_SUCCESS;
    //}
    //catch (const NovelRT::Exceptions::KeyNotFoundException&)
    //{
    //    Nrt_setErrMsgKeyNotFoundInternal();
    //    return NRT_FAILURE_KEY_NOT_FOUND;
    //}
}

NrtResult Nrt_DefaultRenderingSystem_ForceVertexTextureFutureResolution(NrtDefaultRenderingSystemHandle system)
{
    unused(system);
    return NRT_FAILURE_UNKNOWN;
    //if (system == nullptr)
    //{
    //    Nrt_setErrMsgIsNullInstanceProvidedInternal();
    //    return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    //}

    //reinterpret_cast<DefaultRenderingSystem*>(system)->ForceVertexTextureFutureResolution();
    //return NRT_SUCCESS;
}
