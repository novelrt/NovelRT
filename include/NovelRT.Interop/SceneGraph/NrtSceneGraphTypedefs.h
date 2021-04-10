// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_SCENEGRAPH_TYPEDEFS_H
#define NOVELRT_INTEROP_SCENEGRAPH_TYPEDEFS_H

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct NrtRenderObjectNode* NrtRenderObjectNodeHandle;
    typedef struct NrtQuadTreeNode* NrtQuadTreeNodeHandle;
    typedef struct NrtQuadTreeScenePoint* NrtQuadTreeScenePointHandle;
    typedef struct NrtQuadTreeScenePointArray* NrtQuadTreeScenePointArrayHandle;
    typedef struct NrtScene* NrtSceneHandle;
    typedef struct NrtSceneNode* NrtSceneNodeHandle;
    typedef struct NrtSceneNodeBreadthFirstIterator* NrtSceneNodeBreadthFirstIteratorHandle;
    typedef struct NrtSceneNodeDepthFirstIterator* NrtSceneNodeDepthFirstIteratorHandle;
    typedef struct NrtSceneNodeSet* NrtSceneNodeSetHandle;

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_SCENEGRAPH_TYPEDEFS_H
