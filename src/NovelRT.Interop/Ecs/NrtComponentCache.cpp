// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Ecs/NrtComponentCache.h>
#include <NovelRT/Ecs/Ecs.h>

using namespace NovelRT::Ecs;

extern "C"
{
    NrtComponentCacheHandle Nrt_ComponentCache_Create(size_t poolSize)
    {
        return reinterpret_cast<NrtComponentCacheHandle>(new ComponentCache(poolSize));
    }

    NrtResult Nrt_ComponentCache_RegisterComponentTypeUnsafe(NrtComponentCacheHandle componentCache,
                                                             size_t sizeOfDataType,
                                                             const void* deleteInstructionState,
                                                             NrtComponentUpdateFnPtr updateFnPtr,
                                                             const char* serialisedTypeName,
                                                             void* context,
                                                             NrtComponentTypeId* outputResult)
    {
        if (componentCache == nullptr)
        {
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (deleteInstructionState == nullptr || outputResult == nullptr)
        {
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        try
        {
            *outputResult =
                reinterpret_cast<ComponentCache*>(componentCache)
                    ->RegisterComponentTypeUnsafe(
                        sizeOfDataType, deleteInstructionState,
                        [=](auto lhs, auto rhs, auto size) {
                            updateFnPtr(reinterpret_cast<NrtSparseSetMemoryContainer_ByteIteratorViewHandle>(&lhs),
                                        reinterpret_cast<NrtSparseSetMemoryContainer_ByteIteratorViewHandle>(&rhs),
                                        size, context);
                        },
                        std::string(serialisedTypeName));

            return NRT_SUCCESS;
        }
        catch (const std::bad_alloc&)
        {
            return NRT_FAILURE_OUT_OF_MEMORY;
        }
    }

    NrtResult Nrt_ComponentCache_GetComponentBufferById(NrtComponentCacheHandle componentCache,
                                                        NrtComponentTypeId id,
                                                        NrtComponentBufferMemoryContainerHandle* outputResult)
    {
        if (componentCache == nullptr)
        {
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputResult == nullptr)
        {
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        *outputResult = reinterpret_cast<NrtComponentBufferMemoryContainerHandle>(
            reinterpret_cast<ComponentCache*>(componentCache)->GetComponentBufferById(id).get());

        return NRT_SUCCESS;
    }

    void Nrt_ComponentCache_PrepAllBuffersForNextFrame(NrtComponentCacheHandle componentCache,
                                                       NrtEntityIdVectorHandle entitiesToDelete)
    {
        reinterpret_cast<ComponentCache*>(componentCache)
            ->PrepAllBuffersForNextFrame(*reinterpret_cast<std::vector<EntityId>*>(entitiesToDelete));
    }

    NrtResult Nrt_ComponentCache_Destroy(NrtComponentCacheHandle componentCache)
    {
        if (componentCache == nullptr)
        {
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        delete reinterpret_cast<ComponentCache*>(componentCache);

        return NRT_SUCCESS;
    }
}
