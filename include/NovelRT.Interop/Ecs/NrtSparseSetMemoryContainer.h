// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_NRTSPARSESETMEMORYCONTAINER_H
#define NOVELRT_NRTSPARSESETMEMORYCONTAINER_H

#include "../NrtInteropUtils.h"
#include <stddef.h>

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
                                                                            size_t denseIndex);

    NrtResult Nrt_SparseSetMemoryContainer_GetConstByteIteratorViewBasedOnDenseIndex(
        NrtSparseSetMemoryContainer container,
        size_t denseIndex,
        NrtSparseSetMemoryContainer_ConstByteIteratorView* outputResult);

    NrtSparseSetMemoryContainer_ConstByteIteratorView
    Nrt_SparseSetMemoryContainer_GetConstByteIteratorViewBasedOnDenseIndexUnsafe(NrtSparseSetMemoryContainer container,
                                                                                 size_t index);

    size_t Nrt_SparseSetMemoryContainer_Length(NrtSparseSetMemoryContainer container);

    NrtSparseSetMemoryContainer_ByteIteratorView Nrt_SparseSetMemoryContainer_Indexer(
        NrtSparseSetMemoryContainer container,
        size_t key);

    NrtSparseSetMemoryContainer_ConstByteIteratorView Nrt_SparseSetMemoryContainer_ConstIndexer(
        NrtSparseSetMemoryContainer container,
        size_t key);

    NrtSparseSetMemoryContainer_Iterator Nrt_SparseSetMemoryContainer_begin(NrtSparseSetMemoryContainer container);

    NrtSparseSetMemoryContainer_Iterator Nrt_SparseSetMemoryContainer_end(NrtSparseSetMemoryContainer container);

    NrtSparseSetMemoryContainer_ConstIterator Nrt_SparseSetMemoryContainer_cbegin(
        NrtSparseSetMemoryContainer container);

    NrtSparseSetMemoryContainer_ConstIterator Nrt_SparseSetMemoryContainer_cend(NrtSparseSetMemoryContainer container);

    NrtBool Nrt_SparseSetMemoryContainer_ByteIteratorView_IsValid(NrtSparseSetMemoryContainer_ByteIteratorView view);

    void Nrt_SparseSetMemoryContainer_ByteIteratorView_CopyFromLocation(
        NrtSparseSetMemoryContainer_ByteIteratorView view,
        void* outputLocation);

    void Nrt_SparseSetMemoryContainer_ByteIteratorView_WriteToLocation(
        NrtSparseSetMemoryContainer_ByteIteratorView view,
        void* data);

    void* Nrt_SparseSetMemoryContainer_ByteIteratorView_GetDataHandle(
        NrtSparseSetMemoryContainer_ByteIteratorView view);

    NrtResult Nrt_SparseSetMemoryContainer_ByteIteratorView_Destroy(NrtSparseSetMemoryContainer_ByteIteratorView view);

    NrtBool Nrt_SparseSetMemoryContainer_ConstByteIteratorView_IsValid(
        NrtSparseSetMemoryContainer_ConstByteIteratorView view);

    void Nrt_SparseSetMemoryContainer_ConstByteIteratorView_CopyFromLocation(
        NrtSparseSetMemoryContainer_ConstByteIteratorView view,
        void* outputLocation);

    const void* Nrt_SparseSetMemoryContainer_ConstByteIteratorView_GetDataHandle(
        NrtSparseSetMemoryContainer_ConstByteIteratorView view);

    NrtResult Nrt_SparseSetMemoryContainer_ConstByteIteratorView_Destroy(
        NrtSparseSetMemoryContainer_ConstByteIteratorView view);

    void Nrt_SparseSetMemoryContainer_Iterator_MoveNext(NrtSparseSetMemoryContainer_Iterator iterator);

    NrtBool Nrt_SparseSetMemoryContainer_Iterator_Equal(NrtSparseSetMemoryContainer_Iterator lhs,
                                                        NrtSparseSetMemoryContainer_Iterator rhs);

    NrtBool Nrt_SparseSetMemoryContainer_Iterator_NotEqual(NrtSparseSetMemoryContainer_Iterator lhs,
                                                           NrtSparseSetMemoryContainer_Iterator rhs);

    NrtResult Nrt_SparseSetMemoryContainer_Iterator_GetValuePair(
        NrtSparseSetMemoryContainer_Iterator iterator,
        size_t* outputId,
        NrtSparseSetMemoryContainer_ByteIteratorView* outputView);

    NrtResult Nrt_SparseSetMemoryContainer_Iterator_Destroy(NrtSparseSetMemoryContainer_Iterator iterator);

    void Nrt_SparseSetMemoryContainer_ConstIterator_MoveNext(NrtSparseSetMemoryContainer_ConstIterator iterator);

    NrtBool Nrt_SparseSetMemoryContainer_ConstIterator_Equal(NrtSparseSetMemoryContainer_ConstIterator lhs,
                                                             NrtSparseSetMemoryContainer_ConstIterator rhs);

    NrtBool Nrt_SparseSetMemoryContainer_ConstIterator_NotEqual(NrtSparseSetMemoryContainer_ConstIterator lhs,
                                                                NrtSparseSetMemoryContainer_ConstIterator rhs);

    NrtResult Nrt_SparseSetMemoryContainer_ConstIterator_GetValuePair(
        NrtSparseSetMemoryContainer_ConstIterator iterator,
        size_t* outputId,
        NrtSparseSetMemoryContainer_ConstByteIteratorView* outputView);

    NrtResult Nrt_SparseSetMemoryContainer_ConstIterator_Destroy(NrtSparseSetMemoryContainer_ConstIterator iterator);
#ifdef __cplusplus
};
#endif

#endif // !NOVELRT_NRTSPARSESETMEMORYCONTAINER_H
