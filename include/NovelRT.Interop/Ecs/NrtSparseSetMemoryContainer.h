// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_ECS_SPARSESETMEMORYCONTAINER_H
#define NOVELRT_INTEROP_ECS_SPARSESETMEMORYCONTAINER_H

#include <NovelRT.Interop/NrtTypedefs.h>

#ifdef __cplusplus
extern "C"
{
#endif

    NrtSparseSetMemoryContainerHandle Nrt_SparseSetMemoryContainer_Create(size_t sizeOfDataTypeInBytes);

    NrtResult Nrt_SparseSetMemoryContainer_Insert(NrtSparseSetMemoryContainerHandle container,
                                                  size_t key,
                                                  const void* value);

    NrtBool Nrt_SparseSetMemoryContainer_TryInsert(NrtSparseSetMemoryContainerHandle container,
                                                   size_t key,
                                                   const void* value);

    NrtResult Nrt_SparseSetMemoryContainer_Remove(NrtSparseSetMemoryContainerHandle container, size_t key);

    NrtBool Nrt_SparseSetMemoryContainer_TryRemove(NrtSparseSetMemoryContainerHandle container, size_t key);

    void Nrt_SparseSetMemoryContainer_Clear(NrtSparseSetMemoryContainerHandle container);

    NrtBool Nrt_SparseSetMemoryContainer_ContainsKey(NrtSparseSetMemoryContainerHandle container, size_t key);

    NrtResult Nrt_SparseSetMemoryContainer_CopyKeyBasedOnDenseIndex(NrtSparseSetMemoryContainerHandle container,
                                                                    size_t denseIndex,
                                                                    size_t* outputResult);

    size_t Nrt_SparseSetMemoryContainer_CopyKeyBasedOnDenseIndexUnsafe(NrtSparseSetMemoryContainerHandle container,
                                                                       size_t denseIndex);

    NrtResult Nrt_SparseSetMemoryContainer_GetByteIteratorViewBasedOnDenseIndex(
        NrtSparseSetMemoryContainerHandle container,
        size_t denseIndex,
        NrtSparseSetMemoryContainer_ByteIteratorViewHandle* outputResult);

    NrtSparseSetMemoryContainer_ByteIteratorViewHandle
    Nrt_SparseSetMemoryContainer_GetByteIteratorViewBasedOnDenseIndexUnsafe(NrtSparseSetMemoryContainerHandle container,
                                                                            size_t denseIndex);

    NrtResult Nrt_SparseSetMemoryContainer_GetConstByteIteratorViewBasedOnDenseIndex(
        NrtSparseSetMemoryContainerHandle container,
        size_t denseIndex,
        NrtSparseSetMemoryContainer_ConstByteIteratorViewHandle* outputResult);

    NrtSparseSetMemoryContainer_ConstByteIteratorViewHandle
    Nrt_SparseSetMemoryContainer_GetConstByteIteratorViewBasedOnDenseIndexUnsafe(
        NrtSparseSetMemoryContainerHandle container,
        size_t index);

    size_t Nrt_SparseSetMemoryContainer_Length(NrtSparseSetMemoryContainerHandle container);

    NrtSparseSetMemoryContainer_ByteIteratorViewHandle Nrt_SparseSetMemoryContainer_Indexer(
        NrtSparseSetMemoryContainerHandle container,
        size_t key);

    NrtSparseSetMemoryContainer_ConstByteIteratorViewHandle Nrt_SparseSetMemoryContainer_ConstIndexer(
        NrtSparseSetMemoryContainerHandle container,
        size_t key);

    NrtSparseSetMemoryContainer_IteratorHandle Nrt_SparseSetMemoryContainer_begin(
        NrtSparseSetMemoryContainerHandle container);

    NrtSparseSetMemoryContainer_IteratorHandle Nrt_SparseSetMemoryContainer_end(
        NrtSparseSetMemoryContainerHandle container);

    NrtSparseSetMemoryContainer_ConstIteratorHandle Nrt_SparseSetMemoryContainer_cbegin(
        NrtSparseSetMemoryContainerHandle container);

    NrtSparseSetMemoryContainer_ConstIteratorHandle Nrt_SparseSetMemoryContainer_cend(
        NrtSparseSetMemoryContainerHandle container);

    NrtResult Nrt_SparseSetMemoryContainer_Destroy(NrtSparseSetMemoryContainerHandle container);

    NrtBool Nrt_SparseSetMemoryContainer_ByteIteratorView_IsValid(
        NrtSparseSetMemoryContainer_ByteIteratorViewHandle view);

    void Nrt_SparseSetMemoryContainer_ByteIteratorView_CopyFromLocation(
        NrtSparseSetMemoryContainer_ByteIteratorViewHandle view,
        void* outputLocation);

    void Nrt_SparseSetMemoryContainer_ByteIteratorView_WriteToLocation(
        NrtSparseSetMemoryContainer_ByteIteratorViewHandle view,
        void* data);

    void* Nrt_SparseSetMemoryContainer_ByteIteratorView_GetDataHandle(
        NrtSparseSetMemoryContainer_ByteIteratorViewHandle view);

    NrtResult Nrt_SparseSetMemoryContainer_ByteIteratorView_Destroy(
        NrtSparseSetMemoryContainer_ByteIteratorViewHandle view);

    NrtBool Nrt_SparseSetMemoryContainer_ConstByteIteratorView_IsValid(
        NrtSparseSetMemoryContainer_ConstByteIteratorViewHandle view);

    void Nrt_SparseSetMemoryContainer_ConstByteIteratorView_CopyFromLocation(
        NrtSparseSetMemoryContainer_ConstByteIteratorViewHandle view,
        void* outputLocation);

    const void* Nrt_SparseSetMemoryContainer_ConstByteIteratorView_GetDataHandle(
        NrtSparseSetMemoryContainer_ConstByteIteratorViewHandle view);

    NrtResult Nrt_SparseSetMemoryContainer_ConstByteIteratorView_Destroy(
        NrtSparseSetMemoryContainer_ConstByteIteratorViewHandle view);

    void Nrt_SparseSetMemoryContainer_Iterator_MoveNext(NrtSparseSetMemoryContainer_IteratorHandle iterator);

    NrtBool Nrt_SparseSetMemoryContainer_Iterator_Equal(NrtSparseSetMemoryContainer_IteratorHandle lhs,
                                                        NrtSparseSetMemoryContainer_IteratorHandle rhs);

    NrtBool Nrt_SparseSetMemoryContainer_Iterator_NotEqual(NrtSparseSetMemoryContainer_IteratorHandle lhs,
                                                           NrtSparseSetMemoryContainer_IteratorHandle rhs);

    NrtResult Nrt_SparseSetMemoryContainer_Iterator_GetValuePair(
        NrtSparseSetMemoryContainer_IteratorHandle iterator,
        size_t* outputId,
        NrtSparseSetMemoryContainer_ByteIteratorViewHandle* outputView);

    NrtResult Nrt_SparseSetMemoryContainer_Iterator_Destroy(NrtSparseSetMemoryContainer_IteratorHandle iterator);

    void Nrt_SparseSetMemoryContainer_ConstIterator_MoveNext(NrtSparseSetMemoryContainer_ConstIteratorHandle iterator);

    NrtBool Nrt_SparseSetMemoryContainer_ConstIterator_Equal(NrtSparseSetMemoryContainer_ConstIteratorHandle lhs,
                                                             NrtSparseSetMemoryContainer_ConstIteratorHandle rhs);

    NrtBool Nrt_SparseSetMemoryContainer_ConstIterator_NotEqual(NrtSparseSetMemoryContainer_ConstIteratorHandle lhs,
                                                                NrtSparseSetMemoryContainer_ConstIteratorHandle rhs);

    NrtResult Nrt_SparseSetMemoryContainer_ConstIterator_GetValuePair(
        NrtSparseSetMemoryContainer_ConstIteratorHandle iterator,
        size_t* outputId,
        NrtSparseSetMemoryContainer_ConstByteIteratorViewHandle* outputView);

    NrtResult Nrt_SparseSetMemoryContainer_ConstIterator_Destroy(
        NrtSparseSetMemoryContainer_ConstIteratorHandle iterator);
#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_ECS_SPARSESETMEMORYCONTAINER_H
