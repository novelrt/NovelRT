// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include <stdint.h>

#ifndef NOVELRT_INTEROP_SCENEGRAPH_RenderObjectNode_H
#define NOVELRT_INTEROP_SCENEGRAPH_RenderObjectNode_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct RenderObjectNodeHandle* NovelRTRenderObjectNode;
#ifndef NOVELRT_INTEROP_GRAPHICS_GRAPHICSTYPEDEFS_H
typedef struct RenderObjectHandle* NovelRTRenderObject;
#endif

int32_t NovelRT_RenderObjectNode_create(NovelRTRenderObject object, NovelRTRenderObjectNode* outputNode);
int32_t NovelRT_RenderObjectNode_getRenderObject(NovelRTRenderObjectNode node, NovelRTRenderObject* outputObject);
int32_t NovelRT_RenderObjectNode_delete(NovelRTRenderObjectNode node);

#ifdef __cplusplus
}
#endif

#endif //NOVELRT_INTEROP_SCENEGRAPH_RenderObjectNode_H
