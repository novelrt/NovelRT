// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Ecs/NrtSparseSetMemoryContainer.h>
#include <NovelRT/Ecs/SparseSetMemoryContainer.h>
#include <NovelRT/Exceptions/DuplicateKeyException.h>
#include <NovelRT/Exceptions/KeyNotFoundException.h>
#include <stdexcept>

using namespace NovelRT::Ecs;
using namespace NovelRT::Exceptions;

std::vector<std::byte> dummyByteVectorSparseSet{std::byte(0)};
std::vector<size_t> dummySizeTVectorSparseSet{0};

extern "C"
{
    NrtSparseSetMemoryContainer Nrt_SparseSetMemoryContainer_Create(size_t sizeOfDataTypeInBytes)
    {
        return reinterpret_cast<NrtSparseSetMemoryContainer>(new SparseSetMemoryContainer(sizeOfDataTypeInBytes));
    }

    NrtResult Nrt_SparseSetMemoryContainer_Insert(NrtSparseSetMemoryContainer container, size_t key, const void* value)
    {
        if (container == nullptr || value == nullptr)
        {
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        try
        {
            reinterpret_cast<SparseSetMemoryContainer*>(container)->Insert(key, value);

            return NRT_SUCCESS;
        }
        catch (const DuplicateKeyException&)
        {
            return NRT_FAILURE_DUPLICATE_KEY_PROVIDED;
        }
        catch (const std::bad_alloc&)
        {
            return NRT_FAILURE_OUT_OF_MEMORY;
        }
        catch (const std::exception&)
        {
            return NRT_FAILURE_UNKNOWN;
        }
    }

    NrtBool Nrt_SparseSetMemoryContainer_tryInsert(NrtSparseSetMemoryContainer container, size_t key, const void* value)
    {
        return reinterpret_cast<SparseSetMemoryContainer*>(container)->TryInsert(key, value) ? NRT_TRUE : NRT_FALSE;
    }

    NrtResult Nrt_SparseSetMemoryContainer_Remove(NrtSparseSetMemoryContainer container, size_t key)
    {
        if (container == nullptr)
        {
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        try
        {
            reinterpret_cast<SparseSetMemoryContainer*>(container)->Remove(key);
            return NRT_SUCCESS;
        }
        catch (const KeyNotFoundException&)
        {
            return NRT_FAILURE_KEY_NOT_FOUND;
        }
    }

    NrtBool Nrt_SparseSetMemoryContainer_TryRemove(NrtSparseSetMemoryContainer container, size_t key)
    {
        return reinterpret_cast<SparseSetMemoryContainer*>(container)->TryRemove(key) ? NRT_TRUE : NRT_FALSE;
    }

    void Nrt_SparseSetMemoryContainer_Clear(NrtSparseSetMemoryContainer container)
    {
        reinterpret_cast<SparseSetMemoryContainer*>(container)->Clear();
    }

    NrtBool Nrt_SparseSetMemoryContainer_ContainsKey(NrtSparseSetMemoryContainer container, size_t key)
    {
        return reinterpret_cast<SparseSetMemoryContainer*>(container)->ContainsKey(key) ? NRT_TRUE : NRT_FALSE;
    }

    NrtResult Nrt_SparseSetMemoryContainer_CopyKeyBasedOnDenseIndex(NrtSparseSetMemoryContainer container,
                                                                    size_t denseIndex,
                                                                    size_t* outputResult)
    {
        if (container == nullptr || outputResult == nullptr)
        {
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        try
        {
            *outputResult =
                reinterpret_cast<SparseSetMemoryContainer*>(container)->CopyKeyBasedOnDenseIndex(denseIndex);
            return NRT_SUCCESS;
        }
        catch (const std::out_of_range&)
        {
            return NRT_FAILURE_ARGUMENT_OUT_OF_RANGE;
        }
    }

    size_t Nrt_SparseSetMemoryContainer_CopyKeyBasedOnDenseIndexUnsafe(NrtSparseSetMemoryContainer container,
                                                                       size_t denseIndex)
    {
        return reinterpret_cast<SparseSetMemoryContainer*>(container)->CopyKeyBasedOnDenseIndexUnsafe(denseIndex);
    }

    NrtResult Nrt_SparseSetMemoryContainer_GetByteIteratorViewBasedOnDenseIndex(
        NrtSparseSetMemoryContainer container,
        size_t denseIndex,
        NrtSparseSetMemoryContainer_ByteIteratorView* outputResult)
    {
        if (container == nullptr || outputResult == nullptr)
        {
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        try
        {
            auto containerPtr = reinterpret_cast<SparseSetMemoryContainer*>(container);
            auto ptr = new SparseSetMemoryContainer::ByteIteratorView(dummyByteVectorSparseSet.end(), 0);
            *ptr = containerPtr->GetByteIteratorViewBasedOnDenseIndex(denseIndex);
            *outputResult = reinterpret_cast<NrtSparseSetMemoryContainer_ByteIteratorView>(ptr);
            return NRT_SUCCESS;
        }
        catch (const std::out_of_range&)
        {
            return NRT_FAILURE_ARGUMENT_OUT_OF_RANGE;
        }
    }

    NrtSparseSetMemoryContainer_ByteIteratorView
    Nrt_SparseSetMemoryContainer_GetByteIteratorViewBasedOnDenseIndexUnsafe(NrtSparseSetMemoryContainer container,
                                                                            size_t denseIndex)
    {
        auto containerPtr = reinterpret_cast<SparseSetMemoryContainer*>(container);
        auto ptr = new SparseSetMemoryContainer::ByteIteratorView(dummyByteVectorSparseSet.end(), 0);
        *ptr = containerPtr->GetByteIteratorViewBasedOnDenseIndexUnsafe(denseIndex);
        return reinterpret_cast<NrtSparseSetMemoryContainer_ByteIteratorView>(ptr);
    }

    NrtResult Nrt_SparseSetMemoryContainer_GetConstByteIteratorViewBasedOnDenseIndex(
        NrtSparseSetMemoryContainer container,
        size_t denseIndex,
        NrtSparseSetMemoryContainer_ConstByteIteratorView* outputResult)
    {
        if (container == nullptr || outputResult == nullptr)
        {
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        try
        {
            auto containerPtr = reinterpret_cast<const SparseSetMemoryContainer*>(container);
            auto ptr = new SparseSetMemoryContainer::ConstByteIteratorView(dummyByteVectorSparseSet.end(), 0);
            *ptr = containerPtr->GetByteIteratorViewBasedOnDenseIndex(denseIndex);
            *outputResult = reinterpret_cast<NrtSparseSetMemoryContainer_ConstByteIteratorView>(ptr);
            return NRT_SUCCESS;
        }
        catch (const std::out_of_range&)
        {
            return NRT_FAILURE_ARGUMENT_OUT_OF_RANGE;
        }
    }

    NrtSparseSetMemoryContainer_ConstByteIteratorView
    Nrt_SparseSetMemoryContainer_GetConstByteIteratorViewBasedOnDenseIndexUnsafe(NrtSparseSetMemoryContainer container,
                                                                                 size_t denseIndex)
    {
        auto containerPtr = reinterpret_cast<const SparseSetMemoryContainer*>(container);
        auto ptr = new SparseSetMemoryContainer::ConstByteIteratorView(dummyByteVectorSparseSet.end(), 0);
        *ptr = containerPtr->GetByteIteratorViewBasedOnDenseIndexUnsafe(denseIndex);
        return reinterpret_cast<NrtSparseSetMemoryContainer_ConstByteIteratorView>(ptr);
    }

    size_t Nrt_SparseSetMemoryContainer_Length(NrtSparseSetMemoryContainer container)
    {
        return reinterpret_cast<SparseSetMemoryContainer*>(container)->Length();
    }

    NrtSparseSetMemoryContainer_ByteIteratorView Nrt_SparseSetMemoryContainer_Indexer(
        NrtSparseSetMemoryContainer container,
        size_t key)
    {
        auto containerPtr = reinterpret_cast<SparseSetMemoryContainer*>(container);
        auto ptr = new SparseSetMemoryContainer::ByteIteratorView(dummyByteVectorSparseSet.end(), 0);
        *ptr = (*containerPtr)[key];
        return reinterpret_cast<NrtSparseSetMemoryContainer_ByteIteratorView>(ptr);
    }

    NrtSparseSetMemoryContainer_ConstByteIteratorView Nrt_SparseSetMemoryContainer_ConstIndexer(
        NrtSparseSetMemoryContainer container,
        size_t key)
    {
        auto containerPtr = reinterpret_cast<const SparseSetMemoryContainer*>(container);
        auto ptr = new SparseSetMemoryContainer::ConstByteIteratorView(dummyByteVectorSparseSet.end(), 0);
        *ptr = (*containerPtr)[key];
        return reinterpret_cast<NrtSparseSetMemoryContainer_ConstByteIteratorView>(ptr);
    }

    NrtSparseSetMemoryContainer_Iterator Nrt_SparseSetMemoryContainer_begin(NrtSparseSetMemoryContainer container)
    {
        auto containerPtr = reinterpret_cast<SparseSetMemoryContainer*>(container);
        auto ptr = new SparseSetMemoryContainer::Iterator(std::make_tuple(dummySizeTVectorSparseSet.end(), SparseSetMemoryContainer::ByteIteratorView(dummyByteVectorSparseSet.end(), 0)));
        *ptr = containerPtr->begin();
        return reinterpret_cast<NrtSparseSetMemoryContainer_Iterator>(ptr);
    }

    NrtSparseSetMemoryContainer_Iterator Nrt_SparseSetMemoryContainer_end(NrtSparseSetMemoryContainer container)
    {
        auto containerPtr = reinterpret_cast<SparseSetMemoryContainer*>(container);
        auto ptr = new SparseSetMemoryContainer::Iterator(std::make_tuple(dummySizeTVectorSparseSet.end(), SparseSetMemoryContainer::ByteIteratorView(dummyByteVectorSparseSet.end(), 0)));
        *ptr = containerPtr->end();
        return reinterpret_cast<NrtSparseSetMemoryContainer_Iterator>(ptr);
    }

    NrtSparseSetMemoryContainer_ConstIterator Nrt_SparseSetMemoryContainer_cbegin(NrtSparseSetMemoryContainer container)
    {
        auto containerPtr = reinterpret_cast<const SparseSetMemoryContainer*>(container);
        auto ptr = new SparseSetMemoryContainer::ConstIterator(std::make_tuple(dummySizeTVectorSparseSet.end(), SparseSetMemoryContainer::ConstByteIteratorView(dummyByteVectorSparseSet.cend(), 0)));
        *ptr = containerPtr->begin();
        return reinterpret_cast<NrtSparseSetMemoryContainer_ConstIterator>(ptr);
    }

    NrtSparseSetMemoryContainer_ConstIterator Nrt_SparseSetMemoryContainer_cend(NrtSparseSetMemoryContainer container)
    {
        auto containerPtr = reinterpret_cast<const SparseSetMemoryContainer*>(container);
        auto ptr = new SparseSetMemoryContainer::ConstIterator(std::make_tuple(dummySizeTVectorSparseSet.end(), SparseSetMemoryContainer::ConstByteIteratorView(dummyByteVectorSparseSet.cend(), 0)));
        *ptr = containerPtr->end();
        return reinterpret_cast<NrtSparseSetMemoryContainer_ConstIterator>(ptr);
    }
}
