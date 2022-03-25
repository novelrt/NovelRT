// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Ecs/NrtEntityGraphView.h>
#include <NovelRT/Ecs/Ecs.h>

#ifdef __cplusplus
extern "C"
{
#endif

    NrtEntityGraphViewHandle Nrt_EntityGraphView_create(
        NrtCatalogue catalogue,
        NrtEntityId owningEntity,
        NrtEntityGraphComponent component);
    NrtResult Nrt_EntityGraphView_destroy();

    NrtResult Nrt_EntityGraphView_GetRawEntityId(NrtEntityGraphViewHandle graphView, NrtEntityId* outEntity);
    NrtBool Nrt_EntityGraphView_HasParent(NrtEntityGraphViewHandle graphView);
    NrtBool Nrt_EntityGraphView_HasChildren(NrtEntityGraphViewHandle graphView);
    NrtResult Nrt_EntityGraphView_GetRawComponentData(NrtEntityGraphViewHandle* graphView);
    NrtResult Nrt_EntityGraphView_GetRawComponentData(NrtEntityGraphViewHandle* graphView);
    NrtResult GetOriginalChildren(NrtEntityGraphViewHandle graphView, NrtEntityGraphViewVectorHandle* children);
    NrtResult AddInsertChildInstruction(NrtEntityGraphViewHandle* graphView, NrtEntityId newChildEntity);
    NrtResult AddRemoveChildInstruction(NrtEntityGraphViewHandle* graphView, NrtEntityId childToRemove);
    NrtResult Commit(NrtEntityGraphViewHandle graphView);

#ifdef __cplusplus
}
#endif
