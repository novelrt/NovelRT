// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_SCENEGRAPH_RENDEROBJECTNODE_H
#define NOVELRT_INTEROP_SCENEGRAPH_RENDEROBJECTNODE_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_RenderObjectNode_create(NrtRenderObjectHandle object, NrtRenderObjectNodeHandle* outputNode);
    NrtResult Nrt_RenderObjectNode_getRenderObject(NrtRenderObjectNodeHandle node, NrtRenderObjectHandle* outputObject);
    NrtResult Nrt_RenderObjectNode_delete(NrtRenderObjectNodeHandle node);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_SCENEGRAPH_RENDEROBJECTNODE_H
