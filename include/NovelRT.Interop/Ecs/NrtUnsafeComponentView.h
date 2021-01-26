// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_NRTCOMPONENTVIEW_H
#define NOVELRT_NRTCOMPONENTVIEW_H

#include "../NrtInteropUtils.h"
#include "NrtEcsUtils.h"
#include "NrtComponentBufferMemoryContainer.h"

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct UnsafeComponentViewHandle* NrtUnsafeComponentView;

    NrtUnsafeComponentView Nrt_UnsafeComponentView_Create(size_t poolId, NrtComponentBufferMemoryContainer container);

    NrtResult Nrt_UnsafeComponentView_PushComponentUpdateInstruction(NrtUnsafeComponentView componentView,
                                                                     void* instructionData);

    NrtResult Nrt_UnsafeComponentView_RemoveComponent(NrtEntityId entity);

    NrtResult Nrt_UnsafeComponentView_GetComponent(NrtUnsafeComponentView componentView,
                                                   NrtEntityId entity,
                                                   NrtComponentBufferMemoryContainer_ImmutableDataView* outputResult);

    NrtComponentBufferMemoryContainer_ImmutableDataView Nrt_UnsafeComponentView_GetComponentUnsafe(
        NrtUnsafeComponentView componentView,
        NrtEntityId entity);

    size_t Nrt_UnsafeComponentview_GetImmutableDataLength(NrtUnsafeComponentView componentView);

    // clang-format off

    NrtSparseSetMemoryContainer_ConstIterator Nrt_UnsafeComponentView_begin(NrtUnsafeComponentView componentView);

    NrtSparseSetMemoryContainer_ConstIterator Nrt_UnsafeComponentView_end(NrtUnsafeComponentView componentView);

    // clang-format on

#ifdef __cplusplus
};
#endif

#endif // !NOVELRT_NRTCOMPONENTVIEW_H
