// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Ecs/NrtSparseSetMemoryContainer.h>
#include <NovelRT/Ecs/Ecs.h>
#include <NovelRT.Interop/NrtErrorHandling.h>

using namespace NovelRT::Ecs;
using namespace NovelRT::Exceptions;

std::vector<uint8_t> dummyByteVectorSparseSet{uint8_t(0)};
std::vector<size_t> dummySizeTVectorSparseSet{0};

extern "C"
{
    NrtSparseSetMemoryContainerHandle Nrt_SparseSetMemoryContainer_Create(size_t sizeOfDataTypeInBytes)
    {
        return reinterpret_cast<NrtSparseSetMemoryContainerHandle>(new SparseSetMemoryContainer(sizeOfDataTypeInBytes));
    }

    NrtResult Nrt_SparseSetMemoryContainer_Insert(NrtSparseSetMemoryContainerHandle container,
                                                  size_t key,
                                                  const void* value)
    {
        if (container == nullptr)
        {
            Nrt_setErrIsNullInstanceProvided();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (value == nullptr)
        {
            Nrt_setErrIsNullArgProvided();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        try
        {
            reinterpret_cast<SparseSetMemoryContainer*>(container)->Insert(key, value);

            return NRT_SUCCESS;
        }
        catch (const DuplicateKeyException&)
        {
            Nrt_setErrMsgDupKeyGiven();
            return NRT_FAILURE_DUPLICATE_KEY_PROVIDED;
        }
        catch (const std::bad_alloc&)
        {
            Nrt_setErrMsgIsOutOfMemoryInternal();
            return NRT_FAILURE_OUT_OF_MEMORY;
        }
        catch (const std::exception&)
        {
            Nrt_setErrMsgErrorUnknown();
            return NRT_FAILURE_UNKNOWN;
        }
    }

    NrtBool Nrt_SparseSetMemoryContainer_TryInsert(NrtSparseSetMemoryContainerHandle container,
                                                   size_t key,
                                                   const void* value)
    {
        return reinterpret_cast<SparseSetMemoryContainer*>(container)->TryInsert(key, value) ? NRT_TRUE : NRT_FALSE;
    }

    NrtResult Nrt_SparseSetMemoryContainer_Remove(NrtSparseSetMemoryContainerHandle container, size_t key)
    {
        if (container == nullptr)
        {
            Nrt_setErrIsNullInstanceProvided();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        try
        {
            reinterpret_cast<SparseSetMemoryContainer*>(container)->Remove(key);
            return NRT_SUCCESS;
        }
        catch (const KeyNotFoundException&)
        {
            Nrt_setErrMsgKeyNotFound();
            return NRT_FAILURE_KEY_NOT_FOUND;
        }
    }

    NrtBool Nrt_SparseSetMemoryContainer_TryRemove(NrtSparseSetMemoryContainerHandle container, size_t key)
    {
        return reinterpret_cast<SparseSetMemoryContainer*>(container)->TryRemove(key) ? NRT_TRUE : NRT_FALSE;
    }

    void Nrt_SparseSetMemoryContainer_Clear(NrtSparseSetMemoryContainerHandle container)
    {
        reinterpret_cast<SparseSetMemoryContainer*>(container)->Clear();
    }

    NrtBool Nrt_SparseSetMemoryContainer_ContainsKey(NrtSparseSetMemoryContainerHandle container, size_t key)
    {
        return reinterpret_cast<SparseSetMemoryContainer*>(container)->ContainsKey(key) ? NRT_TRUE : NRT_FALSE;
    }

    NrtResult Nrt_SparseSetMemoryContainer_CopyKeyBasedOnDenseIndex(NrtSparseSetMemoryContainerHandle container,
                                                                    size_t denseIndex,
                                                                    size_t* outputResult)
    {
        if (container == nullptr)
        {
            Nrt_setErrIsNullInstanceProvided();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputResult == nullptr)
        {
            Nrt_setErrIsNullArgProvided();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        try
        {
            *outputResult =
                reinterpret_cast<SparseSetMemoryContainer*>(container)->CopyKeyBasedOnDenseIndex(denseIndex);
            return NRT_SUCCESS;
        }
        catch (const std::out_of_range&)
        {
            Nrt_setErrMsgIsArgumentOutOfRangeInternal();
            return NRT_FAILURE_ARGUMENT_OUT_OF_RANGE;
        }
    }

    size_t Nrt_SparseSetMemoryContainer_CopyKeyBasedOnDenseIndexUnsafe(NrtSparseSetMemoryContainerHandle container,
                                                                       size_t denseIndex)
    {
        return reinterpret_cast<SparseSetMemoryContainer*>(container)->CopyKeyBasedOnDenseIndexUnsafe(denseIndex);
    }

    NrtResult Nrt_SparseSetMemoryContainer_GetByteIteratorViewBasedOnDenseIndex(
        NrtSparseSetMemoryContainerHandle container,
        size_t denseIndex,
        NrtSparseSetMemoryContainer_ByteIteratorViewHandle* outputResult)
    {
        if (container == nullptr)
        {
            Nrt_setErrIsNullInstanceProvided();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputResult == nullptr)
        {
            Nrt_setErrIsNullArgProvided();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        try
        {
            auto containerPtr = reinterpret_cast<SparseSetMemoryContainer*>(container);
            auto ptr = new SparseSetMemoryContainer::ByteIteratorView(dummyByteVectorSparseSet.end(), 0);
            *ptr = containerPtr->GetByteIteratorViewBasedOnDenseIndex(denseIndex);
            *outputResult = reinterpret_cast<NrtSparseSetMemoryContainer_ByteIteratorViewHandle>(ptr);
            return NRT_SUCCESS;
        }
        catch (const std::out_of_range&)
        {
            Nrt_setErrMsgIsArgumentOutOfRangeInternal();
            return NRT_FAILURE_ARGUMENT_OUT_OF_RANGE;
        }
    }

    NrtSparseSetMemoryContainer_ByteIteratorViewHandle
    Nrt_SparseSetMemoryContainer_GetByteIteratorViewBasedOnDenseIndexUnsafe(NrtSparseSetMemoryContainerHandle container,
                                                                            size_t denseIndex)
    {
        auto containerPtr = reinterpret_cast<SparseSetMemoryContainer*>(container);
        auto ptr = new SparseSetMemoryContainer::ByteIteratorView(dummyByteVectorSparseSet.end(), 0);
        *ptr = containerPtr->GetByteIteratorViewBasedOnDenseIndexUnsafe(denseIndex);
        return reinterpret_cast<NrtSparseSetMemoryContainer_ByteIteratorViewHandle>(ptr);
    }

    NrtResult Nrt_SparseSetMemoryContainer_GetConstByteIteratorViewBasedOnDenseIndex(
        NrtSparseSetMemoryContainerHandle container,
        size_t denseIndex,
        NrtSparseSetMemoryContainer_ConstByteIteratorViewHandle* outputResult)
    {
        if (container == nullptr)
        {
            Nrt_setErrIsNullInstanceProvided();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputResult == nullptr)
        {
            Nrt_setErrIsNullArgProvided();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        try
        {
            auto containerPtr = reinterpret_cast<const SparseSetMemoryContainer*>(container);
            auto ptr = new SparseSetMemoryContainer::ConstByteIteratorView(dummyByteVectorSparseSet.end(), 0);
            *ptr = containerPtr->GetByteIteratorViewBasedOnDenseIndex(denseIndex);
            *outputResult = reinterpret_cast<NrtSparseSetMemoryContainer_ConstByteIteratorViewHandle>(ptr);
            return NRT_SUCCESS;
        }
        catch (const std::out_of_range&)
        {
            Nrt_setErrMsgIsArgumentOutOfRangeInternal();
            return NRT_FAILURE_ARGUMENT_OUT_OF_RANGE;
        }
    }

    NrtSparseSetMemoryContainer_ConstByteIteratorViewHandle
    Nrt_SparseSetMemoryContainer_GetConstByteIteratorViewBasedOnDenseIndexUnsafe(
        NrtSparseSetMemoryContainerHandle container,
        size_t denseIndex)
    {
        auto containerPtr = reinterpret_cast<const SparseSetMemoryContainer*>(container);
        auto ptr = new SparseSetMemoryContainer::ConstByteIteratorView(dummyByteVectorSparseSet.end(), 0);
        *ptr = containerPtr->GetByteIteratorViewBasedOnDenseIndexUnsafe(denseIndex);
        return reinterpret_cast<NrtSparseSetMemoryContainer_ConstByteIteratorViewHandle>(ptr);
    }

    size_t Nrt_SparseSetMemoryContainer_Length(NrtSparseSetMemoryContainerHandle container)
    {
        return reinterpret_cast<SparseSetMemoryContainer*>(container)->Length();
    }

    NrtSparseSetMemoryContainer_ByteIteratorViewHandle Nrt_SparseSetMemoryContainer_Indexer(
        NrtSparseSetMemoryContainerHandle container,
        size_t key)
    {
        auto containerPtr = reinterpret_cast<SparseSetMemoryContainer*>(container);
        auto ptr = new SparseSetMemoryContainer::ByteIteratorView(dummyByteVectorSparseSet.end(), 0);
        *ptr = (*containerPtr)[key];
        return reinterpret_cast<NrtSparseSetMemoryContainer_ByteIteratorViewHandle>(ptr);
    }

    NrtSparseSetMemoryContainer_ConstByteIteratorViewHandle Nrt_SparseSetMemoryContainer_ConstIndexer(
        NrtSparseSetMemoryContainerHandle container,
        size_t key)
    {
        auto containerPtr = reinterpret_cast<const SparseSetMemoryContainer*>(container);
        auto ptr = new SparseSetMemoryContainer::ConstByteIteratorView(dummyByteVectorSparseSet.end(), 0);
        *ptr = (*containerPtr)[key];
        return reinterpret_cast<NrtSparseSetMemoryContainer_ConstByteIteratorViewHandle>(ptr);
    }

    NrtSparseSetMemoryContainer_IteratorHandle Nrt_SparseSetMemoryContainer_begin(
        NrtSparseSetMemoryContainerHandle container)
    {
        auto containerPtr = reinterpret_cast<SparseSetMemoryContainer*>(container);
        auto ptr = new SparseSetMemoryContainer::Iterator(
            std::make_tuple(dummySizeTVectorSparseSet.end(),
                            SparseSetMemoryContainer::ByteIteratorView(dummyByteVectorSparseSet.end(), 0)));
        *ptr = containerPtr->begin();
        return reinterpret_cast<NrtSparseSetMemoryContainer_IteratorHandle>(ptr);
    }

    NrtSparseSetMemoryContainer_IteratorHandle Nrt_SparseSetMemoryContainer_end(
        NrtSparseSetMemoryContainerHandle container)
    {
        auto containerPtr = reinterpret_cast<SparseSetMemoryContainer*>(container);
        auto ptr = new SparseSetMemoryContainer::Iterator(
            std::make_tuple(dummySizeTVectorSparseSet.end(),
                            SparseSetMemoryContainer::ByteIteratorView(dummyByteVectorSparseSet.end(), 0)));
        *ptr = containerPtr->end();
        return reinterpret_cast<NrtSparseSetMemoryContainer_IteratorHandle>(ptr);
    }

    NrtSparseSetMemoryContainer_ConstIteratorHandle Nrt_SparseSetMemoryContainer_cbegin(
        NrtSparseSetMemoryContainerHandle container)
    {
        auto containerPtr = reinterpret_cast<const SparseSetMemoryContainer*>(container);
        auto ptr = new SparseSetMemoryContainer::ConstIterator(
            std::make_tuple(dummySizeTVectorSparseSet.end(),
                            SparseSetMemoryContainer::ConstByteIteratorView(dummyByteVectorSparseSet.cend(), 0)));
        *ptr = containerPtr->begin();
        return reinterpret_cast<NrtSparseSetMemoryContainer_ConstIteratorHandle>(ptr);
    }

    NrtSparseSetMemoryContainer_ConstIteratorHandle Nrt_SparseSetMemoryContainer_cend(
        NrtSparseSetMemoryContainerHandle container)
    {
        auto containerPtr = reinterpret_cast<const SparseSetMemoryContainer*>(container);
        auto ptr = new SparseSetMemoryContainer::ConstIterator(
            std::make_tuple(dummySizeTVectorSparseSet.end(),
                            SparseSetMemoryContainer::ConstByteIteratorView(dummyByteVectorSparseSet.cend(), 0)));
        *ptr = containerPtr->end();
        return reinterpret_cast<NrtSparseSetMemoryContainer_ConstIteratorHandle>(ptr);
    }

    NrtResult Nrt_SparseSetMemoryContainer_Destroy(NrtSparseSetMemoryContainerHandle container)
    {
        if (container == nullptr)
        {
            Nrt_setErrIsNullInstanceProvided();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        delete reinterpret_cast<SparseSetMemoryContainer*>(container);
        return NRT_SUCCESS;
    }

    NrtBool Nrt_SparseSetMemoryContainer_ByteIteratorView_IsValid(
        NrtSparseSetMemoryContainer_ByteIteratorViewHandle view)
    {
        return reinterpret_cast<SparseSetMemoryContainer::ByteIteratorView*>(view)->IsValid() ? NRT_TRUE : NRT_FALSE;
    }

    void Nrt_SparseSetMemoryContainer_ByteIteratorView_CopyFromLocation(
        NrtSparseSetMemoryContainer_ByteIteratorViewHandle view,
        void* outputLocation)
    {
        reinterpret_cast<SparseSetMemoryContainer::ByteIteratorView*>(view)->CopyFromLocation(outputLocation);
    }

    void Nrt_SparseSetMemoryContainer_ByteIteratorView_WriteToLocation(
        NrtSparseSetMemoryContainer_ByteIteratorViewHandle view,
        void* data)
    {
        reinterpret_cast<SparseSetMemoryContainer::ByteIteratorView*>(view)->WriteToLocation(data);
    }

    void* Nrt_SparseSetMemoryContainer_ByteIteratorView_GetDataHandle(
        NrtSparseSetMemoryContainer_ByteIteratorViewHandle view)
    {
        return reinterpret_cast<SparseSetMemoryContainer::ByteIteratorView*>(view)->GetDataHandle();
    }

    NrtResult Nrt_SparseSetMemoryContainer_ByteIteratorView_Destroy(
        NrtSparseSetMemoryContainer_ByteIteratorViewHandle view)
    {
        if (view == nullptr)
        {
            Nrt_setErrIsNullInstanceProvided();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        delete reinterpret_cast<SparseSetMemoryContainer::ByteIteratorView*>(view);

        return NRT_SUCCESS;
    }

    NrtBool Nrt_SparseSetMemoryContainer_ConstByteIteratorView_IsValid(
        NrtSparseSetMemoryContainer_ConstByteIteratorViewHandle view)
    {
        return reinterpret_cast<SparseSetMemoryContainer::ConstByteIteratorView*>(view)->IsValid() ? NRT_TRUE
                                                                                                   : NRT_FALSE;
    }

    void Nrt_SparseSetMemoryContainer_ConstByteIteratorView_CopyFromLocation(
        NrtSparseSetMemoryContainer_ConstByteIteratorViewHandle view,
        void* outputLocation)
    {
        reinterpret_cast<SparseSetMemoryContainer::ConstByteIteratorView*>(view)->CopyFromLocation(outputLocation);
    }

    const void* Nrt_SparseSetMemoryContainer_ConstByteIteratorView_GetDataHandle(
        NrtSparseSetMemoryContainer_ConstByteIteratorViewHandle view)
    {
        return reinterpret_cast<SparseSetMemoryContainer::ConstByteIteratorView*>(view)->GetDataHandle();
    }

    NrtResult Nrt_SparseSetMemoryContainer_ConstByteIteratorView_Destroy(
        NrtSparseSetMemoryContainer_ConstByteIteratorViewHandle view)
    {
        if (view == nullptr)
        {
            Nrt_setErrIsNullInstanceProvided();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        delete reinterpret_cast<SparseSetMemoryContainer::ConstByteIteratorView*>(view);

        return NRT_SUCCESS;
    }

    void Nrt_SparseSetMemoryContainer_Iterator_MoveNext(NrtSparseSetMemoryContainer_IteratorHandle iterator)
    {
        (*reinterpret_cast<SparseSetMemoryContainer::Iterator*>(iterator))++;
    }

    NrtBool Nrt_SparseSetMemoryContainer_Iterator_Equal(NrtSparseSetMemoryContainer_IteratorHandle lhs,
                                                        NrtSparseSetMemoryContainer_IteratorHandle rhs)
    {
        return ((*reinterpret_cast<SparseSetMemoryContainer::Iterator*>(lhs)) ==
                (*reinterpret_cast<SparseSetMemoryContainer::Iterator*>(rhs)))
                   ? NRT_TRUE
                   : NRT_FALSE;
    }

    NrtBool Nrt_SparseSetMemoryContainer_Iterator_NotEqual(NrtSparseSetMemoryContainer_IteratorHandle lhs,
                                                           NrtSparseSetMemoryContainer_IteratorHandle rhs)
    {
        return ((*reinterpret_cast<SparseSetMemoryContainer::Iterator*>(lhs)) !=
                (*reinterpret_cast<SparseSetMemoryContainer::Iterator*>(rhs)))
                   ? NRT_TRUE
                   : NRT_FALSE;
    }

    NrtResult Nrt_SparseSetMemoryContainer_Iterator_GetValuePair(
        NrtSparseSetMemoryContainer_IteratorHandle iterator,
        size_t* outputId,
        NrtSparseSetMemoryContainer_ByteIteratorViewHandle* outputView)
    {
        if (iterator == nullptr)
        {
            Nrt_setErrIsNullInstanceProvided();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputId == nullptr || outputView == nullptr)
        {
            Nrt_setErrIsNullArgProvided();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        try
        {
            auto ptr = reinterpret_cast<SparseSetMemoryContainer::Iterator*>(iterator);
            auto [key, val] = ptr->operator*();
            *outputId = key;
            auto valPtr = new SparseSetMemoryContainer::ByteIteratorView(dummyByteVectorSparseSet.begin(), 0);
            *valPtr = val;
            *outputView = reinterpret_cast<NrtSparseSetMemoryContainer_ByteIteratorViewHandle>(valPtr);
            return NRT_SUCCESS;
        }
        catch (const std::out_of_range&)
        {
            Nrt_setErrMsgIsArgumentOutOfRangeInternal();
            return NRT_FAILURE_ARGUMENT_OUT_OF_RANGE;
        }
        catch (const std::exception&) // TODO: I'm not sure if this will throw anything else. Docs weren't clear. :(
        {
            Nrt_setErrMsgErrorUnknown();
            return NRT_FAILURE_UNKNOWN;
        }
    }

    NrtResult Nrt_SparseSetMemoryContainer_Iterator_Destroy(NrtSparseSetMemoryContainer_IteratorHandle iterator)
    {
        if (iterator == nullptr)
        {
            Nrt_setErrIsNullInstanceProvided();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        delete reinterpret_cast<SparseSetMemoryContainer::Iterator*>(iterator);

        return NRT_SUCCESS;
    }

    void Nrt_SparseSetMemoryContainer_ConstIterator_MoveNext(NrtSparseSetMemoryContainer_ConstIteratorHandle iterator)
    {
        (*reinterpret_cast<SparseSetMemoryContainer::ConstIterator*>(iterator))++;
    }

    NrtBool Nrt_SparseSetMemoryContainer_ConstIterator_Equal(NrtSparseSetMemoryContainer_ConstIteratorHandle lhs,
                                                             NrtSparseSetMemoryContainer_ConstIteratorHandle rhs)
    {
        return ((*reinterpret_cast<SparseSetMemoryContainer::ConstIterator*>(lhs)) ==
                (*reinterpret_cast<SparseSetMemoryContainer::ConstIterator*>(rhs)))
                   ? NRT_TRUE
                   : NRT_FALSE;
    }

    NrtBool Nrt_SparseSetMemoryContainer_ConstIterator_NotEqual(NrtSparseSetMemoryContainer_ConstIteratorHandle lhs,
                                                                NrtSparseSetMemoryContainer_ConstIteratorHandle rhs)
    {
        return ((*reinterpret_cast<SparseSetMemoryContainer::ConstIterator*>(lhs)) !=
                (*reinterpret_cast<SparseSetMemoryContainer::ConstIterator*>(rhs)))
                   ? NRT_TRUE
                   : NRT_FALSE;
    }

    NrtResult Nrt_SparseSetMemoryContainer_ConstIterator_GetValuePair(
        NrtSparseSetMemoryContainer_ConstIteratorHandle iterator,
        size_t* outputId,
        NrtSparseSetMemoryContainer_ConstByteIteratorViewHandle* outputView)
    {
        if (iterator == nullptr)
        {
            Nrt_setErrIsNullInstanceProvided();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputId == nullptr || outputView == nullptr)
        {
            Nrt_setErrIsNullArgProvided();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        try
        {
            auto ptr = reinterpret_cast<SparseSetMemoryContainer::ConstIterator*>(iterator);
            auto [key, val] = ptr->operator*();
            *outputId = key;
            auto valPtr = new SparseSetMemoryContainer::ConstByteIteratorView(dummyByteVectorSparseSet.cbegin(), 0);
            *valPtr = val;
            *outputView = reinterpret_cast<NrtSparseSetMemoryContainer_ConstByteIteratorViewHandle>(valPtr);
            return NRT_SUCCESS;
        }
        catch (const std::out_of_range&)
        {
            Nrt_setErrMsgIsArgumentOutOfRangeInternal();
            return NRT_FAILURE_ARGUMENT_OUT_OF_RANGE;
        }
        catch (const std::exception&) // I'm not sure if this will throw anything else. Docs weren't clear. :(
        {
            Nrt_setErrMsgErrorUnknown();
            return NRT_FAILURE_UNKNOWN;
        }
    }
}
NrtResult Nrt_SparseSetMemoryContainer_ConstIterator_Destroy(NrtSparseSetMemoryContainer_ConstIteratorHandle iterator)
{
    if (iterator == nullptr)
    {
        Nrt_setErrIsNullInstanceProvided();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    delete reinterpret_cast<SparseSetMemoryContainer::ConstIterator*>(iterator);

    return NRT_SUCCESS;
}
