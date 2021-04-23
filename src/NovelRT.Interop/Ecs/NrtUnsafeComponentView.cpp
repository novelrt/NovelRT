// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Ecs/NrtUnsafeComponentView.h>
#include <NovelRT/Ecs/Ecs.h>
#include <vector>

using namespace NovelRT::Ecs;
using namespace NovelRT::Exceptions;

std::vector<size_t> dummySizeTVectorComponentView;
std::vector<uint8_t> dummyByteVectorComponentView;

extern "C"
{
    NrtUnsafeComponentViewHandle Nrt_UnsafeComponentView_Create(size_t poolId,
                                                                NrtComponentBufferMemoryContainerHandle container)
    {
        return reinterpret_cast<NrtUnsafeComponentViewHandle>(new UnsafeComponentView(
            poolId, reinterpret_cast<ComponentBufferMemoryContainer*>(container)->shared_from_this()));
    }

    NrtResult Nrt_UnsafeComponentView_PushComponentUpdateInstruction(NrtUnsafeComponentViewHandle componentView,
                                                                     NrtEntityId entity,
                                                                     void* instructionData)
    {
        if (componentView == nullptr || instructionData == nullptr)
        {
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        try
        {
            reinterpret_cast<UnsafeComponentView*>(componentView)
                ->PushComponentUpdateInstruction(entity, instructionData);
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
        catch (const std::out_of_range&)
        {
            return NRT_FAILURE_ARGUMENT_OUT_OF_RANGE;
        }
    }

    NrtResult Nrt_UnsafeComponentView_RemoveComponent(NrtUnsafeComponentViewHandle componentView, NrtEntityId entity)
    {
        if (componentView == nullptr)
        {
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        try
        {
            reinterpret_cast<UnsafeComponentView*>(componentView)->RemoveComponent(entity);
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
        catch (const std::out_of_range&)
        {
            return NRT_FAILURE_ARGUMENT_OUT_OF_RANGE;
        }
    }

    NrtResult Nrt_UnsafeComponentView_GetComponent(
        NrtUnsafeComponentViewHandle componentView,
        NrtEntityId entity,
        NrtComponentBufferMemoryContainer_ImmutableDataViewHandle* outputResult)
    {
        if (componentView == nullptr || outputResult == nullptr)
        {
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        try
        {
            auto ptr = new ComponentBufferMemoryContainer::ImmutableDataView(nullptr, 0);
            *ptr = reinterpret_cast<UnsafeComponentView*>(componentView)->GetComponent(entity);
            *outputResult = reinterpret_cast<NrtComponentBufferMemoryContainer_ImmutableDataViewHandle>(ptr);

            return NRT_SUCCESS;
        }
        catch (const KeyNotFoundException&)
        {
            return NRT_FAILURE_KEY_NOT_FOUND;
        }
    }

    NrtComponentBufferMemoryContainer_ImmutableDataViewHandle Nrt_UnsafeComponentView_GetComponentUnsafe(
        NrtUnsafeComponentViewHandle componentView,
        NrtEntityId entity)
    {
        auto ptr = new ComponentBufferMemoryContainer::ImmutableDataView(nullptr, 0);
        *ptr = reinterpret_cast<UnsafeComponentView*>(componentView)->GetComponent(entity);
        return reinterpret_cast<NrtComponentBufferMemoryContainer_ImmutableDataViewHandle>(ptr);
    }

    size_t Nrt_UnsafeComponentView_GetImmutableDataLength(NrtUnsafeComponentViewHandle componentView)
    {
        return reinterpret_cast<UnsafeComponentView*>(componentView)->GetImmutableDataLength();
    }

    NrtSparseSetMemoryContainer_ConstIteratorHandle Nrt_UnsafeComponentView_begin(
        NrtUnsafeComponentViewHandle componentView)
    {
        auto ptr = new SparseSetMemoryContainer::ConstIterator(
            std::make_tuple(dummySizeTVectorComponentView.cbegin(),
                            SparseSetMemoryContainer::ConstByteIteratorView(dummyByteVectorComponentView.cend(), 0)));

        *ptr = reinterpret_cast<UnsafeComponentView*>(componentView)->begin();
        return reinterpret_cast<NrtSparseSetMemoryContainer_ConstIteratorHandle>(ptr);
    }

    NrtSparseSetMemoryContainer_ConstIteratorHandle Nrt_UnsafeComponentView_end(
        NrtUnsafeComponentViewHandle componentView)
    {
        auto ptr = new SparseSetMemoryContainer::ConstIterator(
            std::make_tuple(dummySizeTVectorComponentView.cbegin(),
                            SparseSetMemoryContainer::ConstByteIteratorView(dummyByteVectorComponentView.cend(), 0)));

        *ptr = reinterpret_cast<UnsafeComponentView*>(componentView)->end();
        return reinterpret_cast<NrtSparseSetMemoryContainer_ConstIteratorHandle>(ptr);
    }

    NrtResult Nrt_UnsafeComponentView_Destroy(NrtUnsafeComponentViewHandle componentView)
    {
        if (componentView == nullptr)
        {
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        delete reinterpret_cast<UnsafeComponentView*>(componentView);

        return NRT_SUCCESS;
    }
}
