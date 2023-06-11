// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include "../../LifetimeExtender.h"
#include <NovelRT.Interop/Ecs/Graphics/NrtDefaultRenderingSystem.h>
#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT/Ecs/Ecs.h>

using namespace NovelRT::Ecs;
using namespace NovelRT::Ecs::Graphics;
using namespace NovelRT::Threading;
using namespace NovelRT::Interop;

NrtResult Nrt_DefaultRenderingSystem_FindInScheduler(NrtSystemSchedulerHandle scheduler,
                                                     NrtDefaultRenderingSystemHandle* outputResult)
{
    if (scheduler == nullptr)
    {
        Nrt_setErrMsgIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    if (outputResult == nullptr)
    {
        Nrt_setErrMsgIsNullArgumentProvidedInternal();
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
        Nrt_setErrMsgKeyNotFoundInternal();
        return NRT_FAILURE_KEY_NOT_FOUND;
    }
}

NrtResult Nrt_DefaultRenderingSystem_ForceVertexTextureFutureResolution(NrtDefaultRenderingSystemHandle system)
{
    if (system == nullptr)
    {
        Nrt_setErrMsgIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    reinterpret_cast<DefaultRenderingSystem*>(system)->ForceVertexTextureFutureResolution();
    return NRT_SUCCESS;
}
NrtResult Nrt_DefaultRenderingSystem_GetOrLoadTexture(NrtDefaultRenderingSystemHandle system,
                                                      const char* textureName,
                                                      NrtFutureResultOfTextureInfoHandle* outputTextureFuture)
{
    if (system == nullptr)
    {
        Nrt_setErrMsgIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }
    if (textureName == nullptr)
    {
        Nrt_setErrMsgIsNullArgumentProvidedInternal();
        return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
    }

    auto* rendering = reinterpret_cast<DefaultRenderingSystem*>(system);
    FutureResult<TextureInfo>&& future = rendering->GetOrLoadTexture(std::string(textureName));
    // Let's move the FutureResult to the C land.
    *outputTextureFuture =
        reinterpret_cast<NrtFutureResultOfTextureInfoHandle>(new FutureResult<TextureInfo>{std::move(future)});

    return NRT_SUCCESS;
}

NrtResult Nrt_DefaultRenderingSystem_GetExistingTextureById(NrtDefaultRenderingSystemHandle system,
                                                            NrtAtom id,
                                                            NrtTextureInfoHandle* outputTexture)
{
    if (system == nullptr)
    {
        Nrt_setErrMsgIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }
    if (outputTexture == nullptr)
    {
        Nrt_setErrMsgIsNullArgumentProvidedInternal();
        return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
    }

    auto* rendering = reinterpret_cast<DefaultRenderingSystem*>(system);
    ConcurrentSharedPtr<TextureInfo> texture(nullptr);
    try
    {
        texture = rendering->GetExistingTexture(id);
    }
    catch (const std::out_of_range&)
    {
        return NRT_FAILURE_KEY_NOT_FOUND;
    }

    *outputTexture = reinterpret_cast<NrtTextureInfoHandle>(texture.get());
    ConcurrentLifetime::KeepAlive(std::move(texture));

    return NRT_SUCCESS;
}

NrtResult Nrt_DefaultRenderingSystem_GetExistingTextureByName(NrtDefaultRenderingSystemHandle system,
                                                              const char* name,
                                                              NrtTextureInfoHandle* outputTexture)
{
    if (system == nullptr)
    {
        Nrt_setErrMsgIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }
    if (name == nullptr)
    {
        Nrt_setErrMsgIsNullArgumentProvidedInternal();
        return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
    }
    if (outputTexture == nullptr)
    {
        Nrt_setErrMsgIsNullArgumentProvidedInternal();
        return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
    }

    auto* rendering = reinterpret_cast<DefaultRenderingSystem*>(system);
    ConcurrentSharedPtr<TextureInfo> texture(nullptr);
    try
    {
        texture = rendering->GetExistingTexture(std::string(name));
    }
    catch (const NovelRT::Exceptions::KeyNotFoundException&)
    {
        return NRT_FAILURE_KEY_NOT_FOUND;
    }

    *outputTexture = reinterpret_cast<NrtTextureInfoHandle>(texture.get());
    ConcurrentLifetime::KeepAlive(std::move(texture));

    return NRT_SUCCESS;
}
NrtResult Nrt_DefaultRenderingSystem_DeleteTextureByHandle(NrtDefaultRenderingSystemHandle system,
                                                           NrtTextureInfoHandle texture)
{
    if (system == nullptr)
    {
        Nrt_setErrMsgIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }
    if (texture == nullptr)
    {
        Nrt_setErrMsgIsNullArgumentProvidedInternal();
        return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
    }

    auto* cppTexture = reinterpret_cast<TextureInfo*>(texture);
    ConcurrentSharedPtr<TextureInfo> sharedTexture = ConcurrentLifetime::Find(cppTexture);
    if (sharedTexture == nullptr)
    {
        Nrt_setErrMsgIsAlreadyDeletedOrRemovedInternal();
        return NRT_FAILURE_ALREADY_DELETED_OR_REMOVED;
    }

    auto* rendering = reinterpret_cast<DefaultRenderingSystem*>(system);
    rendering->DeleteTexture(sharedTexture);

    return NRT_SUCCESS;
}

NrtResult Nrt_DefaultRenderingSystem_DeleteTextureByName(NrtDefaultRenderingSystemHandle system, const char* name)
{
    if (system == nullptr)
    {
        Nrt_setErrMsgIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }
    if (name == nullptr)
    {
        Nrt_setErrMsgIsNullArgumentProvidedInternal();
        return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
    }

    auto* rendering = reinterpret_cast<DefaultRenderingSystem*>(system);
    try
    {
        rendering->DeleteTexture(std::string(name));
    }
    catch (const NovelRT::Exceptions::KeyNotFoundException&)
    {
        return NRT_FAILURE_KEY_NOT_FOUND;
    }

    return NRT_SUCCESS;
}

NrtResult Nrt_DefaultRenderingSystem_DeleteTextureById(NrtDefaultRenderingSystemHandle system, NrtAtom id)
{
    if (system == nullptr)
    {
        Nrt_setErrMsgIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    auto* rendering = reinterpret_cast<DefaultRenderingSystem*>(system);
    try
    {
        rendering->DeleteTexture(id);
    }
    catch (const NovelRT::Exceptions::KeyNotFoundException&)
    {
        return NRT_FAILURE_KEY_NOT_FOUND;
    }

    return NRT_SUCCESS;
}
NrtResult Nrt_DefaultRenderingSystem_CreateSpriteEntity(NrtDefaultRenderingSystemHandle system,
                                                        NrtTextureInfoHandle texture,
                                                        NrtCatalogueHandle catalogue,
                                                        NrtEntityId* outputEntityId)
{
    if (system == nullptr)
    {
        Nrt_setErrMsgIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }
    if (texture == nullptr)
    {
        Nrt_setErrMsgIsNullArgumentProvidedInternal();
        return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
    }
    if (catalogue == nullptr)
    {
        Nrt_setErrMsgIsNullArgumentProvidedInternal();
        return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
    }
    if (outputEntityId == nullptr)
    {
        Nrt_setErrMsgIsNullArgumentProvidedInternal();
        return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
    }

    auto* rendering = reinterpret_cast<DefaultRenderingSystem*>(system);
    auto* cppTexture = reinterpret_cast<TextureInfo*>(texture);
    auto* cppCatalogue = reinterpret_cast<Catalogue*>(catalogue);

    ConcurrentSharedPtr<TextureInfo> sharedTexture = ConcurrentLifetime::Find(cppTexture);
    if (sharedTexture == nullptr)
    {
        Nrt_setErrMsgIsAlreadyDeletedOrRemovedInternal();
        return NRT_FAILURE_ALREADY_DELETED_OR_REMOVED;
    }

    NrtAtom id = rendering->CreateSpriteEntity(sharedTexture, *cppCatalogue);
    *outputEntityId = id;

    return NRT_SUCCESS;
}
NrtResult Nrt_DefaultRenderingSystem_CreateSpriteEntityOutsideOfSystem(NrtDefaultRenderingSystemHandle system,
                                                                       NrtTextureInfoHandle texture,
                                                                       NrtSystemSchedulerHandle scheduler,
                                                                       NrtEntityId* outputEntityId)
{
    if (system == nullptr)
    {
        Nrt_setErrMsgIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }
    if (texture == nullptr)
    {
        Nrt_setErrMsgIsNullArgumentProvidedInternal();
        return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
    }
    if (scheduler == nullptr)
    {
        Nrt_setErrMsgIsNullArgumentProvidedInternal();
        return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
    }
    if (outputEntityId == nullptr)
    {
        Nrt_setErrMsgIsNullArgumentProvidedInternal();
        return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
    }

    auto* rendering = reinterpret_cast<DefaultRenderingSystem*>(system);
    auto* cppTexture = reinterpret_cast<TextureInfo*>(texture);
    auto* cppScheduler = reinterpret_cast<SystemScheduler*>(scheduler);

    ConcurrentSharedPtr<TextureInfo> sharedTexture = ConcurrentLifetime::Find(cppTexture);
    if (sharedTexture == nullptr)
    {
        Nrt_setErrMsgIsAlreadyDeletedOrRemovedInternal();
        return NRT_FAILURE_ALREADY_DELETED_OR_REMOVED;
    }

    NrtAtom id = rendering->CreateSpriteEntityOutsideOfSystem(sharedTexture, *cppScheduler);
    *outputEntityId = id;

    return NRT_SUCCESS;
}
