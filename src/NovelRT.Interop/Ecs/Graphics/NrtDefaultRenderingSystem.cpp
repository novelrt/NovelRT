// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Ecs/Graphics/NrtDefaultRenderingSystem.h>
#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT/Ecs/Ecs.h>
#include <NovelRT/Ecs/Graphics/Ecs.Graphics.h>

using namespace NovelRT::Ecs;
using namespace NovelRT::Ecs::Graphics;

NrtResult Nrt_DefaultRenderingSystem_FindInScheduler(NrtSystemSchedulerHandle scheduler,
                                                     NrtDefaultRenderingSystemHandle* outputResult)
{
    if (scheduler == nullptr)
    {
        Nrt_SetErrMsgIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    if (outputResult == nullptr)
    {
        Nrt_SetErrMsgIsNullArgumentProvidedInternal();
        return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
    }

    try
    {
        auto* sched = reinterpret_cast<SystemScheduler*>(scheduler);
        std::shared_ptr<DefaultRenderingSystem> system = sched->GetRegisteredIEcsSystemAs<DefaultRenderingSystem>();
        *outputResult = reinterpret_cast<NrtDefaultRenderingSystemHandle>(system.get());

        return NRT_SUCCESS;
    }
    catch (const NovelRT::Exceptions::KeyNotFoundException&)
    {
        Nrt_SetErrMsgKeyNotFoundInternal();
        return NRT_FAILURE_KEY_NOT_FOUND;
    }
}

NrtResult Nrt_DefaultRenderingSystem_ForceVertexTextureFutureResolution(NrtDefaultRenderingSystemHandle system)
{
    if (system == nullptr)
    {
        Nrt_SetErrMsgIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    reinterpret_cast<DefaultRenderingSystem*>(system)->ForceVertexTextureFutureResolution();
    return NRT_SUCCESS;
}
