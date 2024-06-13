// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_ECS_COMPONENTBUFFERMEMORYCONTAINER_H
#define NOVELRT_INTEROP_ECS_COMPONENTBUFFERMEMORYCONTAINER_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtComponentBufferMemoryContainerHandle Nrt_ComponentBufferMemoryContainer_Create(
        size_t poolSize,
        void* deleteInstructionState,
        size_t sizeOfDataTypeInBytes,
        NrtComponentUpdateFnPtr fnPtr,
        NrtComponentComparatorFnPtr comparatorPtr,
        const char* serialisedTypeName,
        void* context);

    void Nrt_ComponentBufferMemoryContainer_PrepContainerForFrame(NrtComponentBufferMemoryContainerHandle container,
                                                                  NrtEntityIdVectorHandle entitiesToDelete);

    NrtComponentBufferMemoryContainer_ImmutableDataViewHandle
    Nrt_ComponentBufferMemoryContainer_GetDeleteInstructionState(NrtComponentBufferMemoryContainerHandle container);

    NrtResult Nrt_ComponentBufferMemoryContainer_PushComponentUpdateInstruction(
        NrtComponentBufferMemoryContainerHandle container,
        size_t poolId,
        NrtEntityId entity,
        const void* componentData);

    NrtResult Nrt_ComponentBufferMemoryContainer_GetComponent(
        NrtComponentBufferMemoryContainerHandle container,
        NrtEntityId entity,
        NrtComponentBufferMemoryContainer_ImmutableDataViewHandle* outputResult);

    NrtComponentBufferMemoryContainer_ImmutableDataViewHandle Nrt_ComponentBufferMemoryContainer_GetComponentUnsafe(
        NrtComponentBufferMemoryContainerHandle container,
        NrtEntityId entity);

    NrtBool Nrt_ComponentBufferMemoryContainer_HasComponent(NrtComponentBufferMemoryContainerHandle container,
                                                            NrtEntityId entity);

    size_t Nrt_ComponentBufferMemoryContainer_GetImmutableDataLength(NrtComponentBufferMemoryContainerHandle container);

    NrtSparseSetMemoryContainer_ConstIteratorHandle Nrt_ComponentBufferMemoryContainer_Begin(
        NrtComponentBufferMemoryContainerHandle container);

    NrtSparseSetMemoryContainer_ConstIteratorHandle Nrt_ComponentBufferMemoryContainer_End(
        NrtComponentBufferMemoryContainerHandle container);

    NrtResult Nrt_ComponentBufferMemoryContainer_Destroy(NrtComponentBufferMemoryContainerHandle container);

    const void* Nrt_ComponentBufferMemoryContainer_ImmutableDataView_GetDataHandle(
        NrtComponentBufferMemoryContainer_ImmutableDataViewHandle view);

    NrtResult Nrt_ComponentBufferMemoryContainer_ImmutableDataView_Destroy(
        NrtComponentBufferMemoryContainer_ImmutableDataViewHandle view);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ECS_COMPONENTBUFFERMEMORYCONTAINER_H
