// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Ecs/NrtComponentCache.h>
#include <NovelRT/Ecs/ComponentCache.h>

using namespace NovelRT::Ecs;

extern "C"
{
    NrtComponentCache Nrt_ComponentCache_Create(size_t poolSize)
    {
        return reinterpret_cast<NrtComponentCache>(new ComponentCache(poolSize));
    }

    NrtResult Nrt_ComponentCache_RegisterComponentTypeUnsafe(NrtComponentCache componentCache,
                                                             size_t sizeOfDataType,
                                                             const void* deleteInstructionState,
                                                             NrtComponentUpdateFnPtr updateFnPtr,
                                                             NrtComponentTypeId* outputResult)
    {
        if (componentCache == nullptr || deleteInstructionState == nullptr || outputResult == nullptr)
        {
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        try
        {
            *outputResult =
                reinterpret_cast<ComponentCache*>(componentCache)
                    ->RegisterComponentTypeUnsafe(
                        sizeOfDataType, deleteInstructionState, [=](auto lhs, auto rhs, auto size) {
                            updateFnPtr(reinterpret_cast<NrtSparseSetMemoryContainer_ByteIteratorView>(&lhs),
                                        reinterpret_cast<NrtSparseSetMemoryContainer_ByteIteratorView>(&rhs), size);
                        });

            return NRT_SUCCESS;
        }
        catch (const std::bad_alloc&)
        {
            return NRT_FAILURE_OUT_OF_MEMORY;
        }
    }

    NrtResult Nrt_ComponentCache_GetComponentBufferById(NrtComponentCache componentCache,
                                                        NrtComponentTypeId id,
                                                        NrtComponentBufferMemoryContainer* outputResult)
    {
        if (componentCache == nullptr || outputResult == nullptr)
        {
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        *outputResult = reinterpret_cast<NrtComponentBufferMemoryContainer>(
            reinterpret_cast<ComponentCache*>(componentCache)->GetComponentBufferById(id).get());

        return NRT_SUCCESS;
    }

    void Nrt_ComponentCache_PrepAllBuffersForNextFrame(NrtComponentCache componentCache,
                                                       NrtEntityIdVector entitiesToDelete)
    {
        reinterpret_cast<ComponentCache*>(componentCache)
            ->PrepAllBuffersForNextFrame(*reinterpret_cast<std::vector<EntityId>*>(entitiesToDelete));
    }

    NrtResult Nrt_ComponentCache_Destroy(NrtComponentCache componentCache)
    {
        if (componentCache == nullptr)
        {
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        delete reinterpret_cast<ComponentCache*>(componentCache);

        return NRT_SUCCESS;
    }
}
