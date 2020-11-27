// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_SCENEGRAPH_QuadTreeNode_H
#define NOVELRT_INTEROP_SCENEGRAPH_QuadTreeNode_H

#include <stdint.h>
#include "../NrtInteropUtils.h"
#include "NrtSceneGraphTypedefs.h"

#ifdef __cplusplus
extern "C" {
#endif

NrtResult Nrt_QuadTreeNode_create(NrtQuadTreeScenePointArray points, NrtQuadTreeNode* outputPoint);
NrtResult Nrt_QuadTreeNode_getTopLeft(NrtQuadTreeNode node, NrtQuadTreeScenePoint* outputPoint);
NrtResult Nrt_QuadTreeNode_getTopRight(NrtQuadTreeNode node, NrtQuadTreeScenePoint* outputPoint);
NrtResult Nrt_QuadTreeNode_getBottomLeft(NrtQuadTreeNode node, NrtQuadTreeScenePoint* outputPoint);
NrtResult Nrt_QuadTreeNode_getBottomRight(NrtQuadTreeNode node, NrtQuadTreeScenePoint* outputPoint);

NrtResult Nrt_QuadTreeScenePointArray_create(NrtQuadTreeScenePoint pointOne, NrtQuadTreeScenePoint pointTwo,
    NrtQuadTreeScenePoint pointThree, NrtQuadTreeScenePoint pointFour,
    NrtQuadTreeScenePointArray* outputArray);

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_INTEROP_SCENEGRAPH_QuadTreeNode_H
