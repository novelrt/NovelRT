// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_SCENEGRAPH_RENDEROBJECTNODE_H
#define NOVELRT_INTEROP_SCENEGRAPH_RENDEROBJECTNODE_H

#include <stdint.h>
#include "../NrtInteropUtils.h"
#include "../Graphics/NrtGraphicsTypedefs.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct RenderObjectNodeHandle* NovelRTRenderObjectNode;

NrtResult Nrt_RenderObjectNode_create(NrtRenderObject object, NovelRTRenderObjectNode* outputNode);
NrtResult Nrt_RenderObjectNode_getRenderObject(NovelRTRenderObjectNode node, NrtRenderObject* outputObject);
NrtResult Nrt_RenderObjectNode_delete(NovelRTRenderObjectNode node);

#ifdef __cplusplus
}
#endif

#endif //!NOVELRT_INTEROP_SCENEGRAPH_RENDEROBJECTNODE_H
