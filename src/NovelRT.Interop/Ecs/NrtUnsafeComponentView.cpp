// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Ecs/NrtUnsafeComponentView.h>
#include <NovelRT/Ecs/UnsafeComponentView.h>
#include <NovelRT/Exceptions/DuplicateKeyException.h>

using namespace NovelRT::Ecs;
using namespace NovelRT::Exceptions;

std::vector<size_t> dummySizeTVector;
std::vector<std::byte> dummyByteVector;

extern "C"
{
    NrtUnsafeComponentView Nrt_UnsafeComponentView_Create(size_t poolId, NrtComponentBufferMemoryContainer container)
    {
        return reinterpret_cast<NrtUnsafeComponentView>(new UnsafeComponentView(
            poolId, reinterpret_cast<ComponentBufferMemoryContainer*>(container)->shared_from_this()));
    }

    NrtResult Nrt_UnsafeComponentView_PushComponentUpdateInstruction(NrtUnsafeComponentView componentView,
                                                                     void* instructionData)
    {
        if (componentView == nullptr || instructionData == nullptr)
        {
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        try
        {
            reinterpret_cast<UnsafeComponentView*>(componentView)->PushComponentUpdateInstruction(instructionData);
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

    NrtResult Nrt_UnsafeComponentView_RemoveComponent(NrtUnsafeComponentView componentView, NrtEntityId entity)
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

    NrtResult Nrt_UnsafeComponentView_GetComponent(NrtUnsafeComponentView componentView,
                                                   NrtEntityId entity,
                                                   NrtComponentBufferMemoryContainer_ImmutableDataView* outputResult)
    {
        if (componentView == nullptr || outputResult == nullptr)
        {
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        try
        {
            auto ptr = new ComponentBufferMemoryContainer::ImmutableDataView(nullptr, 0);
            *ptr = reinterpret_cast<UnsafeComponentView*>(componentView)->GetComponent(entity);
            *outputResult = reinterpret_cast<NrtComponentBufferMemoryContainer_ImmutableDataView>(ptr);

            return NRT_SUCCESS;
        }
        catch (const KeyNotFoundException&)
        {
            return NRT_FAILURE_KEY_NOT_FOUND;
        }
    }

    NrtComponentBufferMemoryContainer_ImmutableDataView Nrt_UnsafeComponentView_GetComponentUnsafe(
        NrtUnsafeComponentView componentView,
        NrtEntityId entity)
    {
        auto ptr = new ComponentBufferMemoryContainer::ImmutableDataView(nullptr, 0);
        *ptr = reinterpret_cast<UnsafeComponentView*>(componentView)->GetComponent(entity);
        return reinterpret_cast<NrtComponentBufferMemoryContainer_ImmutableDataView>(ptr);
    }

    size_t Nrt_UnsafeComponentView_GetImmutableDataLength(NrtUnsafeComponentView componentView)
    {
        return reinterpret_cast<UnsafeComponentView*>(componentView)->GetImmutableDataLength();
    }

    NrtSparseSetMemoryContainer_ConstIterator Nrt_UnsafeComponentView_begin(NrtUnsafeComponentView componentView)
    {
        auto ptr = new SparseSetMemoryContainer::ConstIterator(std::make_tuple(
            dummySizeTVector.cbegin(), SparseSetMemoryContainer::ConstByteIteratorView(dummyByteVector.cend(), 0)));

        *ptr = reinterpret_cast<UnsafeComponentView*>(componentView)->begin();
        return reinterpret_cast<NrtSparseSetMemoryContainer_ConstIterator>(ptr);
    }

    NrtSparseSetMemoryContainer_ConstIterator Nrt_UnsafeComponentView_end(NrtUnsafeComponentView componentView)
    {
        auto ptr = new SparseSetMemoryContainer::ConstIterator(std::make_tuple(
            dummySizeTVector.cbegin(), SparseSetMemoryContainer::ConstByteIteratorView(dummyByteVector.cend(), 0)));

        *ptr = reinterpret_cast<UnsafeComponentView*>(componentView)->begin();
        return reinterpret_cast<NrtSparseSetMemoryContainer_ConstIterator>(ptr);
    }

    NrtResult Nrt_UnsafeComponentView_Destroy(NrtUnsafeComponentView componentView)
    {
        if (componentView == nullptr)
        {
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        delete reinterpret_cast<UnsafeComponentView*>(componentView);

        return NRT_SUCCESS;
    }
}