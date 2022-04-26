// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_ECS_UNSAFECOMPONENTVIEW_H
#define NOVELRT_INTEROP_ECS_UNSAFECOMPONENTVIEW_H

#include <NovelRT.Interop/NrtTypedefs.h>

#ifdef __cplusplus
extern "C"
{
#endif

    NrtUnsafeComponentViewHandle Nrt_UnsafeComponentView_Create(size_t poolId,
                                                                NrtComponentBufferMemoryContainerHandle container);

    NrtResult Nrt_UnsafeComponentView_PushComponentUpdateInstruction(NrtUnsafeComponentViewHandle componentView,
                                                                     NrtEntityId entity,
                                                                     void* instructionData);

    NrtResult Nrt_UnsafeComponentView_RemoveComponent(NrtUnsafeComponentViewHandle componentView, NrtEntityId entity);

    NrtResult Nrt_UnsafeComponentView_GetComponent(
        NrtUnsafeComponentViewHandle componentView,
        NrtEntityId entity,
        NrtComponentBufferMemoryContainer_ImmutableDataViewHandle* outputResult);

    NrtComponentBufferMemoryContainer_ImmutableDataViewHandle Nrt_UnsafeComponentView_GetComponentUnsafe(
        NrtUnsafeComponentViewHandle componentView,
        NrtEntityId entity);

    size_t Nrt_UnsafeComponentView_GetImmutableDataLength(NrtUnsafeComponentViewHandle componentView);

    NrtSparseSetMemoryContainer_ConstIteratorHandle Nrt_UnsafeComponentView_begin(
        NrtUnsafeComponentViewHandle componentView);

    NrtSparseSetMemoryContainer_ConstIteratorHandle Nrt_UnsafeComponentView_end(
        NrtUnsafeComponentViewHandle componentView);

    NrtResult Nrt_UnsafeComponentView_Destroy(NrtUnsafeComponentViewHandle componentView);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ECS_UNSAFECOMPONENTVIEW_H
