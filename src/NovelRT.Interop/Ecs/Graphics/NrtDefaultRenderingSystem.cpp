// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Ecs/Graphics/NrtDefaultRenderingSystem.h>
#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT/Ecs/Ecs.h>

using namespace NovelRT;
using namespace Threading;
using namespace Ecs::Graphics;
using namespace PluginManagement;

std::list<std::shared_ptr<DefaultRenderingSystem>> _defaultRenderingSystemCollection;

#ifdef __cplusplus
extern "C"
{
#endif

    NrtDefaultRenderingSystemHandle Nrt_DefaultRenderingSystem_Create(
        NrtIGraphicsPluginProviderPtrHandle graphicsPluginProvider,
        NrtIWindowingPluginProviderPtrHandle windowingPluginProvider,
        NrtIResourceManagementPluginProviderPtrHandle resourceManagementPluginProvider)
    {
        auto graphics =
            reinterpret_cast<PluginManagement::IGraphicsPluginProvider*>(graphicsPluginProvider)->shared_from_this();
        auto window =
            reinterpret_cast<PluginManagement::IWindowingPluginProvider*>(windowingPluginProvider)->shared_from_this();
        auto resources =
            reinterpret_cast<PluginManagement::IResourceManagementPluginProvider*>(resourceManagementPluginProvider)
                ->shared_from_this();

        _defaultRenderingSystemCollection.push_back(
            std::make_shared<DefaultRenderingSystem>(graphics, window, resources));

        return reinterpret_cast<NrtDefaultRenderingSystemHandle>(_defaultRenderingSystemCollection.back().get());
    }

    NrtResult Nrt_DefaultRenderingSystem_Destroy(NrtDefaultRenderingSystemHandle system)
    {
        if (system == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto toDelete = reinterpret_cast<DefaultRenderingSystem*>(system)->shared_from_this();
        if (std::find(_defaultRenderingSystemCollection.begin(), _defaultRenderingSystemCollection.end(), toDelete) ==
            _defaultRenderingSystemCollection.end())
        {
            Nrt_setErrMsgIsAlreadyDeletedOrRemovedInternal();
            return NRT_FAILURE_ALREADY_DELETED_OR_REMOVED;
        }
        _defaultRenderingSystemCollection.remove(toDelete);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_DefaultRenderingSystem_Update(NrtDefaultRenderingSystemHandle system,
                                                NrtTimestamp delta,
                                                NrtCatalogueHandle catalogue)
    {
        if (system == nullptr || catalogue == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto cppSystem = reinterpret_cast<DefaultRenderingSystem*>(system);
        auto cppDelta = Timing::Timestamp(delta);
        auto cppCatalogue = reinterpret_cast<Ecs::Catalogue*>(catalogue);

        cppSystem->Update(cppDelta, *cppCatalogue);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_DefaultRenderingSystem_GetOrLoadTexture(NrtDefaultRenderingSystemHandle system,
                                                          const char* spriteName,
                                                          NrtTextureInfoFutureResultHandle* outputResult)
    {
        if (system == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputResult == nullptr || spriteName == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto spriteString = std::string(spriteName);
        auto cppSystem = reinterpret_cast<DefaultRenderingSystem*>(system);
        auto newResult = new FutureResult<TextureInfo>(Threading::MakeConcurrentShared<TextureInfo>(), TextureInfo{});

        *newResult = cppSystem->GetOrLoadTexture(spriteString);
        *outputResult = reinterpret_cast<NrtTextureInfoFutureResultHandle>(newResult);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_DefaultRenderingSystem_GetExistingTextureBasedOnId(NrtDefaultRenderingSystemHandle system,
                                                                     NrtAtom ecsId,
                                                                     NrtTextureInfoThreadedPtrHandle* outputResult)
    {
        if (system == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputResult == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto cppSystem = reinterpret_cast<DefaultRenderingSystem*>(system);
        auto newConcurrent = Threading::MakeConcurrentShared<TextureInfo>();

        newConcurrent = cppSystem->GetExistingTextureBasedOnId(ecsId);
        *outputResult = reinterpret_cast<NrtTextureInfoThreadedPtrHandle>(&newConcurrent);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_DefaultRenderingSystem_LoadVertexDataRawUntyped(NrtDefaultRenderingSystemHandle system,
                                                                  const char* vertexDataName,
                                                                  void* data,
                                                                  size_t dataTypeSize,
                                                                  size_t dataLength,
                                                                  NrtVertexInfoFutureResultHandle* outputResult)
    {
        if (system == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputResult == nullptr || vertexDataName == nullptr || data == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto cppSystem = reinterpret_cast<DefaultRenderingSystem*>(system);
        auto cppVertexDataName = std::string(vertexDataName);
        auto newResult = new FutureResult<VertexInfo>(Threading::MakeConcurrentShared<VertexInfo>(), VertexInfo{});

        *newResult = cppSystem->LoadVertexDataRawUntyped(cppVertexDataName, data, dataTypeSize, dataLength);
        *outputResult = reinterpret_cast<NrtVertexInfoFutureResultHandle>(newResult);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_DefaultRenderingSystem_GetExistingVertexDataBasedOnName(NrtDefaultRenderingSystemHandle system,
                                                                          const char* vertexDataName,
                                                                          NrtVertexInfoThreadedPtrHandle* outputResult)
    {
        if (system == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputResult == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto cppSystem = reinterpret_cast<DefaultRenderingSystem*>(system);
        auto cppVertexDataName = std::string(vertexDataName);
        auto newConcurrent = Threading::MakeConcurrentShared<VertexInfo>();

        newConcurrent = cppSystem->GetExistingVertexDataBasedOnName(cppVertexDataName);
        *outputResult = reinterpret_cast<NrtVertexInfoThreadedPtrHandle>(&newConcurrent);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_DefaultRenderingSystem_GetExistingVertexDataBasedOnId(NrtDefaultRenderingSystemHandle system,
                                                                        NrtAtom ecsId,
                                                                        NrtVertexInfoThreadedPtrHandle* outputResult)
    {
        if (system == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputResult == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto cppSystem = reinterpret_cast<DefaultRenderingSystem*>(system);
        auto newConcurrent = Threading::MakeConcurrentShared<VertexInfo>();

        newConcurrent = cppSystem->GetExistingVertexDataBasedOnId(ecsId);
        *outputResult = reinterpret_cast<NrtVertexInfoThreadedPtrHandle>(&newConcurrent);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_DefaultRenderingSystem_GetExistingPipelineInfoBasedOnId(
        NrtDefaultRenderingSystemHandle system,
        NrtAtom ecsId,
        NrtGraphicsPipelineInfoThreadedPtrHandle* outputResult)
    {
        if (system == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputResult == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto cppSystem = reinterpret_cast<DefaultRenderingSystem*>(system);
        auto newConcurrent = Threading::MakeConcurrentShared<GraphicsPipelineInfo>();

        newConcurrent = cppSystem->GetExistingPipelineInfoBasedOnId(ecsId);
        *outputResult = reinterpret_cast<NrtGraphicsPipelineInfoThreadedPtrHandle>(&newConcurrent);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_DefaultRenderingSystem_RegisterPipeline(
        NrtDefaultRenderingSystemHandle system,
        const char* pipelineName,
        NrtGraphicsPipelinePtrHandle pipeline,
        NrtGraphicsResourceMemoryVectorHandle customConstantBufferRegions,
        NrtBool useEcsTransforms,
        NrtGraphicsPipelineInfoThreadedPtrHandle* outputResult)
    {
        if (system == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputResult == nullptr || pipelineName == nullptr || pipeline == nullptr ||
            customConstantBufferRegions == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto cppSystem = reinterpret_cast<DefaultRenderingSystem*>(system);
        auto cppPipelineName = std::string(pipelineName);
        auto cppPipeline = std::dynamic_pointer_cast<Graphics::GraphicsPipeline>(
            reinterpret_cast<Graphics::GraphicsPipeline*>(pipeline)->shared_from_this());
        auto cppConstantBuffer =
            reinterpret_cast<std::vector<Graphics::GraphicsMemoryRegion<Graphics::GraphicsResource>>*>(
                customConstantBufferRegions);
        auto newConcurrent = Threading::MakeConcurrentShared<GraphicsPipelineInfo>();

        newConcurrent = cppSystem->RegisterPipeline(cppPipelineName, cppPipeline, *cppConstantBuffer, useEcsTransforms);
        *outputResult = reinterpret_cast<NrtGraphicsPipelineInfoThreadedPtrHandle>(&newConcurrent);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_DefaultRenderingSystem_AttachSpriteRenderingToEntity(NrtDefaultRenderingSystemHandle system,
                                                                       NrtEntityId entity,
                                                                       NrtTextureInfoThreadedPtrHandle texture,
                                                                       NrtCatalogueHandle catalogue)
    {
        if (system == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (texture == nullptr || catalogue == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto cppSystem = reinterpret_cast<DefaultRenderingSystem*>(system);
        auto cppTextureInfo = reinterpret_cast<Threading::ConcurrentSharedPtr<TextureInfo>*>(texture);
        auto cppCatalogue = reinterpret_cast<Ecs::Catalogue*>(catalogue);

        cppSystem->AttachSpriteRenderingToEntity(entity, *cppTextureInfo, *cppCatalogue);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_DefaultRenderingSystem_CreateSpriteEntity(NrtDefaultRenderingSystemHandle system,
                                                            NrtTextureInfoThreadedPtrHandle texture,
                                                            NrtCatalogueHandle catalogue,
                                                            NrtEntityId* outputResult)
    {
        if (system == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (texture == nullptr || catalogue == nullptr || outputResult == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto cppSystem = reinterpret_cast<DefaultRenderingSystem*>(system);
        auto cppTextureInfo = reinterpret_cast<Threading::ConcurrentSharedPtr<TextureInfo>*>(texture);
        auto cppCatalogue = reinterpret_cast<Ecs::Catalogue*>(catalogue);

        auto newEntity = cppSystem->CreateSpriteEntity(*cppTextureInfo, *cppCatalogue);
        *outputResult = *reinterpret_cast<NrtEntityId*>(&newEntity);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_DefaultRenderingSystem_CreateSpriteEntityOutsideOfSystem(NrtDefaultRenderingSystemHandle system,
                                                                           NrtTextureInfoThreadedPtrHandle texture,
                                                                           NrtSystemSchedulerHandle scheduler,
                                                                           NrtEntityId* outputResult)
    {
        if (system == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (texture == nullptr || scheduler == nullptr || outputResult == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto cppSystem = reinterpret_cast<DefaultRenderingSystem*>(system);
        auto cppTextureInfo = reinterpret_cast<Threading::ConcurrentSharedPtr<TextureInfo>*>(texture);
        auto cppScheduler = reinterpret_cast<Ecs::SystemScheduler*>(scheduler);

        auto newEntity = cppSystem->CreateSpriteEntityOutsideOfSystem(*cppTextureInfo, *cppScheduler);
        *outputResult = *reinterpret_cast<NrtEntityId*>(&newEntity);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_DefaultRenderingSystem_ForceVertexTextureFutureResolution(NrtDefaultRenderingSystemHandle system)
    {
        if (system == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto cppSystem = reinterpret_cast<DefaultRenderingSystem*>(system);
        cppSystem->ForceVertexTextureFutureResolution();
        return NRT_SUCCESS;
    }

#ifdef __cplusplus
}
#endif
