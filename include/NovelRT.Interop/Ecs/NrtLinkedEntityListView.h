// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_ECS_LINKEDENTITYLISTVIEW_H
#define NOVELRT_INTEROP_ECS_LINKEDENTITYLISTVIEW_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif
    // class ConstIterator
    NrtConstIteratorHandle Nrt_ConstIterator_create(NrtEntityId currentEntityNode, NrtCatalogue catalogue);
    NrtResult Nrt_ConstIterator_destroy(NrtConstIteratorHandle iterator);
    NrtEntityId Nrt_ConstIterator_PtrAccess_Operator(NrtConstIteratorHandle iterator);
    NrtConstIteratorHandle Nrt_ConstIterator_Increment_Operator(NrtConstIteratorHandle iterator);
    NrtConstIteratorHandle Nrt_ConstIterator_Decrement_Operator(NrtConstIteratorHandle iterator);
    NrtBool Nrt_ConstIterator_Equals_Operator(NrtConstIteratorHandle lhs, NrtConstIteratorHandle rhs);
    NrtBool Nrt_ConstIterator_NotEquals_Operator(NrtConstIteratorHandle lhs, NrtConstIteratorHandle rhs);

    NrtResult Nrt_ConstIterator_GetCurrentEntityNode(NrtConstIteratorHandle iterator, NrtEntityId* Node);
    NrtResult Nrt_ConstIterator_GetListNode(NrtConstIteratorHandle iterator, NrtLinkedEntityListNodeComponent* list);

    // class LinkedEntityListView
    NrtLinkedEntityListViewHandle Nrt_LinkedEntityListView_create(NrtEntityId node, NrtCatalogue catalogue);
    NrtResult Nrt_LinkedEntityListView_Indexing_Operator(NrtLinkedEntityListViewHandle list, size_t index, NrtEntityId* element_id);
    NrtResult Nrt_LinkedEntityListView_destroy(NrtLinkedEntityListViewHandle list);

    NrtResult Nrt_LinkedEntityListView_begin(NrtLinkedEntityListViewHandle list, NrtConstIterator* begining);
    NrtResult Nrt_LinkedEntityListView_end(NrtLinkedEntityListViewHandle list, NrtConstIterator* end);
    NrtBool Nrt_LinkedEntityListView_ContainsNode(NrtLinkedEntityListViewHandle list, NrtEntityId target);
    NrtResult Nrt_LinkedEntityListView_GetLength(NrtLinkedEntityListViewHandle list, size_t* length);

    NrtResult Nrt_LinkedEntityListView_AddInsertBeforeIndexInstruction(
        NrtLinkedEntityListViewHandle list, size_t index, NrtEntityId newNode);
    NrtResult Nrt_LinkedEntityListView_AddInsertAfterIndexInstruction(
        NrtLinkedEntityListViewHandle list, size_t index, NrtEntityId newNode);

    NrtBool Nrt_LinkedEntityListView_TryGetComposedDiffInstruction(
        NrtLinkedEntityListViewHandle list,
        NrtEntityId node,
        NrtLinkedEntityListNodeComponent* outNodeComponent);
    NrtBool Nrt_LinkedEntityListView_TryGetComposedDiffInstructionAtBeginning(
        NrtLinkedEntityListViewHandle list,
        NrtLinkedEntityListNodeComponent* outNodeComponent);
    NrtBool Nrt_LinkedEntityListView_TryGetComposedDiffInstructionAtEnd(
        NrtLinkedEntityListViewHandle list,
        NrtLinkedEntityListNodeComponent* outNodeComponent);
    NrtBool Nrt_LinkedEntityListView_TryGetNewNodeAtBeginning(
        NrtLinkedEntityListViewHandle list,
        NrtEntityId* outEntityId);
    NrtBool Nrt_LinkedEntityListView_TryGetNewNodeAtEnd(
        NrtLinkedEntityListViewHandle list,
        NrtEntityId* outEntityId);
    NrtResult Nrt_LinkedEntityListView_GetOriginalBeginning(
        NrtLinkedEntityListViewHandle list,
        NrtEntityId* outEntityId);
    NrtResult Nrt_LinkedEntityListView_GetOriginalEnd(
        NrtLinkedEntityListViewHandle list,
        NrtEntityId* outEntityId);

    NrtResult Nrt_LinkedEntityListView_AddInsertAtBackInstruction(
        NrtLinkedEntityListViewHandle list,
        NrtEntityId newNode);
    NrtResult Nrt_LinkedEntityListView_AddInsertAtFrontInstruction(
        NrtLinkedEntityListViewHandle list,
        NrtEntityId newNode);
    NrtResult Nrt_LinkedEntityListView_AddRemoveNodeInstruction(
        NrtLinkedEntityListViewHandle list,
        NrtEntityId nodeToRemove);
    NrtResult Nrt_LinkedEntityListView_Commit(NrtLinkedEntityListViewHandle list);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ECS_LINKEDENTITYLISTVIEW_H
