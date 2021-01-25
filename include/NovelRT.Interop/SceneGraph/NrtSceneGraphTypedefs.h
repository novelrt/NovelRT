// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_SCENEGRAPH_TYPEDEFS_H
#define NOVELRT_INTEROP_SCENEGRAPH_TYPEDEFS_H

#include "../NrtInteropUtils.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

    // NrtQuadTreeScenePoint
    typedef struct QuadTreeScenePointHandle* NrtQuadTreeScenePoint;

    // NrtQuadTreeNode
    typedef struct QuadTreeNodeHandle* NrtQuadTreeNode;
    typedef struct QuadTreeScenePointArray* NrtQuadTreeScenePointArray;

    // NrtScene
    typedef struct SceneHandle* NrtScene;

    // NrtSceneNode
    typedef struct SceneNodeHandle* NrtSceneNode;
    typedef struct StdSet_SceneNode* NrtSceneNodeSet;
    typedef struct BreadthFirstIterator* NrtSceneNodeBreadthFirstIterator;
    typedef struct DepthFirstIterator* NrtSceneNodeDepthFirstIterator;

    // NrtSceneNodeBreadthFirstIterator
    typedef struct BreadthFirstIterator* NrtSceneNodeBreadthFirstIterator;

    // NrtSceneNodeDepthFirstIterator
    typedef struct DepthFirstIterator* NrtSceneNodeDepthFirstIterator;

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_SCENEGRAPH_TYPEDEFS_H
