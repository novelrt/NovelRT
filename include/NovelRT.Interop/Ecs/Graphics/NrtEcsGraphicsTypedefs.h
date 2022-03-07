// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_ECS_GRAPHICS_TYPEDEFS_H
#define NOVELRT_INTEROP_ECS_GRAPHICS_TYPEDEFS_H

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct NrtGraphicsPipelineThreadedPtr* NrtGraphicsPipelineThreadedPtrHandle;
    typedef struct NrtGraphicsPipelinePtr* NrtGraphicsPipelinePtrHandle;

    typedef struct NrtGPUCustomConstantBuffers* NrtGPUCustomConstantBuffersHandle;

    typedef struct NrtGraphicsResourceRegionMemory* NrtGraphicsResourceMemoryRegionHandle;
    typedef struct NrtGraphicsResourceMemoryMap* NrtGraphicsResourceMemoryMapHandle;
    typedef struct NrtGraphicsResourceMemoryVector* NrtGraphicsResourceMemoryVectorHandle;

    typedef struct
    {
        NrtGraphicsPipelineThreadedPtrHandle gpuPipeline;
        NrtGPUCustomConstantBuffersHandle gpuCustomConstantBuffers;
        NrtBool useEcsTransforms;
        char* pipelineName;
        NrtAtom ecsId;
    } NrtGraphicsPipelineInfo;

    typedef struct NrtGraphicsPipelineInfoThreadedPtr* NrtGraphicsPipelineInfoThreadedPtrHandle;

    typedef struct
    {
        NrtGraphicsResourceMemoryRegionHandle gpuVertexRegion;
        char* vertexInfoName;
        NrtAtom ecsId;
        void* stagingPtr;
        size_t sizeOfVert;
        size_t stagingPtrLength;
        uint32_t stride;
    } NrtVertexInfo;

    typedef struct NrtVertexInfoThreadedPtr* NrtVertexInfoThreadedPtrHandle;
    typedef struct NrtVertexInfoFutureResult* NrtVertexInfoFutureResultHandle;

    typedef struct
    {
        NrtGraphicsResourceMemoryRegionHandle gpuTextureRegion;
        char* textureName;
        uint32_t width;
        uint32_t height;
        NrtAtom ecsId;
    } NrtTextureInfo;

    typedef struct NrtTextureInfoThreadedPtr* NrtTextureInfoThreadedPtrHandle;
    typedef struct NrtTextureInfoFutureResult* NrtTextureInfoFutureResultHandle;

    typedef struct NrtEntityIdPtr* NrtEntityIdPtrHandle;

    typedef struct NrtDefaultRenderingSystem* NrtDefaultRenderingSystemHandle;
    typedef struct
    {
        NrtEntityId entityId;
        NrtTextureInfoThreadedPtrHandle texturePtr;
        NrtVertexInfoThreadedPtrHandle meshPtr;
        NrtGraphicsPipelineInfoThreadedPtrHandle pipelinePtr;
    } NrtAttachRenderToExistingEntityRequestInfo;

    typedef struct
    {
        NrtGraphicsResourceMemoryRegionHandle gpuConstantBufferRegion;
    } NrtConstantBufferInfo;

    typedef struct
    {
        NrtEntityIdPtrHandle entityId;
        NrtTextureInfoThreadedPtrHandle texturePtr;
        NrtVertexInfoThreadedPtrHandle meshPtr;
        NrtGraphicsPipelineInfoThreadedPtrHandle pipelinePtr;
    } NrtCreateRenderEntityRequestInfo;

    typedef struct
    {
        NrtAtom vertexDataId;
        NrtAtom textureId;
        NrtAtom pipelineId;
        NrtAtom primitiveInfoId;
        bool markedForDeletion;
    } NrtRenderComponent;

    typedef struct
    {
        NrtGeoVector3F Position;
        NrtGeoVector2F UV;
    } NrtTexturedVertexTest;

    typedef struct
    {
        NrtAtom ecsVertexDataId;
        NrtAtom ecsTextureId;
        NrtAtom ecsPipelineId;
        NrtGraphicsResourceMemoryMapHandle gpuTransformConstantBufferRegions;
    } NrtGraphicsPrimitiveInfo;

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ECS_GRAPHICS_TYPEDEFS_H
