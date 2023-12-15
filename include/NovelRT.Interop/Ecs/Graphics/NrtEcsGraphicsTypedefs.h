// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#ifndef NOVELRT_INTEROP_ECS_GRAPHICS_NRTECSGRAPHICSTYPEDEFS_H
#define NOVELRT_INTEROP_ECS_GRAPHICS_NRTECSGRAPHICSTYPEDEFS_H

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct NrtDefaultRenderingSystem* NrtDefaultRenderingSystemHandle;

    // Component types

    typedef struct {
        NrtAtom vertexDataId;
        NrtAtom textureId;
        NrtAtom pipelineId;
        NrtAtom primitiveInfoId;
        bool requiresCustomRendering;
        bool markedForDeletion;
    } NrtRenderComponent;

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ECS_GRAPHICS_NRTECSGRAPHICSTYPEDEFS_H
