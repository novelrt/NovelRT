// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_SCENEGRAPH_RENDEROBJECTNODE_H
#define NOVELRT_INTEROP_SCENEGRAPH_RENDEROBJECTNODE_H

#include <stdint.h>
#include "../NrtInteropUtils.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct RenderObjectNodeHandle* NovelRTRenderObjectNode;
#ifndef NOVELRT_INTEROP_GRAPHICS_GRAPHICSTYPEDEFS_H
typedef struct RenderObjectHandle* NrtRenderObject;
#endif

NrtResult Nrt_RenderObjectNode_create(NrtRenderObject object, NovelRTRenderObjectNode* outputNode);
NrtResult Nrt_RenderObjectNode_getRenderObject(NovelRTRenderObjectNode node, NrtRenderObject* outputObject);
NrtResult Nrt_RenderObjectNode_delete(NovelRTRenderObjectNode node);

#ifdef __cplusplus
}
#endif

#endif //!NOVELRT_INTEROP_SCENEGRAPH_RENDEROBJECTNODE_H
