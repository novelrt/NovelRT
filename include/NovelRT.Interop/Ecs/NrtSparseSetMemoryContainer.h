// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_NRTSPARSESETMEMORYCONTAINER_H
#define NOVELRT_NRTSPARSESETMEMORYCONTAINER_H

#include "../NrtInteropUtils.h"

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct SparseSetMemoryContainerHandle* NrtSparseSetMemoryContainer;

    typedef struct SparseSetByteIteratorViewHandle* NrtSparseSetMemoryContainer_ByteIteratorView;

    typedef struct SparseSetConstByteIteratorViewHandle* NrtSparseSetMemoryContainer_ConstByteIteratorView;

    typedef struct SparseSetIteratorHandle* NrtSparseSetMemoryContainer_Iterator;

    typedef struct SparseSetConstIteratorHandle* NrtSparseSetMemoryContainer_ConstIterator;

NrtSparseSetMemoryContainer Nrt_SparseSetMemoryContainer_Create(size_t sizeOfDataTypeInBytes);

    NrtResult Nrt_SparseSetMemoryContainer_Insert(NrtSparseSetMemoryContainer container, size_t key, const void* value);

    NrtBool Nrt_SparseSetMemoryContainer_tryInsert(NrtSparseSetMemoryContainer container,
                                                   size_t key,
                                                   const void* value);

    NrtResult Nrt_SparseSetMemoryContainer_Remove(NrtSparseSetMemoryContainer container, size_t key);

    NrtBool Nrt_SparseSetMemoryContainer_TryRemove(NrtSparseSetMemoryContainer container, size_t key);

    void Nrt_SparseSetMemoryContainer_Clear(NrtSparseSetMemoryContainer container);

    NrtBool Nrt_SparseSetMemoryContainer_ContainsKey(NrtSparseSetMemoryContainer container, size_t key);

    NrtResult Nrt_SparseSetMemoryContainer_CopyKeyBasedOnDenseIndex(NrtSparseSetMemoryContainer container,
                                                                    size_t denseIndex,
                                                                    size_t* outputResult);

    size_t Nrt_SparseSetMemoryContainer_CopyKeyBasedOnDenseIndexUnsafe(NrtSparseSetMemoryContainer container,
                                                                       size_t denseIndex);

    NrtResult Nrt_SparseSetMemoryContainer_GetByteIteratorViewBasedOnDenseIndex(
        NrtSparseSetMemoryContainer container,
        size_t denseIndex,
        NrtSparseSetMemoryContainer_ByteIteratorView* outputResult);

    NrtSparseSetMemoryContainer_ByteIteratorView
    Nrt_SparseSetMemoryContainer_GetByteIteratorViewBasedOnDenseIndexUnsafe(NrtSparseSetMemoryContainer container,
                                                                            size_t index);

    NrtResult Nrt_SparseSetMemoryContainer_GetConstByteIteratorViewBasedOnDenseIndex(
        NrtSparseSetMemoryContainer container,
        size_t denseIndex,
        NrtSparseSetMemoryContainer_ConstByteIteratorView* outputResult);

    NrtSparseSetMemoryContainer_ConstByteIteratorView
    Nrt_SparseSetMemoryContainer_GetConstByteIteratorViewBasedOnDenseIndexUnsafe(
        const NrtSparseSetMemoryContainer container,
        size_t index);

    size_t Nrt_SparseSetMemoryContainer_Length(NrtSparseSetMemoryContainer container);

    NrtSparseSetMemoryContainer_ByteIteratorView Nrt_SparseSetMemoryContainer_Indexer(
        NrtSparseSetMemoryContainer container,
        size_t key);

    NrtSparseSetMemoryContainer_ByteIteratorView Nrt_SparseSetMemoryContainer_ConstIndexer(
        const NrtSparseSetMemoryContainer container,
        size_t key);

    // clang-format off

    NrtSparseSetMemoryContainer_Iterator Nrt_SparseSetMemoryContainer_begin(NrtSparseSetMemoryContainer container);

    NrtSparseSetMemoryContainer_Iterator Nrt_SparseSetMemoryContainer_end(NrtSparseSetMemoryContainer container);

    NrtSparseSetMemoryContainer_ConstIterator Nrt_SparseSetMemoryContainer_cbegin(const NrtSparseSetMemoryContainer container);

    NrtSparseSetMemoryContainer_ConstIterator Nrt_SparseSetMemoryContainer_cend(const NrtSparseSetMemoryContainer container);

    // clang-format on

#ifdef __cplusplus
};
#endif

#endif // !NOVELRT_NRTSPARSESETMEMORYCONTAINER_H
