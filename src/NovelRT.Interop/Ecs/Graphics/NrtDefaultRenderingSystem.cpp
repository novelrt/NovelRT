// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Ecs/Graphics/NrtDefaultRenderingSystem.h>
#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT/Ecs/Ecs.h>

using namespace NovelRT;
using namespace Threading;
using namespace Ecs::Graphics;
using namespace PluginManagement;

std::list<std::shared_ptr<DefaultRenderingSystem>> _DefaultRenderingSystemCollection;

#ifdef __cplusplus
extern "C"
{
#endif

    NrtDefaultRenderingSystemHandle Nrt_DefaultRenderingSystem_create(
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

        _DefaultRenderingSystemCollection.push_back(
            std::make_shared<DefaultRenderingSystem>(graphics, window, resources));

        return reinterpret_cast<NrtDefaultRenderingSystemHandle>(_DefaultRenderingSystemCollection.back().get());
    }

    NrtResult Nrt_DefaultRenderingSystem_destroy(NrtDefaultRenderingSystemHandle system)
    {
        if (system == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto to_delete = reinterpret_cast<DefaultRenderingSystem*>(system)->shared_from_this();
        if (std::find(_DefaultRenderingSystemCollection.begin(), _DefaultRenderingSystemCollection.end(), to_delete) ==
            _DefaultRenderingSystemCollection.end())
        {
            Nrt_setErrMsgIsAlreadyDeletedOrRemovedInternal();
            return NRT_FAILURE_ALREADY_DELETED_OR_REMOVED;
        }
        _DefaultRenderingSystemCollection.remove(to_delete);
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

        auto CppSystem = reinterpret_cast<DefaultRenderingSystem*>(system);
        auto CppDelta = Timing::Timestamp(delta);
        auto CppCatalogue = reinterpret_cast<Ecs::Catalogue*>(catalogue);

        CppSystem->Update(CppDelta, *CppCatalogue);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_DefaultRenderingSystem_GetOrLoadTexture(NrtDefaultRenderingSystemHandle system,
                                                          const char* spriteName,
                                                          NrtTextureInfoFutureResultHandle* output)
    {
        if (system == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (output == nullptr || spriteName == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        std::string spriteString = spriteName;
        auto CppSystem = reinterpret_cast<DefaultRenderingSystem*>(system);
        auto NewResult = new FutureResult<TextureInfo>(Threading::MakeConcurrentShared<TextureInfo>(), TextureInfo{});

        *NewResult = CppSystem->GetOrLoadTexture(spriteString);
        *output = reinterpret_cast<NrtTextureInfoFutureResultHandle>(NewResult);
        return NRT_SUCCESS;

    }

    NrtResult Nrt_DefaultRenderingSystem_GetExistingTextureBasedOnId(NrtDefaultRenderingSystemHandle system,
                                                                     NrtAtom ecsId,
                                                                     NrtTextureInfoThreadedPtrHandle* output)
    {
        if (system == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (output == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto CppSystem = reinterpret_cast<DefaultRenderingSystem*>(system);
        auto NewConcurrent = Threading::MakeConcurrentShared<TextureInfo>();

        NewConcurrent = CppSystem->GetExistingTextureBasedOnId(ecsId);
        *output = reinterpret_cast<NrtTextureInfoThreadedPtrHandle>(&NewConcurrent);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_DefaultRenderingSystem_LoadVertexDataRawUntyped(NrtDefaultRenderingSystemHandle system,
                                                                  const char* vertexDataName,
                                                                  void* data,
                                                                  size_t dataTypeSize,
                                                                  size_t dataLength,
                                                                  NrtVertexInfoFutureResultHandle* output)
    {
        if (system == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (output == nullptr || vertexDataName == nullptr || data == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto CppSystem = reinterpret_cast<DefaultRenderingSystem*>(system);
        std::string CppVertexDataName = vertexDataName;
        auto NewResult = new FutureResult<VertexInfo>(Threading::MakeConcurrentShared<VertexInfo>(), VertexInfo{});

        *NewResult = CppSystem->LoadVertexDataRawUntyped(CppVertexDataName, data, dataTypeSize, dataLength);
        *output = reinterpret_cast<NrtVertexInfoFutureResultHandle>(NewResult);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_DefaultRenderingSystem_GetExistingVertexDataBasedOnName(NrtDefaultRenderingSystemHandle system,
                                                                          const char* vertexDataName,
                                                                          NrtVertexInfoThreadedPtrHandle* output)
    {
        if (system == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (output == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto CppSystem = reinterpret_cast<DefaultRenderingSystem*>(system);
        std::string CppVertexDataName = vertexDataName;
        auto NewConcurrent = Threading::MakeConcurrentShared<VertexInfo>();

        NewConcurrent = CppSystem->GetExistingVertexDataBasedOnName(CppVertexDataName);
        *output = reinterpret_cast<NrtVertexInfoThreadedPtrHandle>(&NewConcurrent);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_DefaultRenderingSystem_GetExistingVertexDataBasedOnId(NrtDefaultRenderingSystemHandle system,
                                                                        NrtAtom ecsId,
                                                                        NrtVertexInfoThreadedPtrHandle* output)
    {
        if (system == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (output == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto CppSystem = reinterpret_cast<DefaultRenderingSystem*>(system);
        auto NewConcurrent = Threading::MakeConcurrentShared<VertexInfo>();

        NewConcurrent = CppSystem->GetExistingVertexDataBasedOnId(ecsId);
        *output = reinterpret_cast<NrtVertexInfoThreadedPtrHandle>(&NewConcurrent);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_DefaultRenderingSystem_GetExistingPipelineInfoBasedOnId(
        NrtDefaultRenderingSystemHandle system,
        NrtAtom ecsId,
        NrtGraphicsPipelineInfoThreadedPtrHandle* output)
    {
        if (system == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (output == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto CppSystem = reinterpret_cast<DefaultRenderingSystem*>(system);
        auto NewConcurrent = Threading::MakeConcurrentShared<GraphicsPipelineInfo>();

        NewConcurrent = CppSystem->GetExistingPipelineInfoBasedOnId(ecsId);
        *output = reinterpret_cast<NrtGraphicsPipelineInfoThreadedPtrHandle>(&NewConcurrent);
        return NRT_SUCCESS;
    }
    NrtResult Nrt_DefaultRenderingSystem_RegisterPipeline(
        NrtDefaultRenderingSystemHandle system,
        const char* pipelineName,
        NrtGraphicsPipelinePtrHandle pipeline,
        NrtGraphicsResourceMemoryVectorHandle customConstantBufferRegions,
        NrtBool useEcsTransforms,
        NrtGraphicsPipelineInfoThreadedPtrHandle *output)
    {
        if (system == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (output == nullptr || pipelineName == nullptr || pipeline == nullptr ||
            customConstantBufferRegions == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto CppSystem = reinterpret_cast<DefaultRenderingSystem*>(system);
        std::string CppPipelineName = pipelineName;
        auto CppPipeline = std::dynamic_pointer_cast<Graphics::GraphicsPipeline>(
            reinterpret_cast<Graphics::GraphicsPipeline*>(pipeline)->shared_from_this());
        auto CppConstantBuffer =
            reinterpret_cast<std::vector<Graphics::GraphicsMemoryRegion<Graphics::GraphicsResource>>*>(
                customConstantBufferRegions);
        auto NewConcurrent = Threading::MakeConcurrentShared<GraphicsPipelineInfo>();

        NewConcurrent = CppSystem->RegisterPipeline(CppPipelineName, CppPipeline, *CppConstantBuffer, useEcsTransforms);
        *output = reinterpret_cast<NrtGraphicsPipelineInfoThreadedPtrHandle>(&NewConcurrent);
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

        auto CppSystem = reinterpret_cast<DefaultRenderingSystem*>(system);
        auto CppTextureInfo = reinterpret_cast<Threading::ConcurrentSharedPtr<TextureInfo>*>(texture);
        auto CppCatalogue = reinterpret_cast<Ecs::Catalogue*>(catalogue);

        CppSystem->AttachSpriteRenderingToEntity(entity, *CppTextureInfo, *CppCatalogue);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_DefaultRenderingSystem_CreateSpriteEntity(NrtDefaultRenderingSystemHandle system,
                                                            NrtTextureInfoThreadedPtrHandle texture,
                                                            NrtCatalogueHandle catalogue,
                                                            NrtEntityId* output)
    {
        if (system == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (texture == nullptr || catalogue == nullptr || output == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto CppSystem = reinterpret_cast<DefaultRenderingSystem*>(system);
        auto CppTextureInfo = reinterpret_cast<Threading::ConcurrentSharedPtr<TextureInfo>*>(texture);
        auto CppCatalogue = reinterpret_cast<Ecs::Catalogue*>(catalogue);

        auto NewEntity = CppSystem->CreateSpriteEntity(*CppTextureInfo, *CppCatalogue);
        *output = *reinterpret_cast<NrtEntityId*>(&NewEntity);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_DefaultRenderingSystem_CreateSpriteEntityOutsideOfSystem(NrtDefaultRenderingSystemHandle system,
                                                                           NrtTextureInfoThreadedPtrHandle texture,
                                                                           NrtSystemSchedulerHandle scheduler,
                                                                           NrtEntityId* output)
    {
        if (system == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (texture == nullptr || scheduler == nullptr || output == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto CppSystem = reinterpret_cast<DefaultRenderingSystem*>(system);
        auto CppTextureInfo = reinterpret_cast<Threading::ConcurrentSharedPtr<TextureInfo>*>(texture);
        auto CppScheduler = reinterpret_cast<Ecs::SystemScheduler*>(scheduler);

        auto NewEntity = CppSystem->CreateSpriteEntityOutsideOfSystem(*CppTextureInfo, *CppScheduler);
        *output = *reinterpret_cast<NrtEntityId*>(&NewEntity);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_DefaultRenderingSystem_ForceVertexTextureFutureResolution(NrtDefaultRenderingSystemHandle system)
    {
        if (system == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto CppSystem = reinterpret_cast<DefaultRenderingSystem*>(system);
        CppSystem->ForceVertexTextureFutureResolution();
        return NRT_SUCCESS;
    }

#ifdef __cplusplus
}
#endif