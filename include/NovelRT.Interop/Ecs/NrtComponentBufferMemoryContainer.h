// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_NRTCOMPONENTBUFFERMEMORYCONTAINER_H
#define NOVELRT_NRTCOMPONENTBUFFERMEMORYCONTAINER_H

#include "../NrtInteropUtils.h"
#include "NrtEcsUtils.h"
#include "NrtSparseSetMemoryContainer.h"

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct ComponentBufferMemoryContainerHandle* NrtComponentBufferMemoryContainer;

    typedef struct ComponentBufferImmutableDataViewHandle* NrtComponentBufferMemoryContainer_ImmutableDataView;

    typedef (*NrtComponentUpdateFnPtr)(NrtSparseSetMemoryContainer_ByteIteratorView,
                                       NrtSparseSetMemoryContainer_ByteIteratorView,
                                       size_t);

    NrtComponentBufferMemoryContainer Nrt_ComponentBufferMemoryContainer_Create(size_t poolSize,
                                                                                NrtComponentUpdateFnPtr fnPtr);

    void Nrt_ComponentBufferMemoryContainer_PrepContainerForFrame(NrtComponentBufferMemoryContainer container,
                                                                  NrtEntityIdVector entitiesToDelete);

    NrtComponentBufferMemoryContainer_ImmutableDataView Nrt_ComponentBufferMemoryContainer_GetDeleteInstructionState(
        NrtComponentBufferMemoryContainer container);

    NrtResult Nrt_ComponentBufferMemoryContainer_PushComponentUpdateInstruction(
        NrtComponentBufferMemoryContainer container,
        size_t poolId,
        NrtEntityId entity,
        const void* componentData);

    NrtResult Nrt_ComponentBufferMemoryContainer_GetComponent(
        NrtComponentBufferMemoryContainer container,
        NrtEntityId entity,
        NrtComponentBufferMemoryContainer_ImmutableDataView* outputResult);

    NrtComponentBufferMemoryContainer_ImmutableDataView Nrt_ComponentBufferMemoryContainer_GetComponentUnsafe(
        NrtComponentBufferMemoryContainer container,
        NrtEntityId entity);

    NrtBool Nrt_ComponentBufferMemoryContainer_HasComponent(NrtComponentBufferMemoryContainer container,
                                                            NrtEntityId entity);

    size_t Nrt_ComponentBufferMemoryContainer_GetImmutableDataLength(NrtComponentBufferMemoryContainer container);

    // clang-format off

    NrtSparseSetMemoryContainer_ConstIterator Nrt_ComponentBufferMemoryContainer_begin(
        NrtComponentBufferMemoryContainer container);

    NrtSparseSetMemoryContainer_ConstIterator Nrt_ComponentBufferMemoryContainer_end(
        NrtComponentBufferMemoryContainer container);

    // clang-format on

#ifdef __cplusplus
};
#endif

#endif // !NOVELRT_NRTCOMPONENTBUFFERMEMORYCONTAINER_H
