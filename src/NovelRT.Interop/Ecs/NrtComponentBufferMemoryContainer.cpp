// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Ecs/NrtComponentBufferMemoryContainer.h>
#include <NovelRT/Ecs/ComponentBufferMemoryContainer.h>
#include <NovelRT/Exceptions/Exceptions.h>

using namespace NovelRT::Ecs;
using namespace NovelRT::Exceptions;

std::vector<size_t> dummySizeTCollection{};
std::vector<std::byte> dummyByteCollection{};

extern "C"
{
    NrtComponentBufferMemoryContainer Nrt_ComponentBufferMemoryContainer_Create(size_t poolSize,
                                                                                void* deleteInstructionState,
                                                                                size_t sizeOfDataTypeInBytes,
                                                                                NrtComponentUpdateFnPtr fnPtr)
    {
        auto func = [=](SparseSetMemoryContainer::ByteIteratorView lhs, SparseSetMemoryContainer::ByteIteratorView rhs,
                        size_t size) {
            fnPtr(reinterpret_cast<NrtSparseSetMemoryContainer_ByteIteratorView>(&lhs),
                  reinterpret_cast<NrtSparseSetMemoryContainer_ByteIteratorView>(&rhs), size);
        };

        return reinterpret_cast<NrtComponentBufferMemoryContainer>(
            new ComponentBufferMemoryContainer(poolSize, deleteInstructionState, sizeOfDataTypeInBytes, func));
    }

    // TODO: Not sure if I should add safety here?
    void Nrt_ComponentBufferMemoryContainer_PrepContainerForFrame(NrtComponentBufferMemoryContainer container,
                                                                  NrtEntityIdVector entitiesToDelete)
    {
        reinterpret_cast<ComponentBufferMemoryContainer*>(container)->PrepContainerForFrame(
            *reinterpret_cast<std::vector<EntityId>*>(entitiesToDelete));
    }

    NrtComponentBufferMemoryContainer_ImmutableDataView Nrt_ComponentBufferMemoryContainer_GetDeleteInstructionState(
        NrtComponentBufferMemoryContainer container)
    {
        auto ptr = new ComponentBufferMemoryContainer::ImmutableDataView(nullptr, 0);
        *ptr = reinterpret_cast<ComponentBufferMemoryContainer*>(container)->GetDeleteInstructionState();

        return reinterpret_cast<NrtComponentBufferMemoryContainer_ImmutableDataView>(ptr);
    }

    NrtResult Nrt_ComponentBufferMemoryContainer_PushComponentUpdateInstruction(
        NrtComponentBufferMemoryContainer container,
        size_t poolId,
        NrtEntityId entity,
        const void* componentData)
    {
        if (container == nullptr || componentData == nullptr)
        {
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        try
        {
            reinterpret_cast<ComponentBufferMemoryContainer*>(container)->PushComponentUpdateInstruction(poolId, entity,
                                                                                                         componentData);
            return NRT_SUCCESS;
        }
        catch (const std::out_of_range&)
        {
            return NRT_FAILURE_ARGUMENT_OUT_OF_RANGE;
        }
        catch (const DuplicateKeyException&)
        {
            return NRT_FAILURE_DUPLICATE_KEY_PROVIDED;
        }
    }

    NrtResult Nrt_ComponentBufferMemoryContainer_GetComponent(
        NrtComponentBufferMemoryContainer container,
        NrtEntityId entity,
        NrtComponentBufferMemoryContainer_ImmutableDataView* outputResult)
    {
        if (container == nullptr || outputResult == nullptr)
        {
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        try
        {
            auto ptr = new ComponentBufferMemoryContainer::ImmutableDataView(nullptr, 0);
            *ptr = reinterpret_cast<ComponentBufferMemoryContainer*>(container)->GetComponent(entity);
            *outputResult = reinterpret_cast<NrtComponentBufferMemoryContainer_ImmutableDataView>(ptr);

            return NRT_SUCCESS;
        }
        catch (const KeyNotFoundException&)
        {
            return NRT_FAILURE_KEY_NOT_FOUND;
        }
    }

    NrtComponentBufferMemoryContainer_ImmutableDataView Nrt_ComponentBufferMemoryContainer_GetComponentUnsafe(
        NrtComponentBufferMemoryContainer container,
        NrtEntityId entity)
    {
        auto ptr = new ComponentBufferMemoryContainer::ImmutableDataView(nullptr, 0);
        *ptr = reinterpret_cast<ComponentBufferMemoryContainer*>(container)->GetComponentUnsafe(entity);

        return reinterpret_cast<NrtComponentBufferMemoryContainer_ImmutableDataView>(ptr);
    }

    NrtBool Nrt_ComponentBufferMemoryContainer_HasComponent(NrtComponentBufferMemoryContainer container,
                                                            NrtEntityId entity)
    {
        return reinterpret_cast<ComponentBufferMemoryContainer*>(container)->HasComponent(entity) ? NRT_TRUE
                                                                                                  : NRT_FALSE;
    }

    size_t Nrt_ComponentBufferMemoryContainer_GetImmutableDataLength(NrtComponentBufferMemoryContainer container)
    {
        return reinterpret_cast<ComponentBufferMemoryContainer*>(container)->GetImmutableDataLength();
    }

    NrtSparseSetMemoryContainer_ConstIterator Nrt_ComponentBufferMemoryContainer_begin(
        NrtComponentBufferMemoryContainer container)
    {
        auto ptr = new SparseSetMemoryContainer::ConstIterator(std::make_tuple(
            dummySizeTCollection.end(), SparseSetMemoryContainer::ConstByteIteratorView(dummyByteCollection.end(), 0)));
        *ptr = reinterpret_cast<ComponentBufferMemoryContainer*>(container)->begin();

        return reinterpret_cast<NrtSparseSetMemoryContainer_ConstIterator>(ptr);
    }

    NrtSparseSetMemoryContainer_ConstIterator Nrt_ComponentBufferMemoryContainer_end(
        NrtComponentBufferMemoryContainer container)
    {
        auto ptr = new SparseSetMemoryContainer::ConstIterator(std::make_tuple(
            dummySizeTCollection.end(), SparseSetMemoryContainer::ConstByteIteratorView(dummyByteCollection.end(), 0)));
        *ptr = reinterpret_cast<ComponentBufferMemoryContainer*>(container)->end();

        return reinterpret_cast<NrtSparseSetMemoryContainer_ConstIterator>(ptr);
    }

    NrtResult Nrt_ComponentBufferMemoryContainer_Destroy(NrtComponentBufferMemoryContainer container)
    {
        if (container == nullptr)
        {
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        delete reinterpret_cast<ComponentBufferMemoryContainer*>(container);

        return NRT_SUCCESS;
    }

    const void* Nrt_ComponentBufferMemoryContainer_ImmutableDataView_GetDataHandle(
        NrtComponentBufferMemoryContainer_ImmutableDataView view)
    {
        return reinterpret_cast<ComponentBufferMemoryContainer::ImmutableDataView*>(view)->GetDataHandle();
    }

    NrtResult Nrt_ComponentBufferMemoryContainer_ImmutableDataView_Destroy(
        NrtComponentBufferMemoryContainer_ImmutableDataView view)
    {
        if (view == nullptr)
        {
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        delete reinterpret_cast<ComponentBufferMemoryContainer::ImmutableDataView*>(view);

        return NRT_SUCCESS;
    }
}
