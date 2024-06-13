// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Ecs/NrtComponentBufferMemoryContainer.h>
#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT/Ecs/Ecs.h>

#include <vector>

using namespace NovelRT::Ecs;
using namespace NovelRT::Exceptions;

std::vector<size_t> dummySizeTCollection{};
std::vector<uint8_t> dummyByteCollection{};

extern "C"
{
    NrtComponentBufferMemoryContainerHandle Nrt_ComponentBufferMemoryContainer_Create(
        size_t poolSize,
        void* deleteInstructionState,
        size_t sizeOfDataTypeInBytes,
        NrtComponentUpdateFnPtr fnPtr,
        NrtComponentComparatorFnPtr comparatorPtr,
        const char* serialisedTypeName,
        void* context)
    {
        auto func = [=](void* lhs, const void* rhs, size_t size) { fnPtr(lhs, rhs, size, context); };
        auto comparatorFunc = [=](const void* lhs, const void* rhs) { return comparatorPtr(lhs, rhs, context); };

        return reinterpret_cast<NrtComponentBufferMemoryContainerHandle>(
            new ComponentBufferMemoryContainer(poolSize, deleteInstructionState, sizeOfDataTypeInBytes, func,
                                               comparatorFunc, std::string(serialisedTypeName)));
    }

    // TODO: Not sure if I should add safety here?
    void Nrt_ComponentBufferMemoryContainer_PrepContainerForFrame(NrtComponentBufferMemoryContainerHandle container,
                                                                  NrtEntityIdVectorHandle entitiesToDelete)
    {
        reinterpret_cast<ComponentBufferMemoryContainer*>(container)->PrepContainerForFrame(
            *reinterpret_cast<std::vector<EntityId>*>(entitiesToDelete));
    }

    NrtComponentBufferMemoryContainer_ImmutableDataViewHandle
    Nrt_ComponentBufferMemoryContainer_GetDeleteInstructionState(NrtComponentBufferMemoryContainerHandle container)
    {
        auto ptr = new ComponentBufferMemoryContainer::ImmutableDataView(nullptr, 0);
        *ptr = reinterpret_cast<ComponentBufferMemoryContainer*>(container)->GetDeleteInstructionState();

        return reinterpret_cast<NrtComponentBufferMemoryContainer_ImmutableDataViewHandle>(ptr);
    }

    NrtResult Nrt_ComponentBufferMemoryContainer_PushComponentUpdateInstruction(
        NrtComponentBufferMemoryContainerHandle container,
        size_t poolId,
        NrtEntityId entity,
        const void* componentData)
    {
        if (container == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (componentData == nullptr)
        {
            Nrt_SetErrMsgIsNullArgumentProvidedInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        try
        {
            reinterpret_cast<ComponentBufferMemoryContainer*>(container)->PushComponentUpdateInstruction(poolId, entity,
                                                                                                         componentData);
            return NRT_SUCCESS;
        }
        catch (const std::out_of_range&)
        {
            Nrt_SetErrMsgIsArgumentOutOfRangeInternal();
            return NRT_FAILURE_ARGUMENT_OUT_OF_RANGE;
        }
        catch (const DuplicateKeyException&)
        {
            Nrt_SetErrMsgDupKeyGivenInternal();
            return NRT_FAILURE_DUPLICATE_KEY_PROVIDED;
        }
    }

    NrtResult Nrt_ComponentBufferMemoryContainer_GetComponent(
        NrtComponentBufferMemoryContainerHandle container,
        NrtEntityId entity,
        NrtComponentBufferMemoryContainer_ImmutableDataViewHandle* outputResult)
    {
        if (container == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputResult == nullptr)
        {
            Nrt_SetErrMsgIsNullArgumentProvidedInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        try
        {
            auto ptr = new ComponentBufferMemoryContainer::ImmutableDataView(nullptr, 0);
            *ptr = reinterpret_cast<ComponentBufferMemoryContainer*>(container)->GetComponent(entity);
            *outputResult = reinterpret_cast<NrtComponentBufferMemoryContainer_ImmutableDataViewHandle>(ptr);

            return NRT_SUCCESS;
        }
        catch (const KeyNotFoundException&)
        {
            Nrt_SetErrMsgKeyNotFoundInternal();
            return NRT_FAILURE_KEY_NOT_FOUND;
        }
    }

    NrtComponentBufferMemoryContainer_ImmutableDataViewHandle Nrt_ComponentBufferMemoryContainer_GetComponentUnsafe(
        NrtComponentBufferMemoryContainerHandle container,
        NrtEntityId entity)
    {
        auto ptr = new ComponentBufferMemoryContainer::ImmutableDataView(nullptr, 0);
        *ptr = reinterpret_cast<ComponentBufferMemoryContainer*>(container)->GetComponentUnsafe(entity);

        return reinterpret_cast<NrtComponentBufferMemoryContainer_ImmutableDataViewHandle>(ptr);
    }

    NrtBool Nrt_ComponentBufferMemoryContainer_HasComponent(NrtComponentBufferMemoryContainerHandle container,
                                                            NrtEntityId entity)
    {
        return reinterpret_cast<ComponentBufferMemoryContainer*>(container)->HasComponent(entity) ? NRT_TRUE
                                                                                                  : NRT_FALSE;
    }

    size_t Nrt_ComponentBufferMemoryContainer_GetImmutableDataLength(NrtComponentBufferMemoryContainerHandle container)
    {
        return reinterpret_cast<ComponentBufferMemoryContainer*>(container)->GetImmutableDataLength();
    }

    NrtSparseSetMemoryContainer_ConstIteratorHandle Nrt_ComponentBufferMemoryContainer_Begin(
        NrtComponentBufferMemoryContainerHandle container)
    {
        auto ptr = new SparseSetMemoryContainer::ConstIterator(std::make_tuple(
            dummySizeTCollection.end(), SparseSetMemoryContainer::ConstByteIteratorView(dummyByteCollection.end(), 0)));
        *ptr = reinterpret_cast<ComponentBufferMemoryContainer*>(container)->begin();

        return reinterpret_cast<NrtSparseSetMemoryContainer_ConstIteratorHandle>(ptr);
    }

    NrtSparseSetMemoryContainer_ConstIteratorHandle Nrt_ComponentBufferMemoryContainer_End(
        NrtComponentBufferMemoryContainerHandle container)
    {
        auto ptr = new SparseSetMemoryContainer::ConstIterator(std::make_tuple(
            dummySizeTCollection.end(), SparseSetMemoryContainer::ConstByteIteratorView(dummyByteCollection.end(), 0)));
        *ptr = reinterpret_cast<ComponentBufferMemoryContainer*>(container)->end();

        return reinterpret_cast<NrtSparseSetMemoryContainer_ConstIteratorHandle>(ptr);
    }

    NrtResult Nrt_ComponentBufferMemoryContainer_Destroy(NrtComponentBufferMemoryContainerHandle container)
    {
        if (container == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        delete reinterpret_cast<ComponentBufferMemoryContainer*>(container);

        return NRT_SUCCESS;
    }

    const void* Nrt_ComponentBufferMemoryContainer_ImmutableDataView_GetDataHandle(
        NrtComponentBufferMemoryContainer_ImmutableDataViewHandle view)
    {
        return reinterpret_cast<ComponentBufferMemoryContainer::ImmutableDataView*>(view)->GetDataHandle();
    }

    NrtResult Nrt_ComponentBufferMemoryContainer_ImmutableDataView_Destroy(
        NrtComponentBufferMemoryContainer_ImmutableDataViewHandle view)
    {
        if (view == nullptr)
        {
            Nrt_SetErrMsgIsNullInstanceProvidedInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        delete reinterpret_cast<ComponentBufferMemoryContainer::ImmutableDataView*>(view);

        return NRT_SUCCESS;
    }
}
